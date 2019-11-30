#include "motor_utils.h"

void HandleInputs(vex::controller ctrl, vex::motor* mlist_arms, int len) {
  bool r1Press = false;
  bool r2Press = false;
  while(true)
  {
    if(ctrl.ButtonR1.pressing() && !r1Press) {
      for(int i = 0; i < len; i++) {
        mlist_arms[i].setVelocity(100, velocityUnits::pct);
        mlist_arms[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonR1.pressing() && r1Press) {
      for(int i = 0; i < len; i++) {
       mlist_arms[i].stop(brakeType::hold);
      }
    }
    r1Press = ctrl.ButtonR1.pressing();

    if(ctrl.ButtonR2.pressing() && !r2Press) {
      for(int i = 0; i < len; i++) {
        mlist_arms[i].setVelocity(100, velocityUnits::pct);
        mlist_arms[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonR2.pressing() && r2Press) {
      for(int i = 0; i < len; i++) {
       mlist_arms[i].stop(brakeType::hold);
      }
    }
    r2Press = ctrl.ButtonR2.pressing();
    task::sleep(10);
  }
}

void HandleDriveInputsArcade(vex::controller ctrl, vex::motor* mlist_drive, int len) {
  bool r1Pressed = false;
  while(true) {
    mlist_drive[2].spin(directionType::fwd, ctrl.Axis3.position() + ctrl.Axis4.position(), velocityUnits::pct);
    mlist_drive[3].spin(directionType::fwd, ctrl.Axis3.position() - ctrl.Axis4.position(), velocityUnits::pct);
    mlist_drive[1].spin(directionType::fwd, ctrl.Axis3.position() - ctrl.Axis4.position(), velocityUnits::pct);
    mlist_drive[0].spin(directionType::fwd, ctrl.Axis3.position() + ctrl.Axis4.position(), velocityUnits::pct);
    if (ctrl.ButtonR1.pressing() && r1Pressed == false) {
      r1Pressed = true;
      break;
    }
  }
}

void HandleDriveInputsTank(vex::controller ctrl, vex::motor* mlist_drive, int len) {
  bool r1Pressed = false;
  while (true) {
    mlist_drive[0].spin(directionType::fwd, ctrl.Axis3.position(), velocityUnits::pct);
    mlist_drive[1].spin(directionType::fwd, ctrl.Axis2.position(), velocityUnits::pct);
    mlist_drive[2].spin(directionType::fwd, ctrl.Axis3.position(), velocityUnits::pct);
    mlist_drive[3].spin(directionType::fwd, ctrl.Axis2.position(), velocityUnits::pct);
    if (ctrl.ButtonR1.pressing() && r1Pressed == false) {
      r1Pressed = true;
      break;
    }
  }
}

void HandleDriveInputs(vex::controller ctrl, vex::motor* mlist_drive, int len) {
  while (true) {
    HandleDriveInputsArcade(ctrl, mlist_drive, len);
    this_thread::sleep_for(std::chrono::milliseconds(500));
    HandleDriveInputsTank(ctrl, mlist_drive, len);
    this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}