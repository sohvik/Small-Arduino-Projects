/* Tee pelin aihio. Peli käynnistyy lähettämällä sarjaporttiin merkki 's'. 
Pelin ollessa käynnissä ohjelma arpoo kahden sekunnin välein 
numeron 1,2,3 tai 4 ja tulostaa sen kometoriville. 
Käyttäjän tulee kytkeä numeroa vastaava pinni maahan 
ennen kuin seuraava numero arvotaan. 
Peli jatkuu kunnes käyttäjä kytkee väärän pinnin, tai ei ehdi ajoissa. 
Lopuksi tulostetaan kometoriville onnnistuneiden painallusten määrä. 
Pelin voi aloittaa alusta kirjoittamalla uudenstaan merkki 's' sarjaporttiin. */

unsigned long previousMillis = 0;  // stores the last time the action happened
const unsigned long interval = 2000;


volatile int pcint0PinLow = 0;
char aloitus = 'x';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 2; i < 6; i++) {
    pinMode(i, INPUT_PULLUP);  // Arduino pinnit 1-4 INPUT_PULLUP tilaan
  }

  PCICR |= (1 << PCIE2);  // aktivoidaan portti D!!!
  PCMSK2 = B00111100;     // 0x04;  // PCMSK2 = Portti D:n pinnien maskaus!!!! Käyttöön 1-4

  interrupts();  // Keskeytykset enabloituna CPU:sta.
}


void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    aloitus = Serial.read();

    if (aloitus == 's') {
      Serial.println("Peli alkaa!");

      while (1) {
        unsigned long currentMillis = millis();

        // check if 'interval' milliseconds have elapsed
        if (currentMillis - previousMillis >= interval) {
          // save the timestamp of this event
          previousMillis = currentMillis;


          int randomPinni = random(2, 6);
          Serial.println(randomPinni);
        }

        // EHKÄ TURHA ALKAA
        if (pcint0PinLow != 0) {

          // do your task here (e.g., toggle an LED)
          Serial.print("PCINT0 vaylasta keskeytys pinnista HIGH to LOW = ");
          Serial.println(pcint0PinLow);
          pcint0PinLow = 0;
          //delay(2000);  // POISTA DELAY :))
        }
      }
    }
  }

  // other code can run here continuously without being blocked

}  // loop loppuu


ISR(PCINT0_vect) {
  // This function will be called when a pin change interrupt occurs on pin 2
  Serial.println("interrupt 1");
}

ISR(PCINT1_vect) {
  // This function will be called when a pin change interrupt occurs on pin 2
  Serial.println("interrupt 2");
}

ISR(PCINT2_vect) {
  // This function will be called when a pin change interrupt occurs on pin 2
  // Joku pinneista D8 - D13 on muuttanut tilaansa 1:sta 0 tai 0 ykkoseen selvitetaan mika pinni
  for (int i = 2; i < 6; i++) {
    byte luettu = digitalRead(i);

    /*while(digitalRead(i)==LOW)
    {
      //odotellaan, etta kayttaja nostaa napin
      //
    }*/

    if (luettu == LOW) {
      pcint0PinLow = i;
    }
  }
}
