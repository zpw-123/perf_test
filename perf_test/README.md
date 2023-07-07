# perf_test_new
# perf_test 
## 编译   
g++ -std=gnu++11 -g channel.cpp test_channel.cpp -o test_channel
## 运行  
./test_channel 10000 pid   
10000==period 采样周期   
pid 可以写 286810等等(通过top查看)   
