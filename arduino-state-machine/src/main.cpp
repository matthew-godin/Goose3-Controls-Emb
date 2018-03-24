//Simple test code to test the Arduino State Machine on an Arduino Mega 2560
#include "Cosa/RTT.hh"
#include "Cosa/OutputPin.hh"

OutputPin ledPin(Board::LED);

void setup() 
{
	RTT::begin();
	ArduinoMachine* myMachine = new ArduinoMachine;
}

void loop() 
{
    ledPin.on();
    delay(50);
    ledPin.off();
    delay(500);
}
