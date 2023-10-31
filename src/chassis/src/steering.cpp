#include "steering.hpp"
#include <cmath>

float Steering::Steering_Wheel::get_wheel_v()
{
    return this->v_x;
}

void Steering::Chassis::Straight_Mode()
{
    this->State = Steering::Straight;
}

void Steering::Chassis::Straight_Speed(const float v_x ,const float v_y, const float delta)
{
    for(int i=0;i<4;i++)
    {
        wheel_ptr[i]->set_wheel_v(v_x,v_y);
        wheel_ptr[i]->set_wheel_w(0);
        wheel_ptr[i]->set_wheel_angle(delta);
    }
}
/*
void Steering::Chassis::Rotation_Speed(const float w)
{
    float v = w*wheel2center_length;
    for(int i=0;i<4;i++)
    {
        wheel_ptr[i]->set_wheel_v();
        wheel_ptr[i]->set_wheel_w(0);
        wheel_ptr[i]->set_wheel_angle();
    }
}
*/

void Steering::Chassis::Curve_Speed()
{

}