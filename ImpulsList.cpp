#include "ImpulsList.h"

ImpulsList::ImpulsList()
{
	this->list = new Impuls[capacity];
}

ImpulsList::ImpulsList(short capacity)
{
	this->capacity = capacity;
	this->list = new Impuls[capacity];
}

void ImpulsList::Add(Impuls imp)
{
	list[idx] = imp; //* ovo mozda ne radi. u tom slucaju kopirati clanove posebno
	if (++idx == capacity)
	{
		idx = 0;
		isFull = true;
	}
}

void ImpulsList::RemoveAll()
{
	idx = 0;
	isFull = false;
}

Impuls ImpulsList::GetImpuls(short i)
{
	if (isFull)
		return list[(idx + i) % capacity];
	else
		return list[i];
}

Impuls* ImpulsList::GetImpulsPtr(short i)
{
	if (isFull)
		return list + (idx + i) % capacity;
	else
		return list + i;
}

short* ImpulsList::GetValues(short* count, byte id)
{
	// brojanje koliko ima impulsa za dati ID
	short i, n = 0, m = GetCount();
	for (i = 0; i < m; i++)
		if (GetImpulsRaw(i).GetId() == id)
			n++;

	// zauzimanje memorije
	*count = n;
	if (n < 1)
		return NULL;
	short* values = new short[n];

	// popunjavanje niza vrednostima impulsa
	i = GetCount() - 1;
	short j = 0;
	while (i >= 0)
	{
		Impuls* pi = GetImpulsPtr(i);
		if (pi->GetId() == id)
			values[j++] = pi->GetValue();
		i--;
	}
	return values;
}

Impuls* ImpulsList::GetLastImpuls(byte id)
{
	short i = GetCount() - 1;
	while (i >= 0)
	{
		Impuls* pi = GetImpulsPtr(i);
		if (pi->GetId() == id)
			return pi;
		i--;
	}
	return NULL;
}
