#include "Impuls.h"
#ifdef _CONSOLE
int millis() { return 1500; }
#endif // _CONSOLE

Impuls::Impuls()
{
	this->time = 0;
	this->id = 0;
	this->value = 0;
}

Impuls::Impuls(byte id, short value)
{
	this->time = millis() / 10;
	this->id = id;
	this->value = value;
}

Impuls::Impuls(byte* s)
{
	time = s[1];
	time += (unsigned int)s[0] << 8;
	id = s[2];
	value = s[4] + s[3] * 256;
}

byte* Impuls::Serialize()
{
	//TEST ms = 2580;
	unsigned long mask = 0xFF;
	byte* s = (byte*)malloc(ImpulsSerLength);

	s[1] = time & mask;
	s[0] = (time & mask << 8) >> 8;
	s[2] = id;
	s[3] = value >> 8;
	s[4] = value & mask;

	return s;
}

String Impuls::ToString()
{
	String s;
	s += time;
	s += '\t'; s += ConvertId2Name(id);
	s += '\t'; s += value;
	return s;
}

String ConvertId2Name(byte id)
{
	switch (id)
	{
		// SENZORI
	case USF: return "USF";
	case USR: return "USR";
	case USB: return "USB";
	case USL: return "USL";

	case OIR: return "OIR";
	case OIL: return "OIL";

	case GYx: return "GYx";
	case GYy: return "GYy";
	case GYz: return "GYz";

		// KOMANDE
	case UsC: return "UsC";
	case VeC: return "VeC";

	default:
		return "???";
	}
}

String ConvertId2Class(byte id)
{
	switch (id)
	{
	case USF: return "USF";
	case USR: return "USR";
	case USB: return "USB";
	case USL: return "USL";
	case OIR: case OIL: return "OI";
	case GYx: case GYy: case GYz: return "GY";
	case UsC: return "UsC";
	case VeC: return "VeC";

	default:
		return "???";
	}
}