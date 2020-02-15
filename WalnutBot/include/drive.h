#ifndef DRIVE_H_FILE
#define DRIVE_H_FILE

#include <vector>
#include "vex.h"

#include "utils.h"

/*
// define your global instances of motors and other devices like this
vex::motor      LBMotor(vex::PORT4, false);   //
vex::motor      LFMotor(vex::PORT2, false);   //
vex::motor      RBMotor(vex::PORT3, true);    //
vex::motor      RFMotor(vex::PORT1, true);    //
*/

typedef struct wheel_data {
  double wheel_circumference;
  double wheel_gear_ratio;
  double wheel_turning_diameter;
} WheelData;

using namespace vex;

double Approach(double current, double goal, double dt);

class Drive {
private:
	vex::motor* LBMotor;
	vex::motor* LFMotor;
	vex::motor* RBMotor;
	vex::motor* RFMotor;
  WheelData wheel_data;
public:
	void InitDrive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor, WheelData wheel_data);
  void DriveArcade(vex::controller::axis f, vex::controller::axis r);
	void DriveTank(vex::controller::axis l, vex::controller::axis r);
  void DriveForward(float inches, bool coast = false, double pwr = 75);
  void DriveBackwards(float inches, bool coast = false, double pwr = 75);
  void Turn(float degrees, double pwr = 75);
};

void Drive::InitDrive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor, WheelData wheel_data) {
	this->LBMotor = &lb_motor;
	this->LFMotor = &lf_motor;
	this->RBMotor = &rb_motor;
	this->RFMotor = &rf_motor;
}

void Drive::DriveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LBMotor->spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  LFMotor->spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RBMotor->spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
  RFMotor->spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

void Drive::DriveTank(vex::controller::axis l, vex::controller::axis r) {
  double left = l.position();
  double right = r.position();
  LFMotor->spin(directionType::fwd, left, velocityUnits::pct);
  LBMotor->spin(directionType::fwd, left, velocityUnits::pct);
  RFMotor->spin(directionType::fwd, -1 * right, velocityUnits::pct);
  RBMotor->spin(directionType::fwd, -1 * right, velocityUnits::pct);
}

void Drive::DriveForward(float inches, bool coast, double pwr) {
  float wheelCirc =  this->wheel_data.wheel_circumference * PI;
  float rots = inches / wheelCirc;
  //resetDriveEnc();
  LBMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  LFMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RBMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RFMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, true);
  if(!coast) {
    LBMotor->stop(vex::brakeType::hold);
    LFMotor->stop(vex::brakeType::hold);
    RBMotor->stop(vex::brakeType::hold);
    RFMotor->stop(vex::brakeType::hold);
  }
}

void Drive::DriveBackwards(float inches, bool coast, double pwr) {
  float wheelCirc =  this->wheel_data.wheel_circumference * PI;
  float rots = inches / wheelCirc * (-1);
  //resetDriveEnc();
  LBMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  LFMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RBMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, false);
  RFMotor->rotateFor(rots, rotationUnits::rev, pwr, velocityUnits::pct, true);
  if(!coast) {
    LBMotor->stop(vex::brakeType::hold);
    LFMotor->stop(vex::brakeType::hold);
    RBMotor->stop(vex::brakeType::hold);
    RFMotor->stop(vex::brakeType::hold);
  }
}


// WARNING: untested
void Drive::Turn(float degrees, double pwr) {
  // Note: +90 degrees is a right turn
    float turningRatio = this->wheel_data.wheel_turning_diameter / (this->wheel_data.wheel_circumference / PI);
    float wheelDegrees = turningRatio * degrees;    
    // Divide by two because each wheel provides half the rotation
    LBMotor->startRotateFor(
        wheelDegrees * this->wheel_data.wheel_gear_ratio / 2, vex::rotationUnits::deg, 
        pwr, vex::velocityUnits::pct
    );
    LFMotor->startRotateFor(
      wheelDegrees * this->wheel_data.wheel_gear_ratio / 2, vex::rotationUnits::deg, 
        pwr, vex::velocityUnits::pct
    );
    RBMotor->startRotateFor(
        wheelDegrees * this->wheel_data.wheel_gear_ratio / 2, vex::rotationUnits::deg,
        pwr * -1, vex::velocityUnits::pct
    );
    RFMotor->rotateFor(
      wheelDegrees * this->wheel_data.wheel_gear_ratio / 2, vex::rotationUnits::deg,
        pwr * -1, vex::velocityUnits::pct
    );
}

#endif // DRIVE_H_FILE