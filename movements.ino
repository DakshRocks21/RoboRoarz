// function file to control the movement of the robot


void movements() {

 // BELOW IS THE CODE FOR A ACTION / MOVEMENT OF ROBOT WHEN BOTH LEFT & RIGHT SENSORS(OBSTACLE AVOIDANCE SENSORS) ARE TRIGGERED

 //  "0" MEANS OBSTACLE IS PRESENT & "1" MEANS NO OBSTACLE
 
//  if (left_sensor_status==0 && right_sensor_status==0){
//    Serial.println("1 Move Straight");
//    my_robot.MoveForward(40);
//  }

  if (left_sensor_status==0 && right_sensor_status==0)
  {
    // INSERT YOUR CODE HERE
    my_robot.MoveForward(straightSpeed);
  }
  else if(right_sensor_status==0)
  {
    // INSERT YOUR CODE HERE
    my_robot.CenterPivotLeft(leftSpeed);
  }
  else if(left_sensor_status==0)
  {
    // INSERT YOUR CODE HEREMoveTurnUpRight
    my_robot.CenterPivotRight(rightSpeed);
    
  }      
  else
  {
  // BELOW IS THE CODE FOR THE BOTTOM LINE FOLLOWING SENSORS ARE TRIGGERED  

  //  "0" MEANS OBSTACLE IS PRESENT & "1" MEANS NO OBSTACLE
    if(bottom_left_sensor_status==1 && bottom_right_sensor_status==0)
    {
      if (isGoingStraight)
      {
        if (isSpeedBoost)
        {
        my_robot.MoveForward(speedBoost);
        Serial.println("BOOOOST straiught");
        }
        else
        {
        my_robot.MoveForward(straightSpeed);
        Serial.println("no boost straiught");
        }
      }
      else if (isGoingRight)
      {
        //if (is180flipStatus != 2) {
          my_robot.MoveTurnUpRight(rightSpeed, angV);
        //}
        
      }
      else if (isGoingLeft)
      {
        //if (is180flipStatus != 2) {
        my_robot.MoveTurnUpLeft(leftSpeed, angV);
        //}
      }
      else if (is180ing)
      {
        my_robot.CenterPivotLeft(leftSpeed);
      }
      else 
      {
        my_robot.CenterPivotLeft(leftSpeed);
      }
    }
    else if(bottom_left_sensor_status==0 && bottom_right_sensor_status==1)
    {

      if (isGoingStraight)
      {
        if (isSpeedBoost)
        {
        my_robot.MoveForward(speedBoost);
        Serial.println("BOOOOST straiught");
        }
        else
        {
        my_robot.MoveForward(straightSpeed);
        Serial.println("no boost straiught");
        }
      }
      else if (isGoingLeft)
      {
        //if (is180flipStatus != 2) {
          my_robot.MoveTurnUpLeft(leftSpeed, angV);
        //}
      }
      else if (isGoingRight)
      {
        //if (is180flipStatus != 2) {
        my_robot.MoveTurnUpRight(rightSpeed, angV);
        //}
      }
      else if (is180ing)
      {
        my_robot.CenterPivotLeft(leftSpeed);
      }
      else 
      {
        my_robot.CenterPivotRight(rightSpeed);
      }
    }
    else
    {
      if (isGoingLeft){
        //if (is180flipStatus != 2) {
        my_robot.MoveTurnUpLeft(leftSpeed, angV);
        //}
      }
      else if (isGoingRight)
      {
        //if (is180flipStatus != 2) {
        my_robot.MoveTurnUpRight(rightSpeed, angV);
        //} 
      }
      else if (is180ing)
      {
        my_robot.CenterPivotLeft(leftSpeed);
      }
      else 
      {
        my_robot.MoveForward(straightSpeed);
      }
    }
  }
}