#ifndef MOTORS_H_FILE
#define MOTORS_H_FILE

#include "vex.h"

using namespace vex;

double Approach(double current, double goal, double dt) {
    double difference = goal - current;

    if (difference > dt) {
        return current + dt;
    } if (difference < -dt) {
        return current-dt;
    }
    return goal;
}

class Motor {
private:
	vex::motor* m;
	double velocity;
	double velocity_goal;
	double dt;
  vex::directionType direction;


	// for driving
	double wheel_circumference;
	double wheel_gear_ratio;
  double wheel_turning_diameter;
public:
	// Constructor/setup functions
	void InitMotor(vex::motor m, double wheel_circumference, double wheel_gear_ratio, double wheel_turning_diameter);

	// Raw Velocity Increase/Driving
	void ChangeVelocity(double dt, double velocity_goal, vex::directionType direction);
	void UpdateVelocity();
	void Brake();

	// Controlled driving
	void DriveControlled(double inches);
};

void Motor::InitMotor(vex::motor m, double wheel_circumference, double wheel_gear_ratio, double wheel_turning_diameter) {
	this->m = &m;
	this->wheel_circumference = wheel_circumference;
	this->wheel_gear_ratio = wheel_gear_ratio;
	this->wheel_turning_diameter = wheel_turning_diameter;
  this->velocity_goal = 0;
  this->velocity = 0;
}

void Motor::ChangeVelocity(double dt, double velocity_goal, vex::directionType direction) {
	this->dt = dt;
	this->velocity_goal = velocity_goal;
	this->direction = direction;
}

void Motor::UpdateVelocity() {
	// ramp up velocity
	this->velocity = Approach(this->velocity, this->velocity_goal, this->dt);

	// set the motor velocity
	this->m->setVelocity(this->velocity, velocityUnits::pct);
	this->m->spin(this->direction);
}

void Motor::Brake() {
  this->velocity_goal = 0;
  this->velocity = 0;
  this->m->setVelocity(0, vex::velocityUnits::pct);
	this->m->stop(vex::brakeType::hold);
}

void Motor::DriveControlled(double inches) {
	float inchesPerDegree = this->wheel_circumference / 360;
    float degrees = inches / inchesPerDegree;
    // startRotate doesn't wait for completion
    // this way, the other wheel can turn at same time
    this->m->startRotateFor(
        degrees * this->wheel_gear_ratio, vex::rotationUnits::deg, 
        100, vex::velocityUnits::pct
    );

/* From: http://medium.com/thefloatingpoint/autonomous-driving-tutorial-for-vex-v5-robots-774703ca2d3c
    RightMotor.rotateFor(
        degrees * GEAR_RATIO, vex::rotationUnits::deg,
        AUTON_DRIVE_PCT, vex::velocityUnits::pct
    );
*/
}

#endif // MOTORS_H_FILE