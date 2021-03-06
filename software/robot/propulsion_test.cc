#include <iostream>

#include "logging.h"
#include "robot.h"
#include "delay.h"

stopwatch idp::logging::logging_stopwatch;

int main(int argc, char* argv[]) {
  idp::logging::log_init();
  idp::Robot r;
  
  IDP_INFO << "Loading constants." << std::endl;
  
  r.load_constants();
  
  IDP_INFO << "Done loading constants." << std::endl;

  if (!r.initialise()) {
    IDP_ERR << "Unable to connect to robot. Exiting." << std::endl;
    return -1;
  }

  try {
    r.configure();
  }
  catch (idp::Robot::LinkError& e) {
    //IDP_ERR << "First configuration failed. Exiting." << std::endl;
    //return -1;
  }

  try {
    r.test();
  }
  catch (idp::Robot::LinkError& e) {
    IDP_ERR << "Preliminary test failed. Exiting." << std::endl;
    return -1;
  }


  try {
    IDP_INFO << "Moving at cruise speed for 1 metre." << std::endl;
    r.move(idp::Robot::MotorDemand(r._constants.cruise_speed, r._constants.cruise_speed), 1);
    r.move(idp::Robot::MotorDemand(0,0));
	
  /*
	IDP_INFO << "Rotating 90 degrees anticlockwise." << std::endl;
	r.turn(M_PI/2);
	
	delay(2000);
	
	IDP_INFO << "Rotating 90 degrees clockwise." << std::endl;
	r.turn(-M_PI/2);
	
	IDP_INFO << "Reversing at maximum speed for 10 seconds." << std::endl;
    r.move(idp::Robot::MotorDemand(-r._constants.max_speed_l, -r._constants.max_speed_l));
    delay(10000);  // delay 10 seconds
  */
	r.move(idp::Robot::MotorDemand(0,0));
  }
  catch (idp::Robot::LinkError& e) {
    // Something's gone wrong with the link.  
    if (!r.reinitialise()) {
      IDP_ERR << "Could not recover from link error. Exiting." << std::endl;
      return -1;
    }
    try {
      r.configure();
    }
    catch (idp::Robot::LinkError& e) {
      IDP_ERR << "Could not recover from link error. Exiting." << std::endl;
      return -1;
    }
  }

  return 0;
}
