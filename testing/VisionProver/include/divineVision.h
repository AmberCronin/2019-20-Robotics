/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature ANNOYING_ORANGE = vex::vision::signature (1, 6783, 8327, 7554, -2495, -1789, -2142, 3, 0);
vex::vision::signature SEASICK_SAILOR = vex::vision::signature (2, -7873, -5631, -6752, -3485, -1739, -2612, 4.5, 0);
vex::vision::signature MAGESTIC_ROBES = vex::vision::signature (3, 763, 2101, 1432, 8097, 12779, 10438, 1.7, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision seer = vex::vision (vex::PORT2, 50, ANNOYING_ORANGE, SEASICK_SAILOR, MAGESTIC_ROBES, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/