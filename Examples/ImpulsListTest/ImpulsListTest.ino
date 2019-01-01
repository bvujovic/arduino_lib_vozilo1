#include <ImpulsList.h>

ImpulsList data(30);
int cnt = 1, max = 50;

void setup() {
	Serial.begin(9600);

	delay(100);
	Impuls imp(3, 123);
	Serial.println(sizeof(Impuls));
	Serial.println(sizeof(Impuls*));
	Serial.println(imp.ToString());
	delay(100);
	Impuls imp2(imp.Serialize());
	Serial.println(imp2.ToString());
}

void loop() {
	if (cnt <= max)
	{
		Impuls* pi = new Impuls(cnt % 2 ? OIR : OIL, cnt * 10);
		if (pi != NULL)
		{
			data.Add(*pi);
			Serial.print('.');
			delete pi;
		}
		else
			Serial.print('x');
	}
	if (cnt == max - 10)
	{
		Serial.println();
		Serial.print("poslednji impuls: ");
		Serial.println((data.GetImpulsPtr(data.GetCount() - 1))->ToString());
	}
	if (cnt == max)
	{
		int n = data.GetCount();
		Serial.println(n);
		for (int i = 0; i < n; i++)
			Serial.println(data.GetImpuls(i).ToString());

		Serial.print("poslednji impuls: ");
		Serial.println((data.GetImpulsPtr(n - 1))->ToString());

		Serial.print("poslednji impuls za dati ID: ");
		//* Impuls* pi = data.GetLastImpuls(USR);
		Impuls* pi = data.GetLastImpuls(OIR);
		Serial.println(pi != NULL ? pi->ToString() : "ne postoji");

		short cnt;
		short* vals = data.GetValues(&cnt, OIL);
		Serial.print("OIL vrednosti: ");
		if (cnt > 0)
			for (int i = 0; i < cnt; i++)
			{
				Serial.print(vals[i]);
				Serial.print(' ');
			}
		else
			Serial.print("nema trazenih vrednosti");
		Serial.println();
	}

	cnt++;
	delay(50);
}