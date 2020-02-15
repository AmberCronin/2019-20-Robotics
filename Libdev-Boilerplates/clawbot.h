#ifndef CLAWBOT_H_FILE
#define CLAWBOT_H_FILE

#include <vector>
#include "motors.h"
#include "vex.h"

using namespace vex;

//NOTE: Left claw motor goes in fwd direction, while
// right claw motor goes in rev direction
class ArmsNClaw {
private:
	// declarations of motors
	std::vector<Motor> arm_motors;
	Motor l_claw_motor;
	Motor r_claw_motor;
public:
	void InitArmsNClaw(std::vector<Motor> arm_motors, Motor l_claw_motor, Motor r_claw_motor);
	void MoveArms(double dt, double velocity_goal, vex::directionType direction);
	void MoveClaws(double dt, double velocity_goal, vex::directionType direction);
	void UpdateArmsNClaw();
};

void ArmsNClaw::InitArmsNClaw(std::vector<Motor> arm_motors, Motor l_claw_motor, Motor r_claw_motor) {
	this->arm_motors = arm_motors;
	this->l_claw_motor = l_claw_motor;
	this->r_claw_motor = r_claw_motor;
}

void ArmsNClaw::MoveArms(double dt, double velocity_goal, vex::directionType direction) {
	for (int i = 0; i < this->arm_motors.size(); ++i) {
		this->arm_motors[i].ChangeVelocity(dt, velocity_goal, direction);
	}
}

void ArmsNClaw::MoveClaws(double dt, double velocity_goal, vex::directionType direction) {
	l_claw_motor.ChangeVelocity(dt, velocity_goal, directionType::fwd);
	r_claw_motor.ChangeVelocity(dt, velocity_goal, directionType::rev);
}

void ArmsNClaw::UpdateArmsNClaw() {
	this->l_claw_motor.UpdateVelocity();
	this->r_claw_motor.UpdateVelocity();

	for (int i = 0; i < this->arm_motors.size(); ++i) {
		this->arm_motors[i].UpdateVelocity();
	}
}

#endif // CLAWBOT_H_FILE