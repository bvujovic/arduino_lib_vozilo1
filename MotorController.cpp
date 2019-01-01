//B #include <iostream>

#include "MotorController.h"

MotorController::MotorController()
{
}

bool MotorController::Execute(VoziloKomande cmd, short speed)
{
	//B const short stateMaxAbs = 255;	// apsolutni maksimum stanja motora
	//B const short stateMinAbs = 45;	// apsolutni minimum - ispod ovog broja stanje se postavlja na 0
	const short stateMax = 235;  // maksimum stanja (za F ili B)
	const short stateMin = 60;   // minimum stanja (za F ili B)
	const short minStartL = 120; // minimum za start levog motora
	const short minStartR = 70;  // minimum za start desnog motora
								 //B const short maxSpeedDirCorrect = 15;	// maksimum korekcije pravca

								 // 1 - racunanje idealnog stanja za datu komandu
	if (cmd == Stop || (cmd != DirCorrect && -MotorStateMinAbs <= speed && speed <= MotorStateMinAbs))
	{
		stateML = stateMR = 0;
		return false;
	}

	short oldStateML = stateML;
	short oldStateMR = stateMR;

	if (cmd == DirCorrect)
	{
		if (speed > MotorMaxDirCorrect)
			speed = MotorMaxDirCorrect;
		if (speed < -MotorMaxDirCorrect)
			speed = -MotorMaxDirCorrect;
	}
	else
	{
		speed = abs(speed);
		if (speed > stateMax)
			speed = stateMax;
		if (speed > 0 && speed < stateMin)
			speed = stateMin; // (+40, +60) -> +60
	}

	if (cmd != DirCorrect)
		stateML = stateMR = speed;
	if (cmd == Forward)
	{
		stateML = abs(stateML);
		stateMR = abs(stateMR);
	}
	if (cmd == Backward)
	{
		stateML = -abs(stateML);
		stateMR = -abs(stateMR);
	}

	if (cmd == LeftTurn)
	{
		stateML = -abs(stateML);
		stateMR = abs(stateMR);
	}
	if (cmd == RightTurn)
	{
		stateML = abs(stateML);
		stateMR = -abs(stateMR);
	}

	if (cmd == DirCorrect)
	{
		stateML -= speed;
		stateMR += speed;
	}

	// 2 - da li je potrebna priprema
	//if (stateML * oldStateML < 0 || stateMR * oldStateMR < 0) // promena smera obrtanja motora
	//	return true;
	if ((abs(stateML) < abs(minStartL) && Sgn(stateML) != Sgn(oldStateML)) || (abs(stateMR) < abs(minStartR) && Sgn(stateMR) != Sgn(oldStateMR)))
	{
		stateML = MotorStateMaxAbs * Sgn(stateML);
		stateMR = MotorStateMaxAbs * Sgn(stateMR);
		return true;
	}

	struct SpeedCorrect
	{
		unsigned char speed;
		unsigned char correction;
	};
	const SpeedCorrect scs[] = { { stateMin, 15 },{ 80, 15 },{ 160, 21 },{ stateMax, 18 } };
	const short scsSize = sizeof(scs) / sizeof(SpeedCorrect);
	//B std::cout << sizeof(scs) << std::endl;

	// 3 - balansiranje
	if (cmd == Forward || cmd == Backward || cmd == LeftTurn || cmd == RightTurn)
	{

		for (short i = 0; i < scsSize; i++)
		{
			//B std::cout << speed << " - " << (short)scs[i].speed << std::endl;
			if (speed == scs[i].speed) // pronadjena je trazena brzina u tabeli
			{
				stateML += Sgn(stateML) * scs[i].correction;
				stateMR -= Sgn(stateMR) * scs[i].correction;
				break;
			}
			if (speed < scs[i].speed) // brzina je izmedju 2 vrednosti u tabeli
			{
				short sd = scs[i].speed - scs[i - 1].speed;
				short sx = speed - scs[i - 1].speed;
				short cd = scs[i].correction - scs[i - 1].correction;
				short c = Rnd(scs[i - 1].correction + (cd * sx / (float)sd));

				stateML += Sgn(stateML) * c;
				stateMR -= Sgn(stateMR) * c;
				break;
			}
		}
	}

	// 4 - provera da li tekuce vrednosti izlaze van okvira dozvoljenih
	RegulateStates();

	return false;
}

void MotorController::RegulateStates()
{
	if (stateML > MotorStateMaxAbs || stateML < -MotorStateMaxAbs)
	{
		short d = Abs(stateML) - Abs(MotorStateMaxAbs);
		stateML -= Sgn(stateML) * d;
		stateMR -= Sgn(stateML) * d;
	}
	if (-MotorStateMinAbs < stateMR && stateMR < MotorStateMinAbs)
	{
		short d = Abs(MotorStateMinAbs) - Abs(stateMR);
		stateML += Sgn(stateML) * d;
		stateMR += Sgn(stateML) * d;
	}
}
void MotorController::ChangePinENs(short dl, short dr)
{
	stateML += stateML > 0 ? dl : -dl;
	stateMR += stateMR > 0 ? dr : -dr;
	RegulateStates();
}
