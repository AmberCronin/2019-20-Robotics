/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Fri Nov 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Including the vex header file and our custom helper utils
#include "vex.h"
#include "esotils.h"

//gives us access to vex.h
using namespace vex;

//constants for acceleration and better driving
#define DT 10  // this is the constant we use for acceleration

#define WHEEL_D 4
#define PI 3.142069f


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::motor      LBMotor(vex::PORT4, false);   //left back motor
vex::motor      LFMotor(vex::PORT2, false);   //left front motor
vex::motor      RBMotor(vex::PORT3, true);    //right back motor
vex::motor      RFMotor(vex::PORT1, true);    //right front motor

//declares lists of motors for easier handling of hardware changes
//these are initialized at the beginning of each auton and drive periods
vex::motor* arm_motors;
int arm_motors_len = 2;

vex::motor* claw_motors;
int claw_motors_len = 2;

//velocity goals for the arm
double arm_motor_velocity;
double arm_motor_velocity_goal;

//declares controller
vex::controller ctrl(vex::controllerType::primary);

//acceleration function (used by all)
double Approach(double current, double goal, double dt) {
    double difference = goal - current; //calculates the diff

	//returns an increase or decrease of the current value based on the goal
	//uses dt as the difference, typically the DT defined at the beginning of the file
    if (difference > dt) {
        return current + dt;
    } if (difference < -dt) {
        return current-dt;
    }
    return goal;
}

//~~~~~~~~~~~~~~~~~~~\\LOW LEVEL MOVEMENT//~~~~~~~~~~~~~~~~~~~\\

//claw and arm movement functions
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

//~~~~~~~~~~~~~~~~~~~\\MID LEVEL MOVEMENT//~~~~~~~~~~~~~~~~~~~\\

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

//~~~~~~~~~~~~~~~~~~~\\HIGH LEVEL MOVEMENT//~~~~~~~~~~~~~~~~~~~\\


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


//~~~~~~~~~~~~~~~~~~~\\BIG BRAIN LEVEL MOVEMENT//~~~~~~~~~~~~~~~~~~~\\


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

//~~~~~~~~~~~~~~~~~~~\\GALAXY BRAIN LEVEL MOVEMENT//~~~~~~~~~~~~~~~~~~~\\


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



//~~~~~~~~~~~~~~~~\\MOTOR LIST DECLARATIONS//~~~~~~~~~~~~~~~~~~~\\


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


//~~~~~~~~~~~~~~~~~~~\\HIGH LEVEL DRIVE//~~~~~~~~~~~~~~~~~~~\\



void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LBMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}
void UpdateArmVelocity(vex::motor* arm_motors_, double dt, directionType direction) {
    // ramp up velocity
    arm_motor_velocity = Approach(arm_motor_velocity, arm_motor_velocity_goal, dt);

    // set motor velocity
    for (int i = 0; i < arm_motors_len; i++) {
      arm_motors_[i].setVelocity(arm_motor_velocity, velocityUnits::pct);
      arm_motors_[i].spin(direction);
    }
}


// actual code stuff now
void pre_auton( void ) {
  initArmMotorList();//initialize these lists like 10 times, can never be too sure
  initClawMotorList();
}

void initializeAuton() {
  initArmMotorList();
  initClawMotorList();
  //basic auton set up
  //raises arm, sets up claw, lowers arm
  goArm(-50, 500);
  goClaw(100, 350);
  goArm(50, 500);
  brakeClaw(-100, 250);
}

//jake seal of approval
void auton() {
  //robot initialization
  initializeAuton();

  driveBackwards(15, true); //places loaded cube in the bin
  goRobit(-50, 50, 125); //shifts robot slightly to the left to get away from the wall
  brakeDrive();//brakes drive to hold robot and remove uncertainies
  driveForward(25);//drives forward to the next cube
  brakeArm(-50, 500);//raises arm for turning
  goRobit(-75, 75, 800);//turn robot to the left, getting into position for the next cube
  brakeDrive();//stops drive again
  goArm(50, 600);//lowers arm around cube
  driveForward(8, true, 50); //getting into position for grabbing the cube
  driveForward(4, true, 25); //also getting into position, but slower
  brakeClaw(50, 250); //grabbing the cube
  brakeArm(-50, 1000); //lift cube up for mobility
  driveBackwards(13, true, 50);//jerk backwards a little bit to put the cube away
  goRobit(-75, 75, 500);//turns robot to the left more, facing cube bin
  brakeDrive();//stops again lmao
  driveForward(30);//lets get this cube in the bin now
  goArm(50, 750);//lowers arm to dunk on the haters
  goRobit(-75, 75, 250);//turns to the left to knock first cube to the side
  driveForward(4);//moves forward a little bit more
  goClaw(-100, 250);//opens claw, dropping cube
  driveBackwards(6);//gtfood
}
//basic auton, not used
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


//user control stuff yay
void usercontrol( void ) {
	//damn danial, back at it again with the initizliation
    initArmMotorList();
    initClawMotorList();

  // User control code here, inside the loop
  
  // permanent fields for longterm memory
  bool r1Press = false;
  bool r2Press = false;
  bool l1Press = false;
  bool l2Press = false;
  
  directionType direction = directionType::fwd;

  //repeat foreverrrrrr
  while (1) {
	//drives forward/backward with axis 1, drives left/right with axis 2
    driveArcade(ctrl.Axis1, ctrl.Axis2);
    // ARM MOTOR STUFF

	//controls arm movement, implementing acceleration
    if(ctrl.ButtonR1.pressing()) {
      arm_motor_velocity_goal = -100.0;
      direction = directionType::fwd;
    } else if(ctrl.ButtonR2.pressing()) {
		//wanna go all the way
      arm_motor_velocity_goal = -100.0;
      direction = directionType::rev;
    } else {
		//if nothings being pressed
      arm_motor_velocity_goal = 0.0;
      for (int i = 0; i < arm_motors_len; i++) {
        arm_motors[i].stop(brakeType::hold);//brakes the motors
      }
    }
	//this actually sends the speeds to the arm motors
    UpdateArmVelocity(arm_motors, DT, direction);

    // DON'T DELETE! CLAW MOTOR CODE STUFF HERE
	//similar to UpdateArmVelocity, but implemented here because we don't need acceleration for the claw
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