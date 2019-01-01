#include "Vozilo.h"

VoziloKomande CmdConvert(String s)
{
#ifdef _CONSOLE
	if (s == ("OK")) return CmdOk;
	if (s == ("Error")) return CmdError;
	if (s == ("GetImpulses")) return GetImpulses;
	if (s == ("X")) return Stop;

	if (s == ("F")) return Forward;
	if (s == ("R")) return RightTurn;
	if (s == ("B")) return Backward;
	if (s == ("L")) return LeftTurn;
	if (s == ("DC")) return DirCorrect;
#else
	if (s.equals("OK")) return CmdOk;
	if (s.equals("Error")) return CmdError;
	if (s.equals("GetImpulses")) return GetImpulses;
	if (s.equals("X")) return Stop;

	if (s.equals("F")) return Forward;
	if (s.equals("R")) return RightTurn;
	if (s.equals("B")) return Backward;
	if (s.equals("L")) return LeftTurn;
	if (s.equals("DC")) return DirCorrect;
#endif // _CONSOLE

	return CmdError;
}

String CmdConvert(VoziloKomande cmd)
{
	if (cmd == CmdOk) return "OK";
	if (cmd == CmdError) return "Error";
	if (cmd == GetImpulses) return "GetImpulses";
	if (cmd == Stop) return "X";

	if (cmd == Forward) return "F";
	if (cmd == RightTurn) return "R";
	if (cmd == Backward) return "B";
	if (cmd == LeftTurn) return "L";
	if (cmd == DirCorrect) return "DC";

	return "Error";
}