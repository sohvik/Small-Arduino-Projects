#include <Arduino.h>
#include "aliohjelmat.h"

int arvoLuku(int eka,int toka)
{
   int paluuarvo = random(eka, toka);
   return paluuarvo;
}

rajat lueRajat2()
{
  rajat R;
  Serial.println("Anna alaraja");
  while(Serial.available()==0)
  {
      // odotellaan käyttäjän inputtia
  }
  R.ala = Serial.parseInt();

    while (Serial.available() > 0)
  {
    // rivinvaihtojen käsittely puskurista pois
    Serial.read();
  }

  Serial.println("Anna ylaraja");
  while(Serial.available()==0)
  {
      // odotellaan käyttäjän inputtia
  }
  R.yla = Serial.parseInt();
  while (Serial.available() > 0) {
    Serial.read();
  }
  return R;
}







