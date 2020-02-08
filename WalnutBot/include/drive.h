#ifndef DRIVE_H_FILE
#define DRIVE_H_FILE

#include <vector>
#include "vex.h"

/*
// define your global instances of motors and other devices like this
vex::motor      LBMotor(vex::PORT4, false);   //
vex::motor      LFMotor(vex::PORT2, false);   //
vex::motor      RBMotor(vex::PORT3, true);    //
vex::motor      RFMotor(vex::PORT1, true);    //
*/

using namespace vex;

double Approach(double current, double goal, double dt);

class Drive {
private:
	vex::motor* LBMotor;
	vex::motor* LFMotor;
	vex::motor* RBMotor;
	vex::motor* RFMotor;
public:
	void InitDrive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor);
	void DriveArcade(vex::controller::axis f, vex::controller::axis r);
	void DriveTank(vex::controller::axis l, vex::controller::axis r);
};

void Drive::InitDrive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor) {
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

#endif // DRIVE_H_FILE