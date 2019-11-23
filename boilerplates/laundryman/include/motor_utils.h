//Benjamin Ahn

#include "vex.h"

using namespace vex;

void ForwardMotor(vex::motor m, int msec) {
  m.setVelocity(50, velocityUnits::pct);
  m.spin(directionType::fwd);
  task::sleep(msec);

  m.stop();
}

void ReverseMotor(vex::motor m, int msec) {
  m.setVelocity(50, velocityUnits::pct);
  m.spin(directionType::fwd);
  task::sleep(msec);

  m.stop();
}

//resets rotation before rotating. 
void LaundroControlHold(vex::motor* mlist, int len, int rot, rotationUnits unts, int velocity_percent, velocityUnits v_unts) {
  for(int i = 0; i < len - 1; i++) {
    mlist[i].resetRotation();
    mlist[i].rotateFor(rot, unts, velocity_percent, v_unts, false);
  }
  mlist[len - 1].rotateFor(rot, unts, velocity_percent, v_unts);
  
  for(int i = 0; i < len; i++){
    mlist[i].stop(brakeType :: hold);
  }
}

void LaundroHold(vex::motor* mlist, int len, int msec, int velocity_percent, vex::directionType direction) {
  for(int i = 0; i < len; i++) {
    mlist[i].setVelocity(velocity_percent, velocityUnits::pct);
    mlist[i].spin(direction);
  }

  task::sleep(msec);

  for(int i = 0; i < len; i++) {
    mlist[i].stop(brakeType::hold);
  }
}

void LaundroMat(vex::motor* mlist, int len, int msec, int velocity_percent, vex::directionType direction) {
  for (int i = 0; i < len; i++) {
    mlist[i].setVelocity(velocity_percent, velocityUnits::pct);
    mlist[i].spin(direction);
  }

  task::sleep(msec);

  for (int i = 0; i < len; i++) {
    mlist[i].stop();
  }
}

void LaudroLimit(vex::motor *mlist, int len, vex::limit lswitch, int velocity_percent, vex::directionType direction) {
  for (int i = 0; i < len; i++) {
    mlist[i].setVelocity(velocity_percent, velocityUnits::pct);
    mlist[i].spin(direction);
  }

  while (1 == 1) {
    if (lswitch.pressing()) {
      break;
    }
  }

  for (int i = 0; i < len; i++) {
    mlist[i].stop();
  }
}