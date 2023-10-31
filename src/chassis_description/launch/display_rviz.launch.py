import os
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    package_name = 'chassis_description'
    chassis_name = 'steering'
    urdf_name = "chassis_demo.urdf"
    rviz_name = "chassis_rviz.rviz"

    ld = LaunchDescription()
    pkg_share = FindPackageShare(package=package_name).find(package_name) 
    urdf_model_path = os.path.join(pkg_share, f'urdf/{urdf_name}')
    rviz_config_path = os.path.join(pkg_share,f'rviz2/{rviz_name}')

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        arguments=[urdf_model_path]
        )
    
    joint_state_pub_node = Node(
        package='chassis',
        executable='steering',
        name='Chassis'
    )

    joint_state_publisher_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        arguments=[urdf_model_path]
        )

    rviz2_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_path],
        output='screen',
        )
    
    ld.add_action(robot_state_publisher_node)
    ld.add_action(joint_state_pub_node)
    #ld.add_action(joint_state_publisher_node)
    ld.add_action(rviz2_node)

    return ld
