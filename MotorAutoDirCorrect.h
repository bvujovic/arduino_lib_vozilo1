#ifndef MOTAUTOCTRL_H
#define MOTAUTOCTRL_H

#include "MotorController.h"

typedef unsigned short ushort;

class MotorAutoDirCorrect
{
private:
	// ukljucena auto korekcija balansa motora ili ne
	bool _on = false;
	// poslednja komanda (koja je od znacaja za ovu klasu: F/B/TL/TR; Stop predstavlja sve ostale komande)
	VoziloKomande lastCmd = Stop;
	// suma tikova levog i desnog OptoInteraptera
	ushort sumOIL = 0, sumOIR = 0;
	// poslednji tikovi levog i desnog OptoInteraptera
	ushort lastOIL = 0, lastOIR = 0;
	// izracunate izmene nivoa na levom i desnom motoru
	short dl = 0, dr = 0;

public:
	MotorAutoDirCorrect();

	bool IsOn() { return _on; }
	void IsOn(bool on) { _on = on; }
	bool IsCorrecting() { return _on && lastCmd != Stop; }

	void NewCommand(VoziloKomande cmd);
	void NewOIs(ushort oil, ushort oir);

	void ComputeCorrections();
	short GetDL() { return dl; }
	short GetDR() { return dr; }

	short GetSumOIdiff() { return sumOIL - sumOIR; }
	short GetLastOIdiff() { return lastOIL - lastOIR; }
	bool IsSumLastDiffSigns() { return GetSumOIdiff() > 0 && GetLastOIdiff() < 0 || GetSumOIdiff() < 0 && GetLastOIdiff() > 0; }
};

#endif