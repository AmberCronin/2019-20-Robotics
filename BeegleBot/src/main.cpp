/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Sun Nov 10 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
//#include "controller.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor      LMotor(vex::PORT1, false);
vex::motor      RMotor(vex::PORT2, true);

vex::motor* arm_motors;
int arm_motors_len = 2;

vex::motor      claw(vex::PORT5, false);

vex::controller ctrl(vex::controllerType::primary);

vex::motor* AllocMotorList(vex::motor* list, int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return tmotor_list;
}
void initArmMotorList() {
  arm_motors = AllocMotorList(arm_motors, arm_motors_len);
  arm_motors[0] = vex::motor(PORT3, false); //left side forward
  arm_motors[1] = vex::motor(PORT4, true); //right side reversed
}

void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

int main() {
  initArmMotorList();

  bool r1Press = false;
  bool r2Press = false;
  bool l1Press = false;
  bool l2Press = false;

  while(1) {
    driveArcade(ctrl.Axis1, ctrl.Axis2);

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

    if(ctrl.ButtonR2.pressing() && !r2Press) {
      for(int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].setVelocity(100, velocityUnits::pct);
        arm_motors[i].spin(directionType::rev);
      }
    } else if (!ctrl.ButtonR2.pressing() && r2Press) {
      for(int i = 0; i < arm_motors_len; i++) {
       arm_motors[i].stop(brakeType::hold);
      }
    }
    r2Press = ctrl.ButtonR2.pressing();

    if(ctrl.ButtonL2.pressing() && !l1Press) {
      claw.setVelocity(100, velocityUnits::pct);
      claw.spin(directionType::fwd);
    } else if(!ctrl.ButtonL1.pressing() && l1Press) {
      claw.stop(brakeType::hold);
    }
    
    if(ctrl.ButtonL2.pressing() && !l2Press) {
      claw.setVelocity(100, velocityUnits::pct);
      claw.spin(directionType::rev);
    } else if(!ctrl.ButtonL2.pressing() && l2Press) {
      claw.stop(brakeType::hold);
    }

    task::sleep(10);
  }
}
