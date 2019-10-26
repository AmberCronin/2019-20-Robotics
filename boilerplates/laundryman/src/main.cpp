#include "vex.h"
#include "motor_utils.h"

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
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return tmotor_list;
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
