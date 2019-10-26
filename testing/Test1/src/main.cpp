/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Sep 06 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

void runMotor(vex::motor, int, double, brakeType);

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor       TestMotor(vex::PORT1, true);

vex::controller  ctrl(vex::controllerType::primary);

void runMotor(vex::motor m, int timeMS, double velPct, brakeType bT = brakeType::brake)
{
  m.setVelocity(velPct, percentUnits::pct);
  m.spin(directionType::fwd);
  task::sleep(timeMS);
  m.stop(bT);
}

int p = 5;

int main() {
  while(1)
  {

    if(ctrl.ButtonL1.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("L1 pressed");
    }
    if(ctrl.ButtonL2.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("L2 pressed");
    }
    if(ctrl.ButtonR1.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("R1 pressed");
    }
    if(ctrl.ButtonR2.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("R2 pressed");
    }
    if(ctrl.ButtonUp.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Up pressed");
    }
    if(ctrl.ButtonDown.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Down pressed");
    }
    if(ctrl.ButtonLeft.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Left pressed");
    }
    if(ctrl.ButtonRight.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Right pressed");
    }
    if(ctrl.ButtonX.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("X pressed");
    }
    if(ctrl.ButtonB.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("B pressed");
    }
    if(ctrl.ButtonY.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Y pressed");
    }
    if(ctrl.ButtonA.pressing())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("A pressed");
    }
    if(ctrl.Axis1.position())
    {
      Brain.Screen.setCursor(4, 6);
      Brain.Screen.print("Axis1 position");
    }
    if(ctrl.Axis2.position())
    {
      Brain.Screen.setCursor(4,6);
      Brain.Screen.print("Axis2 position");
    }
    if(ctrl.Axis3.position())
    {
      Brain.Screen.setCursor(4,6);
      Brain.Screen.print("Axis3 position");
    }
    if(ctrl.Axis4.position())
    {
      Brain.Screen.setCursor(4,6);
      Brain.Screen.print("Axis4 positon");
    }
    ctrl.Screen.setCursor(0, 0);
    ctrl.Screen.print("hellothere");
    
    task::sleep(100);
    //ctrl.rumble('-...');

  }
}

