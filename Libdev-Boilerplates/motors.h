#ifndef MOTORS_H_FILE
#define MOTORS_H_FILE

#include "vex.h"

using namespace vex;

double Approach(double current, double goal, double dt);

class Motor {
private:
	vex::motor m;
	double velocity;
	double velocity_goal;
	double dt;

	// for driving
	double wheel_circumference;
	double wheel_gear_ratio;
public:
	// Constructor/setup functions
	Motor(vex::motor m, double wheel_circumference, double wheel_gear_ratio, double wheel_turning_diameter);

	// Raw Velocity Increase/Driving
	void ChangeVelocity(double dt, double velocity_goal, vex::directionType direction);
	void UpdateVelocity();
	void Brake();

	// Controlled driving
	void DriveControlled(double inches);
}

#endif // MOTORS_H_FILE