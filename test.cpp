#ifdef _CONSOLE

#include <iostream>
#include "Impuls.h"
#include "ImpulsList.h"
#include "MotorController.h"


using namespace std;

void IspisiMC(MotorController mc)
{
	cout << "L: " << mc.GetPinL1() << mc.GetPinL2() << ' ' << mc.GetPinLEN() << endl;
	cout << "R: " << mc.GetPinR1() << mc.GetPinR2() << ' ' << mc.GetPinREN() << endl;
}

void Izvrsi(MotorController& mc, VoziloKomande cmd, short speed)
{
	bool priprema = mc.Execute(cmd, speed);
	IspisiMC(mc);
	if (priprema)
	{
		cout << "cekanje 5ms..." << endl;
		mc.Execute(cmd, speed);
		IspisiMC(mc);
	}
}

void main()
{
	//Impuls imp(23, -15);
	//cout << imp.GetTime() << endl;
	//cout << imp.GetId() << endl;
	//cout << imp.GetValue() << endl;

	//ImpulsList data(30);
	//int cnt = 1;
	//Impuls* pi = new Impuls(cnt % 2 ? OIR : OIL, cnt * 10);
	//// poslednji impuls
	//cout << (data.GetImpulsPtr(data.GetCount() - 1))->ToString() << endl;

	MotorController mc;
	bool priprema;

	// Izvrsi(mc, Forward, 30);

	// Izvrsi(mc, Backward, -300);

	// Izvrsi(mc, TurnRight, -80);

	//Izvrsi(mc, Backward, 120);
	//Izvrsi(mc, DirCorrect, -15);
	//Izvrsi(mc, Nowhere, 0);

	//Izvrsi(mc, Backward, 160);
	//Izvrsi(mc, Forward, 60);

	//* NE RADI DOBRO
	//Izvrsi(mc, Forward, 235);
	//Izvrsi(mc, DirCorrect, -10);

	Izvrsi(mc, Forward, 80);
	//Izvrsi(mc, DirCorrect, 2);
	//Izvrsi(mc, Forward, 100);
	//Izvrsi(mc, DirCorrect, 0);

	// cout << mc.GetPinLEN() << " - " << mc.GetPinREN() << endl;

	system("pause");
}

#endif // _CONSOLE