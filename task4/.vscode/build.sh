build_path=$1
output_file_name=$2
cmake_path="cmakeBuild"

mkdir $cmake_path
cd $cmake_path
cmake .. -DOUTPUT_FILE_NAME=$output_file_name
make