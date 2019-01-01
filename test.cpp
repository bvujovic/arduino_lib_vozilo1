#ifdef _CONSOLE

#include <iostream>
#include "Impuls.h"
#include "ImpulsList.h"

using namespace std;

void main()
{
	Impuls imp(23, -15);
	cout << imp.GetTime() << endl;
	cout << imp.GetId() << endl;
	cout << imp.GetValue() << endl;

	ImpulsList data(30);
	int cnt = 1;
	Impuls* pi = new Impuls(cnt % 2 ? OIR : OIL, cnt * 10);
	// poslednji impuls
	cout << (data.GetImpulsPtr(data.GetCount() - 1))->ToString() << endl;

	system("pause");
}

#endif // _CONSOLE