#include "vex.h"
#include <thread>
#include <string>
#include <stdio.h>
#include <chrono>
#include <mutex>
#include <vector>

// @TODO:
// 1. Regular motor spinning
// 2. Reverse forebar
// 3. Conveyer belt

using namespace vex;

vex::brain      Brain;

vex::motor      ReverseForebar1(PORT3, false);
vex::motor      ReverseForebar2(PORT4, false);



vex::motor* motor_list;


vex::motor* AllocMotorList(int size) {
  vex::motor* motor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return motor_list;
}

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

void initMotorArray()
{
  motor_list = AllocMotorList(4);
  motor_list[0] = vex::motor(PORT1, false);
  motor_list[1] = vex::motor(PORT2, false);
  motor_list[2] = vex::motor(PORT3, false);
  motor_list[3] = vex::motor(PORT4, false);
}

int main() {
  initMotorArray();
  LaundroMat(motor_list, 4, 2000);
  return 0;
}
