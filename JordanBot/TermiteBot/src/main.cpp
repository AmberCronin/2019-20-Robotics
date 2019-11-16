/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Nov 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
//#include "controller.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor      LMotor(vex::PORT16, false);
vex::motor      RMotor(vex::PORT20, true);

vex::motor* arm_motors;
int arm_motors_len = 2;

vex::motor* claw_motors;
int claw_len = 2;

vex::controller ctrl(vex::controllerType::primary);

vex::motor* AllocMotorList(vex::motor* list, int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return tmotor_list;
}
void initArmMotorList() {
  arm_motors = AllocMotorList(arm_motors, arm_motors_len);
  arm_motors[0] = vex::motor(PORT11, false); //left side forward
  arm_motors[1] = vex::motor(PORT12, true); //right side reversed
}
void initClawMotorList() {
  claw_motors = AllocMotorList(claw_motors, claw_len);
  claw_motors[0] = vex::motor(PORT5, false);
  claw_motors[1] = vex::motor(PORT2, false);
}

void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

int main() {
  initArmMotorList();
  initClawMotorList();

  bool r1Press = false;
  bool r2Press = false;
  bool l1Press = false;
  bool l2Press = false;

  for(int i = 0; i < arm_motors_len; i++) {
    arm_motors[i].resetRotation();
  }

  while(1) {
    driveArcade(ctrl.Axis4, ctrl.Axis3);

    if(ctrl.ButtonL2.pressing() && !l2Press) {
      for(int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].setVelocity(50, velocityUnits::pct);
        arm_motors[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonL2.pressing() && l2Press) {
      for(int i = 0; i < arm_motors_len; i++) {
       arm_motors[i].stop(brakeType::hold);
      }
    }
    l2Press = ctrl.ButtonL2.pressing();

    if(ctrl.ButtonL1.pressing() && !l1Press) {
      for(int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].setVelocity(100, velocityUnits::pct);
        arm_motors[i].spin(directionType::rev);
      }
    } else if (!ctrl.ButtonL1.pressing() && l1Press) {
      for(int i = 0; i < arm_motors_len; i++) {
       arm_motors[i].stop(brakeType::hold);
      }
    }
    l1Press = ctrl.ButtonL1.pressing();

    if(ctrl.ButtonR2.pressing() && !r2Press) {
      claw_motors[0].setVelocity(50, velocityUnits::pct);
      claw_motors[1].setVelocity(100, velocityUnits::pct);
      claw_motors[0].spin(directionType::fwd);
      claw_motors[1].spin(directionType::fwd);
    } else if(!ctrl.ButtonR2.pressing() && r2Press) {
      claw_motors[0].stop(brakeType::hold);
      claw_motors[1].stop(brakeType::hold);
    }
    r2Press = ctrl.ButtonR2.pressing();

    if(ctrl.ButtonR1.pressing() && !r1Press) {
      claw_motors[0].setVelocity(50, velocityUnits::pct);
      claw_motors[1].setVelocity(100, velocityUnits::pct);
      claw_motors[0].spin(directionType::rev);
      claw_motors[1].spin(directionType::rev);
    } else if(!ctrl.ButtonR1.pressing() && r1Press) {
      claw_motors[0].stop(brakeType::hold);
      claw_motors[1].stop(brakeType::hold);
    }
    r1Press = ctrl.ButtonR1.pressing();

    task::sleep(20);
  }
}