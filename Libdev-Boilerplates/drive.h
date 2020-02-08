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
	vex::motor LBMotor;
	vex::motor LFMotor;
	vex::motor RBMotor;
	vex::motor RFMotor;
public:
	Drive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor);
	DriveArcade(vex::controller::axis f, vex::controller::axis r);
	DriveTank(vex::controller::axis l, vex::controller::axis r);
}

Drive::Drive(vex::motor lb_motor, vex::motor lf_motor, vex::motor rb_motor, vex::motor rf_motor) {
	this->LBMotor = lb_motor;
	this->LFMotor = lf_motor;
	this->RBMotor = rb_motor;
	this->RFMotor = rf_motor;
}

#endif // DRIVE_H_FILE