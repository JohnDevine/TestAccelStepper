#ifndef MY_STEPPER_H
#define MY_STEPPER_H
// Manual & Info here: 
// http://www.airspayce.com/mikem/arduino/AccelStepper/ 
// https://hackaday.io/project/183279-accelstepper-the-missing-manual
// https://hackaday.io/project/183713-using-the-arduino-accelstepper-library
// http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html

/*  Simple how to:

// Includes
#include <JDGlobal.h>
#include <MyStepper.h>

// Define some steppers and the pins that they will use
// NOTE!!!!!!  The order of the pins here is IN1, IN3, IN2, IN4 for the ULN2003 driver board
AccelStepper stepper1(AccelStepper::FULL4WIRE, 33, 32, 27, 26); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

// Set the speed in steps per second: I have found a maximum of 300 steps per second works 
// well for my stepper motor (28BYJ-48) and driver board (ULN2003) on Doit ESP32 V1.0 DevKit
    stepper1.setMaxSpeed(300.0);

// Tell the stepper to move to 4096 steps x 3 (3 revolutions. There are 4096 steps to a 
// revolution for 28BYJ-48
    stepper1.moveTo(4096 * 3); // Move to 3 revolutions

// In the main loop you can now call the run() function on each stepper.This will move each motor one step 
// and check if it is time to accelerate or decelerate. It has to be in the loop so that it can keep 
// checking if there is anymore steps to do.
    stepper1.run();

 // Other functions
    run() // Poll the motor and step it if a step is due, implementing accelerations and decelerations to 
                // acheive the target position. You must call this as frequently as possible, but at least once 
                // per step interval, for the smoothest motion. Note that each call to run() will make at most 
                // one step, and then only when a step is due, based on the current speed and the time since 
                // the last step.

    runSpeed() // Poll the motor and step it if a step is due, implementing a constant speed as set 
                // by the most recent call to setSpeed(). 
                // You must call this as frequently as possible, but at least once per step interval,
               
    runSpeedToPosition() // Executes runSpeed() unless the targetPosition is reached. This function 
                // needs to be called often just like runSpeed() or run(). Will step the motor if a step is 
                // required at the currently selected speed unless the target position has been reached. 
                // Does not implement accelerations.

    runToPosition()  //Moves the motor (with acceleration/deceleration) to the new target 
                // position and blocks until it is at position. 
                // Dont use this in event loops, since it blocks.

    runToNewPosition(long 	position)	// Moves the motor (with acceleration/deceleration) to the 
                // new target position and blocks until it is at position. 
                // Dont use this in event loops, since it blocks.



    moveTo(newPosition) // Set a new target position that causes the stepper to stop with a 
                // speed profile 

    virtual void    disableOutputs();
                /// Disable motor pin outputs by setting them all LOW
                /// Depending on the design of your electronics this may turn off
                /// the power to the motor coils, saving power.
                /// This is useful to support Arduino low power modes: disable the outputs
                /// during sleep and then reenable with enableOutputs() before stepping
                /// again.
                /// If the enable Pin is defined, sets it to OUTPUT mode and clears the pin to disabled.
    
    virtual void    enableOutputs();
                /// Enable motor pin outputs by setting the motor pins to OUTPUT
                /// mode. Called automatically by the constructor.
                /// If the enable Pin is defined, sets it to OUTPUT mode and sets the pin to enabled.
                
            
*/

#include <JDGlobal.h>
#include <AccelStepper.h>

#endif // MY_STEPPER_H