// Ciklicna lista objekata klase Impuls.

#ifndef IMPULSLIST_H
#define IMPULSLIST_H

#include "Impuls.h"

class ImpulsList
{
private:
	short capacity = 60;

	// niz pokazivaca na objekte klase Impuls
	//B Impuls* list[ImpulsListCapacity];
	//B Impuls** list;
	Impuls* list;

	// indeks prvog slobodnog elementa u nizu (po principu ciklicne liste)
	short idx = 0;

	// da li je kapacitet liste/niza popunjen do kraja
	bool isFull = false;

public:
	ImpulsList();
	ImpulsList(short capacity);

	void Add(Impuls imp);
	void RemoveAll();

	//* Mozda GetImpuls zameniti sa MoveNext() i GetCurrent (foreach, mozda u rev fazonu - GetPrev)
	Impuls GetImpuls(short i);
	Impuls* GetImpulsPtr(short i);
	Impuls GetImpulsRaw(short i) { return list[i]; }
	short* GetValues(short* count, byte id); // vracanje (svih) vrednosti za dati ID
	Impuls* GetLastImpuls(byte id); // vraca poslednji impuls datog ID-a. null ako u listi nema takvih impulsa.

	short GetCount() { return isFull ? capacity : idx; }
	short GetCapacity() { return capacity; }
	bool IsFull() { return isFull; }

};

#endif