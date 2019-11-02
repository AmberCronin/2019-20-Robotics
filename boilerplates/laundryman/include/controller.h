#include "motor_utils.h"

void HandleInputs(vex::controller ctrl, vex::motor* mlist_arms, int len) {
  bool r1Press = false;
  bool r2Press = false;
  while(true)
  {
    if(ctrl.ButtonR1.pressing() && !r1Press) {
      for(int i = 0; i < len; i++) {
        mlist_arms[i].setVelocity(100, velocityUnits::pct);
        mlist_arms[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonR1.pressing() && r1Press) {
      for(int i = 0; i < len; i++) {
       mlist_arms[i].stop(brakeType::hold);
      }
    }
    r1Press = ctrl.ButtonR1.pressing();

    if(ctrl.ButtonR2.pressing() && !r2Press) {
      for(int i = 0; i < len; i++) {
        mlist_arms[i].setVelocity(100, velocityUnits::pct);
        mlist_arms[i].spin(directionType::fwd);
      }
    } else if (!ctrl.ButtonR2.pressing() && r2Press) {
      for(int i = 0; i < len; i++) {
       mlist_arms[i].stop(brakeType::hold);
      }
    }
    r2Press = ctrl.ButtonR2.pressing();
    task::sleep(10);
  }
}