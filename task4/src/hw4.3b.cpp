#include "../included/src/hw4.3b.hpp"
//call option payoff
double HW43b::payoff(double spot, double strike)
{
    return spot > strike ? (spot - strike) : 0;
}
//simulate spot price using classical BS model
double HW43b::spotPrice()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);
  //  s_0 = 50.0, r = 0.05, sigma = 0.3;
  //  drift_log = r - 0.5 * sigma * sigma
  //  dt = 0.25
  //  dW = std::sqrt(dt) * norm(rng)
  //  log_price = s_0 + drift_log * dt + sigma * dW

    return 50.0*std::exp((0.05 - 0.5 * pow(0.3,2))*0.25 + 0.3*std::sqrt(0.25) * norm(rng));
}

double HW43b::calculateMean(double *data, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double HW43b::calculateVariance(double *data,double mean, int n)
{
    double variance = 0.0;

    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);

    return variance / (n - 1);
}
double HW43b::calculateCovariance(double *data1, double *data2, int n)
{
    double mean1, mean2, covariance = 0.0;

    double sum1 = 0.0, sum2 = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum1 += data1[i];
        sum2 += data2[i];
    }
    mean1 = sum1 / n;
    mean2 = sum2 / n;

    for (int i = 0; i < n; i++)
        covariance += (data1[i] - mean1) * (data2[i] - mean2);

    return covariance / (n - 1);
}
double *HW43b::confidenceInterval(double mean, double SD, int n)
{
    double *result = new double[2];
    if (n < 100)
    { //n=10,df=9,t_9=2.262
        result[0] = mean - 2.262 * SD;
        result[1] = mean + 2.262 * SD;
    }
    else if (n < 1000)
    { //n=100,t=1.984
        result[0] = mean - 1.984 * SD;
        result[1] = mean + 1.984 * SD;
    }
    else
    { //z=1.96
        result[0] = mean - 1.96 * SD;
        result[1] = mean + 1.96 * SD;
    }
    return result;
}

double HW43b::normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double HW43b::expectationPayoff(double t, double S)
{

    double d1 = (std::log(S / 55) + (0.05 + pow(0.3, 2) / 2) * (0.25 - t)) / (0.3 * sqrt(0.25 - t));
    double d2 = d1 - 0.3 * sqrt(0.25 - t);
    return normalCDF(d1) * S * std::exp(0.05 * 0.25) - normalCDF(d2) * 55;
}


HW43b::value HW43b::getValue()
{
    value result;
    result.S_T = spotPrice();
    result.Y = payoff(result.S_T, 55.0);
    return result;
}

double HW43b::getb(std::vector<value> val, double y_mean, double s_t_mean, int n)
{
    double numerator = 0.0, denominator = 0.0;

    for (int i = 0; i < n; i++)
    {
        numerator += (val[i].S_T - s_t_mean) * (val[i].Y - y_mean);
        denominator += pow(val[i].S_T - s_t_mean, 2);
    }

    return numerator / denominator;
}

HW43b::a_final_result HW43b::getYb(value_set values, double b, int n)
{
    double r = 0.05, T = 0.25, s_0 = 50;

    a_final_result result;
    result.Yb = new double[n];
    result.Yb_mean = 0.0;
    double tmp = 0.0;
    for (int i = 0; i < n; i++)
    {
        tmp = values.values[i].Y - b * (values.values[i].S_T - std::exp(r * T) * s_0);
        result.Yb[i] = tmp;
        result.Yb_mean += tmp;
    }

    result.Yb_mean = result.Yb_mean / n;
    result.Y_mean = values.Y_Mean;

    return result;
}

int HW43b::work(int all_step, int length, int log_step, int thread_id)
{
    mt.lock();
    std::cout << "thread[" << thread_id << "] is working now.... " << std::endl;
    mt.unlock();

    clock_t start, end, mid;
    clock_t start_1;
    start_1 = clock();
    double time_t;

    double s_t_sum = 0.0, Y_sum = 0.0, s_t_mean = 0.0, y_mean = 0.0;

    value_set tmp_val_set;
    for (int i = 0; i < all_step; i++)
    {

        for (int j = 0; j < length; j++)
        {
            value val = getValue();

            tmp_val_set.values.push_back(val);
            Y_sum += val.Y;
            s_t_sum += val.S_T;
            // tt.append(to_string(spotPrice(1.1))).append(",");
        }
        // val_set[i].values = val_array;
        tmp_val_set.S_T_Mean = s_t_sum / length;
        tmp_val_set.Y_Mean = Y_sum / length;

        double b = getb(tmp_val_set.values, Y_sum / length, s_t_sum / length, length);

        auto result = getYb(tmp_val_set, b, length);

        Y_sum = 0, s_t_sum = 0;

        mt.lock();
        result_set.push_back(result);
        mt.unlock();

        tmp_val_set.values.clear();
        tmp_val_set.Y_Mean = 0.0;
        tmp_val_set.S_T_Mean = 0.0;
        if (i % log_step == 0)
        {
            mid = clock();
            time_t = (double)(mid - start_1) / CLOCKS_PER_SEC_SIMPLE;
            std::cout << "thread[" << thread_id << "] process time---> " << time_t << std::endl;
        }
    }
    mid = clock();
    time_t = (double)(mid - start_1) / CLOCKS_PER_SEC_SIMPLE;
    std::cout << "thread[" << thread_id << "] is done, process time---> " << time_t << std::endl;

    mt.lock();
    task_count.push_back(thread_id);
    mt.unlock();
}


int HW43b::run(int count, int thread_count, int length)
{

    int step_count = count / thread_count;
    int all_step = step_count / length;
    int step = step_count / 5;

    double EY = expectationPayoff(0, 50);

    clock_t start, end, mid;
    clock_t start_1;
    double time_t;
    bool running = false;

    for (int i = 0; i < thread_count; i++)
    {
        std::thread t(&HW43b::work,this, step_count, length, step, i);
        t.detach();
    }

    while (!running)
    {

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        running = task_count.size() == thread_count;
    }

    std::cout << "all thread is done..." << std::endl;

    double Yb_mean_mean = 0.0, Y_mean_mean = 0.0, Yb_sum = 0.0, Y_sum = 0.0;

    int frequency=0;
    for (int i = 0; i < result_set.size(); i++)
    {
        auto v=result_set[i];
        double sb=sqrt(calculateVariance(v.Yb,v.Yb_mean,length));
        double * tt=confidenceInterval(v.Yb_mean,sb/sqrt(length),length);
        if (EY > tt[0] && EY < tt[1])
        {
                frequency += 1;
        }
    }

    mid = clock();
    time_t = (double)(mid - start) / CLOCKS_PER_SEC_SIMPLE;
    std::cout << "main done,,,,,,,, time---> " << time_t << std::endl;
    result_set.clear();
    task_count.clear();
    return frequency;
}

int HW43b::service()
{
    int length = 5;
    int N[] = {10, 100, 1000, 10000,100000};
    int count = 10000, thread_count = 20;
    int result[length];
    for (int i = 0; i < length; i++)
    {
        result[i] = run(count, thread_count, N[i]);
    }
    for (int i = 0; i < length; i++)
    {
        std::cout << "When n = [ " << N[i] << " ], the probability that EY lies in the 95% confidence interval is " << result[i] / (count + 0.0) << std::endl;
    }
}
