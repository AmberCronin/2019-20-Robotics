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
vex::controller ctrl(vex::controllerType::primary);

vex::motor    LFMotor(vex::PORT1, false);
vex::motor    LBMotor(vex::PORT2, false);
vex::motor    RFMotor(vex::PORT3, true);
vex::motor    RBMotor(vex::PORT4, true);

void driveMech(vex::controller::axis f, vex::controller::axis r, vex::controller::axis s)
{
  double fwd = f.position();
  double rot = r.position();
  double stf = s.position();
  LFMotor.spin(directionType::fwd, fwd + rot + stf, velocityUnits::pct);
  LBMotor.spin(directionType::fwd, fwd + rot - stf, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot + stf), velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot - stf), velocityUnits::pct);
}


int main() {
   
    while(1) {
        driveMech(ctrl.Axis3, ctrl.Axis1, )
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
