/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Nov 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <esotils.h>

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::motor      LBMotor(vex::PORT4, false);   //
vex::motor      LFMotor(vex::PORT2, false);   //
vex::motor      RBMotor(vex::PORT3, true);    //
vex::motor      RFMotor(vex::PORT1, true);    //

vex::motor* arm_motors;
int arm_motors_len = 2;

vex::motor* claw_motors;
int claw_motors_len = 2;

vex::controller ctrl(vex::controllerType::primary);


void spinLeft(double pct)
{
  LBMotor.spin(directionType::fwd, pct, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, pct, velocityUnits::pct);
}
void spinRight(double pct)
{
  RBMotor.spin(directionType::fwd, pct, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, pct, velocityUnits::pct);
}
void stopDrive()
{
  spinLeft(0);
  spinRight(0);
}
void goRobit(int time)
{
  spinLeft(100);
  spinRight(100);
  task::sleep(time);
  stopDrive();
}
void revRobit(int time)
{
  spinLeft(-100);
  spinRight(-100);
  task::sleep(time);
  stopDrive();
}


vex::motor* AllocMotorList(vex::motor* list, int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor) * size);
  return tmotor_list;
}
void initArmMotorList() {
  arm_motors = AllocMotorList(arm_motors, arm_motors_len);
  arm_motors[0] = vex::motor(PORT6, false); //left side forward
  arm_motors[1] = vex::motor(PORT5, false); //right side reversed
}
void initClawMotorList() {
  claw_motors = AllocMotorList(claw_motors, claw_motors_len);
  claw_motors[0] = vex::motor(PORT8, false);
  claw_motors[1] = vex::motor(PORT7, true);
}

void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LBMotor.spin(directionType::rev, fwd + rot, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RBMotor.spin(directionType::rev, -(fwd - rot), velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

/*
bool checkInit()
{
  try
  {
    for(int i = 0; i < arm_motors_len; i++)
    {
      arm_motors[i].isSpinning();
    }
  }
  catch(int e)
  {
    return false;
  }
  return true;
}
*/

void pre_auton( void ) {
  initArmMotorList();
}


void autonomous( void ) {
  initArmMotorList();
  goRobit(3000);
  revRobit(2000);
}


void usercontrol( void ) {
    initArmMotorList();
    initClawMotorList();

  // User control code here, inside the loop
  bool r1Press = false;
  bool r2Press = false;
  bool l1Press = false;
  bool l2Press = false;
  
  double arm_velocity = 0.0;
  double diff = 2;

  while (1) {
    driveArcade(ctrl.Axis1, ctrl.Axis2);
  /*
    if(ctrl.ButtonR1.pressing() && !r1Press) {
      for(int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].setVelocity(100, velocityUnits::pct);
        arm_motors[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonR1.pressing() && r1Press) {
      for(int i = 0; i < arm_motors_len; i++) {
       arm_motors[i].stop(brakeType::hold);
      }
    }
    r1Press = ctrl.ButtonR1.pressing();
    */

    if(ctrl.ButtonR1.pressing()) {

      if(arm_velocity - diff < -100)
      {
        arm_velocity = -100;
      }
      else {
        arm_velocity -= diff;
      }
    }
    else if(ctrl.ButtonR2.pressing()) {
      if(arm_velocity + diff > 100)
      {
        arm_velocity = 100;
      }
      else {
        arm_velocity += diff;
      }
      
    }
    else {
      if(sign(arm_velocity) == 1)
      {
        if(arm_velocity - diff < 0)
        {
          arm_velocity = 0;
        }
        else {
          arm_velocity -= diff;
        }
      }
      else if(sign(arm_velocity) == -1)
      {
        if(arm_velocity + diff > 0)
        {
          arm_velocity = 0;
        }
        else {
          arm_velocity += diff;
        }
      }
    }
    for (int i = 0; i < arm_motors_len; i++) {
      // big increase here
      arm_motors[i].setVelocity(arm_velocity, velocityUnits::pct);
      arm_motors[i].spin(directionType::fwd);
    }
  /*
    for (int i = 0; i < arm_motors_len; i++) {
        // decay here
        for (arm_velocity; arm_velocity <= 0; arm_velocity-=0.02) {
          arm_motors[i].setVelocity(arm_velocity, velocityUnits::pct);
          arm_motors[i].spin(directionType::fwd);
        }
      }
      for(int i = 0; i < arm_motors_len; i++) {
       arm_motors[i].stop(brakeType::hold);
      }
*/
    if(ctrl.ButtonL1.pressing() && !l1Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].setVelocity(100, velocityUnits::pct);
        claw_motors[i].spin(directionType::fwd);
      }
    } else if(!ctrl.ButtonL1.pressing() && l1Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].stop(brakeType::brake);
      }
    }
    l1Press = ctrl.ButtonL1.pressing();

    if(ctrl.ButtonL2.pressing() && !l2Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].setVelocity(100, velocityUnits::pct);
        claw_motors[i].spin(directionType::rev);
      }
    } else if(!ctrl.ButtonL2.pressing() && l2Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].stop(brakeType::hold);
      }
    }
    l2Press = ctrl.ButtonL2.pressing();

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