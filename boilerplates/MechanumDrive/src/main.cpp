/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Sep 27 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::motor    LFMotor(vex::PORT1, false);
vex::motor    LBMotor(vex::PORT2, false);
vex::motor    RFMotor(vex::PORT3, true);
vex::motor    RBMotor(vex::PORT4, true);

vex::controller  ctrl(vex::controllerType::primary);
// define your global instances of motors and other devices here


void driveMech(vex::controller::axis f, vex::controller::axis r, vex::controller::axis s)
{
  /*
  void holoSteer(int fb, int strafe, int rot) { //fb = forward/back motion
    motor[flWheel] = fb + strafe + rot;
    motor[blWheel] = fb - strafe + rot;
    motor[brWheel] = -(fb + strafe - rot);
    motor[frWheel] = -(fb - strafe - rot);
  }
  */
  
  double fwd = f.position();
  double rot = r.position();
  double stf = s.position();
  LFMotor.spin(directionType::fwd, fwd + rot + stf, velocityUnits::pct);
  LBMotor.spin(directionType::fwd, fwd + rot - stf, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot + stf), velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot - stf), velocityUnits::pct);
}

int main()
{
  while(1)
  {
    driveMech(ctrl.Axis1, ctrl.Axis2, ctrl.Axis4);
  }
}
