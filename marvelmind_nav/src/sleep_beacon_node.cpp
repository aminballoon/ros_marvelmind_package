#include <chrono>
#include <string>
#include <iostream> 
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
extern "C"
{
#include "marvelmind_nav/marvelmind_example.h"
#include "marvelmind_nav/marvelmind_devices.h"
#include "marvelmind_nav/marvelmind_utils.h"
#include "marvelmind_nav/marvelmind_pos.h"
#include "marvelmind_nav/marvelmind_api.h"
}

using namespace std::chrono_literals;


int main()
{
    marvelmindStart();
    char str[7] = {'s', 'l', 'e', 'e', 'p', ' ', '0'};
    char *token1 = strtok(str, " ");
    trim(token1);
    char *token2 = strtok(NULL, " ");
    while(!marvelmindCycle());
    while(marvelmindCheckSleepCommand(token1, token2));
    sleep_ms(10000);
    


    marvelmindFinish();

    return 0;
}