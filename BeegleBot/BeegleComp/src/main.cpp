/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Nov 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "esotils.h"

using namespace vex;

#define DT 10  // this is the constant we use for acceleration

#define WHEEL_D 4
#define PI 3.142069f


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::motor      LBMotor(vex::PORT4, false);   //
vex::motor      LFMotor(vex::PORT2, false);   //
vex::motor      RBMotor(vex::PORT3, true);    //
vex::motor      RFMotor(vex::PORT1, true);    //

vex::motor* arm_motors;
int arm_motors_len = 2;

vex::motor* claw_motors;
int claw_motors_len = 2;

double arm_motor_velocity;
double arm_motor_velocity_goal;

vex::controller ctrl(vex::controllerType::primary);

double Approach(double current, double goal, double dt) {
    double difference = goal - current;

    if (difference > dt) {
        return current + dt;
    } if (difference < -dt) {
        return current-dt;
    }
    return goal;
}

void moveClaw(double pct)
{
  for(int i = 0; i < claw_motors_len; i++)
  {
    claw_motors[i].spin(directionType::fwd, pct, velocityUnits::pct);
  }
}
void moveArm(double pct)
{
  for(int i = 0; i < arm_motors_len; i++)
  {
    arm_motors[i].spin(directionType::fwd, pct, velocityUnits::pct);
  }
}
void spinLeft(double pct)
{
  LBMotor.spin(directionType::fwd, pct, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, pct, velocityUnits::pct);
}
void spinRight(double pct)
{
  RBMotor.spin(directionType::fwd, pct, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, pct, velocityUnits::pct);
}
void stopDrive()
{
  spinLeft(0);
  spinRight(0);
}
void goRobit(int time)
{
  spinLeft(100);
  spinRight(100);
  task::sleep(time);
  stopDrive();
}
void revRobit(int time)
{
  spinLeft(-100);
  spinRight(-100);
  task::sleep(time);
  stopDrive();
}
void goRobit(double lpwr, double rpwr, int time)
{
  spinLeft(lpwr);
  spinRight(rpwr);
  task::sleep(time);
  stopDrive();
}
void goArm(double pwr, int time)
{
  moveArm(pwr);
  task::sleep(time);
  moveArm(0);
}
void brakeArm(double pwr, int time)
{
  goArm(pwr, time);
  for(int i = 0; i < arm_motors_len; i++)
  {
    arm_motors[i].stop(brakeType::hold);
  }
}
void goClaw(double pwr, int time)
{
  moveClaw(pwr);
  task::sleep(time);
  moveClaw(0);
}
void brakeClaw(double pwr, int time)
{
  goClaw(pwr, time);
  for(int i = 0; i < claw_motors_len; i++)
  {
    claw_motors[i].stop(brakeType::hold);
  }
}


void resetRDriveEnc() {
  RBMotor.resetRotation();
  RFMotor.resetRotation();
}
void resetLDriveEnc() {
  LBMotor.resetRotation();
  LFMotor.resetRotation();
}
void resetDriveEnc() {
  resetRDriveEnc();
  resetLDriveEnc();
}
void setLDrivePwr(double pwr) {
  LBMotor.setVelocity(pwr, velocityUnits::pct);
  LFMotor.setVelocity(pwr, velocityUnits::pct);
}
void setRDrivePwr(double pwr) {
  RBMotor.setVelocity(pwr, velocityUnits::pct);
  RFMotor.setVelocity(pwr, velocityUnits::pct);
}
void setDrivePwr(double pwr) {
  setLDrivePwr(pwr);
  setRDrivePwr(pwr);
}

void brakeDrive() {
  LBMotor.stop(brakeType::brake);
  LFMotor.stop(brakeType::brake);
  RBMotor.stop(brakeType::brake);
  RFMotor.stop(brakeType::brake);
}

//advanced movement time
void driveForward(float inches, bool coast = false, double pwr = 75) {
  float wheelCirc = WHEEL_D * PI;
  float rots = inches / wheelCirc;
  resetDriveEnc();
  LBMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  LFMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RBMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RFMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, true);
  if(!coast)
    brakeDrive();
}
void driveBackwards(float inches, bool coast = false, double pwr = 75) {
  float wheelCirc = WHEEL_D * PI;
  float rots = inches / wheelCirc * (-1);
  resetDriveEnc();
  LBMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  LFMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RBMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RFMotor.rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, true);
  if(!coast)
    brakeDrive();
}




