#include <Impuls.h>

void setup() {

  Serial.begin(9600);
  delay(27);
  Impuls imp(23, -15);
  Serial.println(imp.GetTime());
  Serial.println(imp.GetId());
  Serial.println(imp.GetValue());
  Serial.println(imp.ToString());

  byte* ser = imp.Serialize();
  for (int i = 0; i < 5; i++)
    Serial.println(ser[i]);

  Impuls imp2(ser);
  Serial.println(imp2.ToString());
}

void loop() {
  delay(1000);

}
