#ifndef MOTRCTRL_H
#define MOTRCTRL_H

#include "Vozilo.h"

const short MotorStateMaxAbs = 255;		// apsolutni maksimum stanja motora
const short MotorStateMinAbs = 45;		// apsolutni minimum - ispod ovog broja stanje se postavlja na 0
const short MotorMinSpeedL = 70;		// minimum za brzinu levog motora
const short MotorMinSpeedR = 50;		// minimum za brzinu desnog motora
const short MotorMaxDirCorrect = 15;	// maksimum korekcije pravca

class MotorController
{
private:
	// stanja levog i desnog motora
	// 0 - mirovanje, +200 veoma brzo unapred, -80 sporo unazad,...
	short stateML = 0;
	short stateMR = 0;

	// da li se motori automatski balansiraju (u kodu Execute metode)
	bool isAutoBalanced = true;

	// stavlja u dozvoljene okvire stanja motora, <255 i sl provere i ispravke
	void RegulateStates();

public:
	static short Abs(short x) { return x > 0 ? x : -x; }
	static short Sgn(short x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }
	static short Rnd(float d) { return d + 0.5F; }

	MotorController();

	bool IsAutoBalanced() { return isAutoBalanced; }
	void SetAutoBalanced(bool ab) { isAutoBalanced = ab; }

	// Metoda izvrsava komandu i vraca info o tome da li je potrebna priprema (kratak i jak impuls na motorima).
	bool Execute(VoziloKomande cmd, short speed);

	short GetPinL1() { return stateML > 0; }
	short GetPinL2() { return stateML < 0; }
	short GetPinLEN() { return Abs(stateML); }
	short GetPinR1() { return stateMR > 0; }
	short GetPinR2() { return stateMR < 0; }
	short GetPinREN() { return Abs(stateMR); }

	void ChangePinENs(short dl, short dr);
};

#endif