vex::motor* AllocMotorList(vex::motor* list, int size) {
  vex::motor* tmotor_list = (vex::motor*)malloc(sizeof(vex::motor) * size);
  return tmotor_list;
}
void initArmMotorList() {
  arm_motors = AllocMotorList(arm_motors, arm_motors_len);
  arm_motors[0] = vex::motor(PORT6, false); //left side forward
  arm_motors[1] = vex::motor(PORT5, false); //right side reversed
}
void initClawMotorList() {
  claw_motors = AllocMotorList(claw_motors, claw_motors_len);
  claw_motors[0] = vex::motor(PORT8, false);
  claw_motors[1] = vex::motor(PORT7, true);
}

void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LBMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

void pre_auton( void ) {
  initArmMotorList();
  initClawMotorList();
}

void initializeAuton() {
  initArmMotorList();
  initClawMotorList();
  goArm(-50, 500);
  goClaw(100, 350);
  goArm(50, 500);
  brakeClaw(-100, 250);

}

void auton() {
  //robot initialization
  initializeAuton();

  driveBackwards(15, true);
  goRobit(-50, 50, 125);
  brakeDrive();
  driveForward(25);
  brakeArm(-50, 500);
  goRobit(-75, 75, 800);
  brakeDrive();
  goArm(50, 600);
  driveForward(8, true, 50); //getting into position for grabbing the cube
  driveForward(4, true, 25);
  brakeClaw(50, 250); //grabbing the cube
  brakeArm(-50, 1000); //lift cube up for mobility
  driveBackwards(10, true, 50);
  goRobit(-75, 75, 600);
  brakeDrive();
  driveForward(30);
  goArm(50, 750);
  goRobit(-75, 75, 100);
  driveForward(4);
  goClaw(-100, 250);
  driveBackwards(6);
}

void autonBasic()
{
  initArmMotorList();
  initClawMotorList();
  goArm(-50, 500);
  goClaw(100, 350);
  goArm(50, 500);
  revRobit(1750);
  goRobit(500);
}

void autonomous( void ) {
  auton();
}

/*
void Character::Update(double dt) {
    // ramp up velocity
    velocity_x = Approach(velocity_x, velocity_x_goal, dt*CHARACTER_DT_MULTIPLIER);
    velocity_y = Approach(velocity_y, velocity_y_goal, dt*CHARACTER_DT_MULTIPLIER);

    // update position
    player_world_pos.x += velocity_x;
    player_world_pos.y += velocity_y;

}
*/

void UpdateArmVelocity(vex::motor* arm_motors_, double dt, directionType direction) {
    // ramp up velocity
    arm_motor_velocity = Approach(arm_motor_velocity, arm_motor_velocity_goal, dt);

    // set motor velocity
    for (int i = 0; i < arm_motors_len; i++) {
      arm_motors_[i].setVelocity(arm_motor_velocity, velocityUnits::pct);
      arm_motors_[i].spin(direction);
    }
}

void usercontrol( void ) {
    initArmMotorList();
    initClawMotorList();

  // User control code here, inside the loop
  bool r1Press = false;
  bool r2Press = false;
  bool l1Press = false;
  bool l2Press = false;
  
  directionType direction;

  while (1) {
    driveArcade(ctrl.Axis1, ctrl.Axis2);
    // ARM MOTOR STUFF


    if(ctrl.ButtonR1.pressing()) {
      arm_motor_velocity_goal = -100.0;
      direction = directionType::fwd;
    } else if(ctrl.ButtonR2.pressing()) {
      arm_motor_velocity_goal = -100.0;
      direction = directionType::rev;
    } else {
      arm_motor_velocity_goal = 0.0;
      for (int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].stop(brakeType::hold);
      }
    }

    UpdateArmVelocity(arm_motors, DT, direction);

    // DON'T DELETE! CLAW MOTOR CODE STUFF HERE
    if(ctrl.ButtonL1.pressing() && !l1Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].setVelocity(100, velocityUnits::pct);
        claw_motors[i].spin(directionType::fwd);
      }
    } else if(!ctrl.ButtonL1.pressing() && l1Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].stop(brakeType::brake);
      }
    }
    l1Press = ctrl.ButtonL1.pressing();

    if(ctrl.ButtonL2.pressing() && !l2Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].setVelocity(100, velocityUnits::pct);
        claw_motors[i].spin(directionType::rev);
      }
    } else if(!ctrl.ButtonL2.pressing() && l2Press) {
      for(int i = 0; i < claw_motors_len; i++) {
        claw_motors[i].stop(brakeType::hold);
      }
    }
    l2Press = ctrl.ButtonL2.pressing();

    //auton button do not press
    if(ctrl.ButtonA.pressing() && ctrl.ButtonRight.pressing())
    {
      auton();
    }


    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}