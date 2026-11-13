#include "aliohjelmat.h"

void setup() {
  Serial.begin(9600);
}

void loop() {

  while (Serial.available() > 0)
  {
    // rivinvaihtojen käsittely puskurista pois
    Serial.read();
  }

  rajat foo = lueRajat2();
  Serial.print("alaraja = ");
  Serial.println(foo.ala);

  Serial.print("ylaraja = ");
  Serial.println(foo.yla);

  int arvottuLuku = arvoLuku(foo.ala,foo.yla);

  int arvaus;
  int arvaukset = 0;
  Serial.println("Arvaa lukua: ");

  do {
    while (Serial.available() == 0) {
      // odotetaan inputia
    }
    arvaus = Serial.parseInt();
    while (Serial.available() > 0) {
      Serial.read();
    }
    Serial.print("Arvasit lukua ");
    Serial.println(arvaus);
    
    if (arvaus > arvottuLuku) {
      Serial.println("Arvaa pienempää lukua");
    }
    else if (arvaus < arvottuLuku) {
      Serial.println("Arvaa suurempaa lukua");
    }
    
    arvaukset++;
  } while (arvaus != arvottuLuku);

  Serial.print("Oikein! Arvasit lukua ");
  Serial.print(arvaukset);
  Serial.println(" kertaa.");
}

