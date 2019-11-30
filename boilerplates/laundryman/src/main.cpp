#include "controller.h"

// @TODO:
// 1. Regular motor spinning
// 2. Reverse forebar
// 3. Conveyer belt

using namespace vex;

vex::brain      Brain;

//vex::motor      ReverseForebar1(PORT3, false);
//vex::motor      ReverseForebar2(PORT4, false);

vex::motor* drive_motors;
vex::motor* arm_motors;

vex::limit lim1(Brain.ThreeWirePort.A);

vex::controller ctrl(vex::controllerType::primary);

vex::motor* AllocMotorList(vex::motor* list, int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor*) * size);
  return tmotor_list;
}

void initDriveMotorList()
{
  drive_motors = AllocMotorList(drive_motors, 5);
  drive_motors[0] = vex::motor(PORT1, false);
  drive_motors[1] = vex::motor(PORT2, true);
  drive_motors[2] = vex::motor(PORT6, false);
  drive_motors[3] = vex::motor(PORT7, true);
}
void initArmMotorList()
{
  arm_motors = AllocMotorList(arm_motors, 2);
  arm_motors[0] = vex::motor(PORT5, false);
  arm_motors[1] = vex::motor(PORT6, false);
}

int main() {
  initDriveMotorList();
  //LaudroLimit(drive_motors, 4, lim1, 100, directionType::fwd);
  HandleDriveInputs(ctrl, drive_motors, 4);
  return 0;
}