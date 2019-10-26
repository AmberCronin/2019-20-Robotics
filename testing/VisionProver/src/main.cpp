/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\bcronin                                          */
/*    Created:      Sat Sep 07 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "divineVision.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor    spinny(vex::PORT1, true);

int minWidth = 50;


int main() {
  while (true) {
    seer.takeSnapshot(1);
    if (seer.largestObject.exists && seer.largestObject.width > minWidth) {
        Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::orange);
        Brain.Screen.drawRectangle(0,0, 480, 240);
        Brain.Screen.setCursor(2,6);
        Brain.Screen.setFont(vex::fontType::mono40);
        Brain.Screen.print("Orange cube aquired");
    }
    else  {
      seer.takeSnapshot(2);
      if (seer.largestObject.exists && seer.largestObject.width > minWidth) {
        Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::green);
        Brain.Screen.drawRectangle(0,0, 480, 240);
        Brain.Screen.setCursor(2,6);
        Brain.Screen.setFont(vex::fontType::mono40);
        Brain.Screen.print("Green cube aquired");
      }
    	else {
        seer.takeSnapshot(3);
        if (seer.largestObject.exists && seer.largestObject.width > minWidth) {
          Brain.Screen.setPenColor(vex::color::white);
          Brain.Screen.setFillColor(vex::color::purple);
          Brain.Screen.drawRectangle(0,0, 480, 240);
          Brain.Screen.setCursor(2,6);
          Brain.Screen.setFont(vex::fontType::mono40);
          Brain.Screen.print("Purple cube aquired");
        }
    	  else {
          Brain.Screen.clearScreen();
        }
      }
    }
    int numObj = 0;
    for(int i = 0; i < 3; i++)
    {
      seer.takeSnapshot(i);
      for(int j = 0; j < seer.objectCount; j++)
      {
        if(seer.objects[j].width > minWidth)
        {
          numObj++;
        }
      }
    }
    Brain.Screen.setCursor(4, 6);
    Brain.Screen.setFont(vex::fontType::mono15);
    Brain.Screen.print("%d%% objects in view", numObj);
    task::sleep(100);
  }

  /*
  visionSetup(seer);
  while(1) {
    Brain.Screen.clearScreen();
    int numObj = 0;
    Brain.Screen.printAt(1, 20, "Found %d%% objects", numObj);



    this_thread::sleep_for(10);
  }
  */
}