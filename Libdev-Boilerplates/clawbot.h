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
	ArmsNClaw(std::vector<Motor> arm_motors, Motor l_claw_motor, Motor r_claw_motor);
	void MoveArms(double dt, double velocity_goal, vex::directionType direction);
	void MoveClaws(double dt, double velocity_goal, vex::directionType direction);
	void UpdateArmsNClaw();
}

#endif // CLAWBOT_H_FILE