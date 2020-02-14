/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Thu Feb 06 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "drive.h"
#include "motors.h"
#include "clawbot.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;
vex::controller ctrl(vex::controllerType::primary);


#define FULLFWD 100
#define FULLBAK -100
#define DT_G 10.0




void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

void auton() {
  
}

void autonomous( void ) {
  auton();
}

void usercontrol( void ) {
  // drive motor declarations
  vex::motor LFMotor(PORT2);
  vex::motor LBMotor(PORT9);
  vex::motor RFMotor(PORT11, true);
  vex::motor RBMotor(PORT19, true);
  Drive drive;
  drive.InitDrive(LBMotor, LFMotor, RBMotor, RFMotor);

  // Ramp push and arm motor declarations
  vex::motor ramp_push_motor(PORT12);
  Motor ramp_push;
  ramp_push.InitMotor(ramp_push_motor, 0.0, 0.0, 0.0);
  vex::motor arm_motor(PORT5);
  Motor arm;
  arm.InitMotor(arm_motor, 0.0, 0.0, 0.0);

  // Ramp intake motor declaration
  vex::motor left_conveyer_motor(PORT8);
  vex::motor right_conveyer_motor(PORT18, true);
  Motor left_conveyer;
  left_conveyer.InitMotor(left_conveyer_motor, 0, 0, 0);
  Motor right_conveyer;
  right_conveyer.InitMotor(right_conveyer_motor, 0, 0, 0);

  while (1) {
    // handle driving
    drive.DriveArcade(ctrl.Axis4, ctrl.Axis3);

    // handle ramp push and arm
    if (ctrl.ButtonA.pressing()) {
      ramp_push.ChangeVelocity(DT_G, FULLFWD, vex::directionType::fwd);
    } else if (ctrl.ButtonB.pressing()) {
      ramp_push.ChangeVelocity(DT_G, FULLBAK, vex::directionType::fwd);
    } else {
      ramp_push.Brake();
    }
    //arm movement
    if(ctrl.ButtonL1.pressing()) {
      arm.ChangeVelocity(DT_G, FULLFWD, vex::directionType::fwd);
    } else if (ctrl.ButtonL2.pressing()) {
      arm.ChangeVelocity(DT_G, FULLBAK, vex::directionType::fwd);
    } else {
      arm.Brake();
    }

    // handle ramp intake
    if (ctrl.ButtonR1.pressing()) {
      left_conveyer.ChangeVelocity(DT_G, FULLFWD, vex::directionType::fwd);
      right_conveyer.ChangeVelocity(DT_G, FULLFWD, vex::directionType::fwd);
    } else if (ctrl.ButtonR2.pressing()) {
      left_conveyer.ChangeVelocity(DT_G, FULLBAK, vex::directionType::fwd);
      right_conveyer.ChangeVelocity(DT_G, FULLBAK, vex::directionType::fwd);
    } else {
      left_conveyer.Brake(true);
      right_conveyer.Brake(true);
    }

    // update velocities here
    ramp_push.UpdateVelocity();
    arm.UpdateVelocity();
    left_conveyer.UpdateVelocity();
    right_conveyer.UpdateVelocity();
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}