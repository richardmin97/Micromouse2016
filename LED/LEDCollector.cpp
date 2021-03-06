#include "LED/LEDCollector.h"
#include "PINS/pinouts.h"

LEDCollector::LEDCollector()
{
    // Controller for IR receivers
    AnalogIn IR_left_back(IR_LEFT_BACK);
    AnalogIn IR_left_front(IR_LEFT_FRONT);
    AnalogIn IR_right_front(IR_RIGHT_FRONT);
    AnalogIn IR_right_back(IR_RIGHT_BACK);
    
    // Controller for IR emitters
    DigitalOut IR_left_back_pwr(IR_LEFT_BACK_PWR);
    DigitalOut IR_left_front_pwr(IR_LEFT_FRONT_PWR);
    DigitalOut IR_right_front_pwr(IR_RIGHT_FRONT_PWR);
    DigitalOut IR_right_back_pwr(IR_RIGHT_BACK_PWR);
    
    leftForwardLED = 0;
    rightForwardLED = 0;
    leftBackLED = 0;
    rightBackLED = 0;

    initialLeftForwardLED = 0;
    initialRightForwardLED = 0;
    initialLeftBackLED = 0;
    initialRightBackLED = 0;

    currHistPosition = 0;
    
    IR_left_front_pwr = 1;
    for(int i = 0; i < LED_ON_TIME; i++)
    {
        initialLeftForwardLED += IR_left_front.read()*1000;
    }
    IR_left_front_pwr = 0;
    
    IR_right_front_pwr = 1;
    for(int i = 0; i < LED_ON_TIME; i++)
    {
        initialRightForwardLED += IR_right_front.read()*1000;
    }
    IR_right_front_pwr = 0;

    IR_left_back_pwr = 1;
    for(int i = 0; i < LED_ON_TIME; i++)
    {
        initialLeftBackLED += IR_left_back.read()*1000;
    }
    IR_left_back_pwr = 0;

    IR_right_front_pwr = 1;
    for(int i = 0; i < LED_ON_TIME; i++)
    {
        initialRightBackLED += IR_right_back.read()*1000;
    }
    IR_right_front_pwr = 0;

    initialRightBackLED /= LED_ON_TIME;
    initialRightForwardLED /= LED_ON_TIME;
    initialLeftBackLED /= LED_ON_TIME;
    initialRightBackLED /= LED_ON_TIME;

    for(int i = 0; i < LED_HIST_SIZE; i++)
    {
        leftForwardLEDHistory[i] = 0;
        leftBackLEDHistory[i] = 0;
        rightForwardLEDHistory[i] = 0;
        rightBackLEDHistory[i] = 0;
    }
}


void LEDCollector::pollLEDs(int milliseconds)
{
    // Controller for IR receivers
    AnalogIn IR_left_back(IR_LEFT_BACK);
    AnalogIn IR_left_front(IR_LEFT_FRONT);
    AnalogIn IR_right_front(IR_RIGHT_FRONT);
    AnalogIn IR_right_back(IR_RIGHT_BACK);
    
    // Controller for IR emitters
    DigitalOut IR_left_back_pwr(IR_LEFT_BACK_PWR);
    DigitalOut IR_left_front_pwr(IR_LEFT_FRONT_PWR);
    DigitalOut IR_right_front_pwr(IR_RIGHT_FRONT_PWR);
    DigitalOut IR_right_back_pwr(IR_RIGHT_BACK_PWR);
    
    leftForwardLED = 0;
    rightForwardLED = 0;
    leftBackLED = 0;
    rightBackLED = 0;

    IR_left_front_pwr = 1;
    for(int i = 0; i < milliseconds; i++)
    {
        leftForwardLED += IR_left_front.read()*1000;
    }
    IR_left_front_pwr = 0;
    
    IR_right_front_pwr = 1;
    for(int i = 0; i < milliseconds; i++)
    {
        rightForwardLED += IR_right_front.read()*1000;
    }
    IR_right_front_pwr = 0;

    IR_left_back_pwr = 1;
    for(int i = 0; i < milliseconds; i++)
    {
        leftBackLED += IR_left_back.read()*1000;
    }
    IR_left_back_pwr = 0;

    IR_right_front_pwr = 1;
    for(int i = 0; i < milliseconds; i++)
    {
        rightBackLED += IR_right_back.read()*1000;
    }
    IR_right_front_pwr = 0;


    
    leftForwardLEDHistory[currHistPosition] = leftForwardLED / milliseconds;
    leftBackLEDHistory[currHistPosition] = leftBackLED / milliseconds;
    rightForwardLEDHistory[currHistPosition] = rightForwardLED / milliseconds;
    rightBackLEDHistory[currHistPosition] = rightBackLED / milliseconds;

    currHistPosition++;

    if(currHistPosition >= LED_HIST_SIZE)
        currHistPosition = 0;
    
    // detectWallChanges();
}


void LEDCollector::detectWallChanges()
{
    //analyze the LED History, seeing if the walls are changing.
    //This is one way of formatively creating the walls of the maze; the other way would be to monitor our location
    //and check if there's a wall each time we enter another square.
    //In fact it's probably simpler to implement it that way.
    //This method provides the small speed benefit of immediately knowing when the walls are changing patterns. 
    //However, it does take more memory
    
}

bool LEDCollector::wallInFront()
{
    printf("wall in front: %f %f\r\n", leftForwardLED, rightForwardLED);
    return (leftForwardLED >= WALL_IN_FRONT_LEFT || rightForwardLED >= WALL_IN_FRONT_RIGHT);
}

bool LEDCollector::wallToLeft()
{
    printf("wall in left: %f\r\n", leftBackLED);
    return (leftBackLED >= WALL_TO_LEFT);
}

bool LEDCollector::wallToRight()
{
    printf("wall in right: %f\r\n", rightBackLED);
    return (rightBackLED >= WALL_TO_RIGHT);
}
