#include "drive.h"

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

void driveArcade(vex::controller::axis f, vex::controller::axis r) {
  double fwd = f.position();
  double rot = r.position();
  LBMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  LFMotor.spin(directionType::fwd, fwd + rot, velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -(fwd - rot), velocityUnits::pct);
}

void driveTank(vex::controller::axis l, vex::controller::axis r) {
  double left = l.position();
  double right = r.position();
  LFMotor.spin(directionType::fwd, left, velocityUnits::pct);
  LBMotor.spin(directionType::fwd, left, velocityUnits::pct);
  RFMotor.spin(directionType::fwd, -1 * right, velocityUnits::pct);
  RBMotor.spin(directionType::fwd, -1 * right, velocityUnits::pct);
}