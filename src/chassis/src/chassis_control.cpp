#include "builtin_interfaces/msg/detail/time__struct.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/logging.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/rate.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/utilities.hpp"
#include "sensor_msgs/msg/detail/joint_state__struct.hpp"
#include "std_msgs/msg/detail/header__struct.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <memory>
#include <ratio>
#include<string>
#include <vector>



class Chassis: public rclcpp::Node
{
    public:
    Chassis():Node("Chassis"),count(0)
    {
        RCLCPP_INFO(this->get_logger(),"Chassis node start!!");
        pub_joint = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
        init_joint_states();
    }

    void thread_pub_()
    {
        rclcpp::Rate loop_rate(10);
        double current_time = this->get_clock()->now().seconds();

        while (rclcpp::ok()) {
            double delta_time = this->get_clock()->now().seconds() - current_time;
            current_time = this->get_clock()->now().seconds();
            RCLCPP_INFO(this->get_logger(),"%f",current_time);

            for(int i = 0; i<8 ;i++)
            {
                positions[i] += delta_time*speeds[i];
            }
            pub_joint_data(names, positions, speeds, efforts);
            loop_rate.sleep();
        }
    }

    void update_speed(std::vector<double> &speeds_)
    {
        speeds = speeds_;
    }

    private:
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr pub_joint;
    uint64_t count;

    std::vector<double> speeds;
    std::vector<std::string> names;
    std::vector<double> positions;
    std::vector<double> efforts;

    void init_joint_states()
    {
        names.push_back("wheel_joint_left1");
        names.push_back("wheel_joint_left2");
        names.push_back("wheel_joint_right1");
        names.push_back("wheel_joint_right2");
        names.push_back("left1_wheel_joint");
        names.push_back("left2_wheel_joint");
        names.push_back("right1_wheel_joint");
        names.push_back("right2_wheel_joint");

        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);
        speeds.push_back(0.0);

        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
        positions.push_back(0.0);
    }

    void pub_joint_data(const std::vector<std::string> &name_,
                        const std::vector<double> &position,
                        const std::vector<double> &speed,
                        const std::vector<double> &effort)
    {
        std::shared_ptr<sensor_msgs::msg::JointState> msg  = std::make_shared<sensor_msgs::msg::JointState>();
        std::shared_ptr<std_msgs::msg::Header> header = std::make_shared<std_msgs::msg::Header>();
        std::shared_ptr<builtin_interfaces::msg::Time> time = std::make_shared<builtin_interfaces::msg::Time>();

        time->set__sec((int32_t)(this->get_clock()->now().seconds()));
        time->set__nanosec((this->get_clock()->now().nanoseconds()));
        std::string frame_id  = "frame_id: "+std::to_string(count);

        header->set__frame_id(frame_id);
        header->set__stamp(*time);

        msg->set__header(*header);
        msg->set__name(name_);
        //(void)position;
        msg->set__position(position);
        msg->set__velocity(speed);
        msg->set__effort(effort);

        RCLCPP_INFO(this->get_logger(),"Success,%ld",count);
        count++;

        pub_joint->publish(*msg);
    }
};

int main(int argc, char** argv)
{
    std::vector<double> speeds_{1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Chassis>();
    node->update_speed(speeds_);
    node->thread_pub_();
    rclcpp::spin(node);
    rclcpp::shutdown();
}