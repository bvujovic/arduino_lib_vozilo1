#ifndef VOZILO_H
#define VOZILO_H

#include "Impuls.h"

const int SwSerSpeed = 9600;
// const int SwSerSpeed = 38400;

enum VoziloKomande
{
	// komunikacija ESP <-> Arduino
	Stop = 0, CmdOk = -1, CmdError = -2, GetImpulses = -3,

	// test komande
	MotorTest = -4,

	// smer vozila
	Forward = 1, RightTurn = 2, Backward = 3, LeftTurn = 4, DirCorrect = 5 //B, SteerWheel = 6

};

enum Motors
{
	MotorLeft, // init: 120, min: 70
	MotorRight, // init: 70, min: 50
	MotorsBoth, MotorsNone
};

VoziloKomande CmdConvert(String s);
String CmdConvert(VoziloKomande cmd);

#endif