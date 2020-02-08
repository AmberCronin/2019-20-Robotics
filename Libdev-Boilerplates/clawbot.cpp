#include "clawbot.h"

ArmsNClaw(std::vector<Motor> arm_motors, Motor l_claw_motor, Motor r_claw_motor) {
	this->arm_motors = arm_motors;
	this->l_claw_motor = l_claw_motor;
	this->r_claw_motor = r_claw_motor;
}

void MoveArms(double dt, double velocity_goal, vex::directionType direction) {
	for (size_t i = 0; i < this->arm_motors; ++i) {
		this->arm_motors[i].ChangeVelocity(dt, velocity_goal, direction);
	}
}

void MoveClaws(double dt, double velocity_goal, vex::directionType direction) {
	l_claw_motor.ChangeVelocity(dt, velocity_goal, directionType::fwd);
	r_claw_motor.ChangeVelocity(dt, velocity_goal, directionType::rev);
}

void UpdateArmsNClaw() {
	this->l_claw_motor.UpdateVelocity();
	this->r_claw_motor.UpdateVelocity();

	for (size_t i = 0; i < this->arm_motors; ++i) {
		this->arm_motors[i].UpdateVelocity();
	}
}