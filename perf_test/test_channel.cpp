#include "channel.h"

int main(int argc, char* argv[])
{
    unsigned long period;
    pid_t pid;
    if(argc != 3 ||
        sscanf(argv[1], "%lu", &period) != 1 ||
        sscanf(argv[2], "%d", &pid) != 1)
    {
        printf("USAGE: %s <period> <pid>\n", argv[0]);
        return 1;
    }
    Channel c;
    Channel c1;
    Channel c2;
    int ret = c.bind(pid, Channel::CHANNEL_LLC_MISS_LD);//LLC_MISS
    int ret1= c1.bind(pid, Channel::CHANNEL_LLC_HIT_LD);//LLC_HIT
    int ret2= c2.bind(pid, Channel::CHANNEL_LOAD);//LLC_ALLLD
    if(ret)
        return ret;
    ret = c.setPeriod(period);
    ret1= c1.setPeriod(period);
    ret2= c2.setPeriod(period);
    if(ret)
        return ret;
    while(true)
    {
        Channel::Sample sample;
        Channel::Sample sample1;
        Channel::Sample sample2;
        ret = c.readSample(&sample);
        ret1= c1.readSample(&sample1);
        ret2= c2.readSample(&sample2);

        if(ret == -EAGAIN && ret1== -EAGAIN && ret2 == -EAGAIN)
        {
            usleep(10000);
            continue;   
        }
        if(ret != -EAGAIN)
        {
            printf("type: %x, cpu: %u, pid: %u, tid: %u, address: %lx, time: %lu LLC_MISS_LD \n",
                sample.type, sample.cpu, sample.pid, sample.tid, sample.address,sample.time);
        }
        if(ret1 != -EAGAIN)
        {
            printf("type: %x, cpu: %u, pid: %u, tid: %u, address: %lx, time: %lu LLC_HIT_LD\n"
                ,sample1.type, sample1.cpu, sample1.pid, sample1.tid, sample1.address,sample1.time);
        }
        if(ret2 != -EAGAIN)
        {
            printf("type: %x, cpu: %u, pid: %u, tid: %u, address: %lx, time: %lu ALL_LD\n"
                ,sample2.type, sample2.cpu, sample2.pid, sample2.tid, sample2.address,sample2.time);
        }

    }
    return 0;
}