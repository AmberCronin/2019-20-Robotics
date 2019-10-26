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

void LaundroMat(vex::motor* mlist, int len, int msec) {
  for (int i = 0; i < len; i++) {
    mlist[i].setVelocity(100, velocityUnits::pct);
    mlist[i].spin(directionType::fwd);
  }

  task::sleep(msec);

  for (int i = 0; i < len; i++) {
    mlist[i].stop();
  }
}