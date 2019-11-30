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

//len is assumed to be 2
//do not change
//static code relies on two motors on each side
//easily adaptable to one motor, check for another function where len is set to 1
int rLastReq = 0;
int lLastReq = 0;
int rLastVel = 0;
int lLastVel = 0;
double dPosp = 0.5;

void AccHandleDriveInArc(vex::controller ctrl, vex::controller::axis mov, vex::controller::axis rot, vex::motor* l_drive, vex::motor* r_drive, int len = 2)
{
  int rReq = mov.position() - rot.position();
  int lReq = mov.position() + rot.position();
  int rCurrVel = rLastVel + dPosp * sign(rLastVel - rReq);
  for(int i = 0; i < len; i++) {
    r_drive[i].spin(directionType::fwd, rCurrVel, velocityUnits::pct);
  }
  int lCurrVel = lLastVel + dPosp * sign(lLastVel - lReq);
  for(int i = 0; i < len; i++) {
    l_drive[i].spin(directionType::fwd, lCurrVel, velocityUnits::pct);
  }
  rLastVel = rCurrVel;
  lLastVel = lCurrVel;
}

void HandleDriveInputsArcade(vex::controller ctrl, vex::controller::axis mov, vex::controller::axis rot, vex::motor* mlist_drive, int len) {
  bool r1Pressed = false;
  while(true) {
    mlist_drive[2].spin(directionType::fwd, mov.position() + rot.position(), velocityUnits::pct);
    mlist_drive[3].spin(directionType::fwd, mov.position() - rot.position(), velocityUnits::pct);
    mlist_drive[1].spin(directionType::fwd, mov.position() - rot.position(), velocityUnits::pct);
    mlist_drive[0].spin(directionType::fwd, mov.position() + rot.position(), velocityUnits::pct);
    if (ctrl.ButtonR1.pressing() && r1Pressed == false) {
      r1Pressed = true;
      break;
    }
    task::sleep(10);
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
    task::sleep(10);
  }
}

void HandleDriveInputs(vex::controller ctrl, vex::motor* mlist_drive, int len) {
  while (true) {
    //HandleDriveInputsArcade(ctrl, mlist_drive, len);
    this_thread::sleep_for(std::chrono::milliseconds(500));
    HandleDriveInputsTank(ctrl, mlist_drive, len);
    this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}