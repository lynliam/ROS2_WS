#include<cmath>
#include <memory>
#include <sys/types.h>


namespace Steering {

enum RState{
    WTR_OK = 0,
    WTR_ERROR
};

typedef unsigned int WTR_STATE ;

typedef enum {
    Stop = 0,
    Running
}Classis_State;
typedef enum{
    Straight = 0,//直线 
    DSM,         //斜行
    ZSM,         //原地旋转
    curve        //曲线模式
}Classis_Running_State;

class Steering_Wheel
{
public:
    Steering_Wheel():v_x(0),v_y(0),w(0),angle(0)
    {}
    float get_wheel_v();
    float get_wheel_w();
    float get_wheel_angle();

    WTR_STATE set_wheel_v(float v_x, float v_y);
    WTR_STATE set_wheel_w(float w_);
    WTR_STATE set_wheel_angle(float angle_);

private:
    float v_x;
    float v_y;
    float w;
    float angle;
    
};



class Chassis
{
public:
    Chassis(const unsigned int W,const unsigned int L):
    chassis_width(W),chassis_length(L),wheel2center_length(std::sqrt(L*L+W*W)/4.0),wheel2center_angle(std::atan(W/L))
    {
        wheel_ptr[0] = std::make_shared<Steering_Wheel>();
        wheel_ptr[1] = std::make_shared<Steering_Wheel>();
        wheel_ptr[2] = std::make_shared<Steering_Wheel>();
        wheel_ptr[3] = std::make_shared<Steering_Wheel>();
    }
    void Straight_Mode();
    void Rotation_Mode();

    void Straight_Speed(const float v_x ,const float v_y, const float w);

    void Rotation_Speed(const float w);

    void Curve_Speed();


private:
    std::shared_ptr<Steering_Wheel> wheel_ptr[4];
    int State;
    unsigned int chassis_width;
    unsigned int chassis_length;
    unsigned int wheel2center_length;
    unsigned int wheel2center_angle;

};

}

