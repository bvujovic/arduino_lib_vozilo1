//B #include "stdafx.h"
#include "MotorAutoDirCorrect.h"

MotorAutoDirCorrect::MotorAutoDirCorrect() {}

void MotorAutoDirCorrect::NewCommand(VoziloKomande cmd)
{
	if (cmd == Forward || cmd == Backward || cmd == LeftTurn || cmd == RightTurn)
	{
		lastCmd = cmd;
		sumOIL = sumOIR = 0;
	}
	else
		lastCmd = Stop;
}

void MotorAutoDirCorrect::NewOIs(ushort oil, ushort oir)
{
	if (IsCorrecting())
	{
		sumOIL += lastOIL = oil;
		sumOIR += lastOIR = oir;
	}
}

void MotorAutoDirCorrect::ComputeCorrections()
{
	if (IsCorrecting())
	{
		short d = GetSumOIdiff() / 4 + GetLastOIdiff();
		dl = -(dr = 4 * d); //TODO menjati koef ispred d da bi se dobili najbolji rezultati
	}
	else
		dl = dr = 0;
}
