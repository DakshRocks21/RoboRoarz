// file to intialise the sensors according to their position on the robot

// DO NOT DELETE / COMMENT THESE LINES !!!!

// lets never ever edit this
void sensor_initialisation() {
  
    right_sensor_status = my_robot.module1_sensor_status(6);
    bottom_right_sensor_status = my_robot.module1_sensor_status(4);
    left_sensor_status = my_robot.module1_sensor_status(10);
    bottom_left_sensor_status = my_robot.module1_sensor_status(0);
    
    movements();

}
