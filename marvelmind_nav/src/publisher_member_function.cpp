#include <chrono>
#include <functional>
#include <memory>
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

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */


class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
      
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
      // marvelmindCycle();
      // checkCommand();
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};


// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   marvelmindStart();
//   // rclcpp::spin(std::make_shared<MinimalPublisher>());
//   while(1) 
//   {
//       marvelmindCycle();
//       sleep_ms(1);
//   }

//   marvelmindFinish();

//   // rclcpp::shutdown();
//   return 0;
// }


int main()
{
    marvelmindStart();
    char str[6] = {'w', 'a', 'k', 'e', ' ','0'};
    char *token1 = strtok(str, " ");
    trim(token1);
    char *token2 = strtok(NULL, " ");
    while(!marvelmindCycle());
    while(marvelmindCheckWakeCommand(token1, token2));
    sleep_ms(10000);


    marvelmindFinish();

    return 0;
}