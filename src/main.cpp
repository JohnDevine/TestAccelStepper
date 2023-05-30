/*
This tests the stepper (28YBJ-48 and ULN2003)
It also tests the switch bounce library
*/
// Manual & Info here:
// http://www.airspayce.com/mikem/arduino/AccelStepper/
// https://hackaday.io/project/183279-accelstepper-the-missing-manual
// https://hackaday.io/project/183713-using-the-arduino-accelstepper-library

// In1 = Pin D33
// In2 = Pin D32
// In3 = Pin D27
// In4 = Pin D26
// Switch = Pin D19

#include <JDGlobal.h>
#include <MyStepper.h>
#include <elapsedMillis.h>
#include <Bounce2.h>

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::FULL4WIRE, 33, 27, 32, 26); // NOTE!!! Pin order for ULN2003 driver board is IN1, IN3, IN2, IN4

elapsedMillis printTime; // Keep track of print time

Bounce bounce = Bounce(); // Instantiate a Bounce object

#define kDoOneRevolution 2048             // 4096 steps per revolution for 28BYJ-48 NOT true
#define kTargetSteps kDoOneRevolution * 3 // 3 revolutions
#define kMaxSpeed 500                     // Maximum speed in steps per second

void setup()
{
    Serial.begin(115200);

    stepper1.setMaxSpeed(kMaxSpeed); // Set the maximum speed in steps per second
    stepper1.setAcceleration(50);    // Acceleration in steps per second per second

    // initialize the pushbutton pin as an pull-up input
    // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
    bounce.attach(PIN_D19, INPUT_PULLUP); // USE INTERNAL PULL-UP
    bounce.interval(5);                   // interval in ms

    // stepper1.setSpeed(300); // use this if using constant speed

    stepper1.moveTo(kTargetSteps); // Move to 3 revolutions
}

void loop()
{

    bounce.update(); // Update the Bounce instance (YOU MUST DO THIS EVERY LOOP)

    // <Bounce>.changed() RETURNS true IF THE STATE CHANGED (FROM HIGH TO LOW OR LOW TO HIGH)
    if (bounce.fell())
    {

        if (bounce.fell())
        {
            Serial.println("switch fell");
        }
        if (bounce.rose())
        {
            Serial.println("switch rose");
        }

        if (stepper1.distanceToGo() != 0)
        {
            stepper1.stop(); // stop if not at the end
            stepper1.moveTo(0);
        }
        else
        {
            if (stepper1.currentPosition() == 0)
                stepper1.moveTo(kTargetSteps);
            else
            {
                if (stepper1.currentPosition() > 0)
                    stepper1.moveTo(-kTargetSteps);
                else
                    stepper1.moveTo(kTargetSteps);
            }
        }
    }

    if (printTime >= 1000)
    {
        printTime = 0;
        float mSpeed = stepper1.speed();
        Serial.print(mSpeed);
        Serial.print(" ");
        Serial.print(stepper1.distanceToGo());
        Serial.print(" ");
        Serial.print(stepper1.currentPosition());
        Serial.print(" ");
        Serial.println(stepper1.targetPosition());
    }

    if (stepper1.distanceToGo() != 0)
    {
        TRACE();
        stepper1.enableOutputs(); // turn on power to the motor
    }

    stepper1.run();

    if (stepper1.distanceToGo() == 0)
    {
        TRACE();
        stepper1.disableOutputs(); // turn off power to the motor
    }
}