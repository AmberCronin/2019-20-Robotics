#include "controller.h"

// @TODO:
// 1. Regular motor spinning
// 2. Reverse forebar
// 3. Conveyer belt

using namespace vex;

vex::brain      Brain;

//vex::motor      ReverseForebar1(PORT3, false);
//vex::motor      ReverseForebar2(PORT4, false);

vex::motor* motor_list;

vex::limit l1(Brain.ThreeWirePort.A);

vex::controller ctrl(vex::controllerType::primary);

vex::motor* AllocMotorList(int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return tmotor_list;
}

void initMotorList()
{
  motor_list = AllocMotorList(4);
  motor_list[0] = vex::motor(PORT1, false);
  motor_list[1] = vex::motor(PORT2, false);
}

int main() {
  initMotorList();
  //LaudroLimit(motor_list, 2, l1, 100, directionType::fwd);
  HandleInputs(ctrl, motor_list, 2);
  return 0;
}