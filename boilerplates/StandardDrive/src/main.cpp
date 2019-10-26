/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Sat Oct 26 2019                                           */
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

vex::controller ctrl(vex::controllerType::primary);


void driveArcade(vex::controller::axis f, vex::controller::axis r)
{
  double fwd = f.position();
  double rot = r.position();
  LFMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  LBMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}
void driveTank(vex::controller::axis l, vex::controller::axis r)
{
  double left = l.position();
  double right = r.position();
  LFMotor.spin(directionType::fwd, left, velocityUnits::pct);
  LBMotor.spin(directionType::fwd, left, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -1 * right, velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -1 * right, velocityUnits::pct);
}

int main() {
  while(1)
  {
    driveArcade(ctrl.Axis1, ctrl.Axis2);
    //driveTank(ctrl.Axis1, ctrl.Axis4);
  }
}
