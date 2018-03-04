#include "hw.hpp"
#include "MVNormal.hpp"

class HW42:public HW
{   
    public:
    private:
    public:
    Eigen::VectorXd getOmega(Eigen::MatrixXd mu, Eigen::MatrixXd Sigma);
    double calculateVariance(Eigen::MatrixXd portfolioReturn, int n);
    int service();
};