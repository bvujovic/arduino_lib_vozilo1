// Objekti ove klase ce sadrzati podatke o jednom ocitavanju nekog senzora,
// primljenoj komandi ili stanju vozila.

#ifndef IMPULS_H
#define IMPULS_H

#ifdef _CONSOLE
#include <string>
typedef std::string String;
typedef unsigned short byte;
#else
#include "Arduino.h"
#endif // _CONSOLE


#define ImpulsSerLength 5

class Impuls
{
private:
	// Stotinka kada je kreiran ovaj podatak. Max vrednost ovog podatka je ~11 minuta.
	unsigned int time;

	///<summary>Naziv izvora podataka. Npr USP, USZ, GYz, GYx, V(vozilo-stanje), CMD(komanda)...</summary>
	// Id senzora/komande/stanja na kojeg se odnosi ovaj impuls.
	byte id;

	// Vrednost impulsa.
	short value;

public:
	Impuls();
	Impuls(byte id, short value);
	Impuls(byte*); // deserijalizacija

	unsigned long GetTime() { return time; }
	byte GetId() { return id; }
	short GetValue() { return value; }

	byte* Serialize();

	String ToString();
};

enum ImpulsIDs
{
	// senzori
	USF = 0, USR, USB, USL,
	OIR = 11, OIL,
	GYx = 21, GYy, GYz,

	// komande
	UsC = 100 /* korisnicke */, VeC  /* komande vozila (automatske) */
};

String ConvertId2Name(byte id);
String ConvertId2Class(byte id);

#endif