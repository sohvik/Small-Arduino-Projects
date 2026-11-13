/* 1: Tee sekuntikello käyttäen Loop-rakennetta ja Timeria. 
Sekuntikellon tulee laskea sekunnin kymmenyksiä, sekunteja ja minuutteja

- Sekuntikello käynnistetään maadoittamalla pinni 2 (voit käyttää keskeytyksiä apuna)

- Sekuntikello päivittää ajan sarjaportille sekunnin välein.

- Sekuntikello pysäytetään maadoittamalla pinni 3, jolloin tulostetaan tarkka aika kymmenyksineen, 
ja nollataan aika uutta ajanottoa varten. */

void ajanAloitus();
void ajanLopetus();
volatile unsigned long timerMillis = 0;
int tila = 0;

void setup() {
  Serial.begin(9600);

  //CTC päälle: WGM21 = 1
  TCCR2A |= (1 << WGM21);

  // Timerin preskaalaus 64-nopeuteen:
  TCCR2B |= (1 << CS22);

  // 1 ms keskeytysväli:
  OCR2A = 249;

  // Compare Match A -keskeytys päälle:
  TIMSK2 |= (1 << OCIE2A);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), ajanAloitus, FALLING);
  
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), ajanLopetus, FALLING);
}

void loop() {
  unsigned long milliSekunnit;

  noInterrupts();
  milliSekunnit = timerMillis;
  interrupts();

  static unsigned long tulostusVali = 0;

  if (tila == 1) {
    // Tässä printtaustahti sekunnin kymmenyksen mukaan:
    if (milliSekunnit - tulostusVali >= 100) {
      tulostusVali += 100;

      unsigned long minuutit = milliSekunnit / 60000;
      unsigned long sekunnit = (milliSekunnit / 1000) % 60;
      unsigned long kymmenykset = (milliSekunnit / 100) % 10;

      Serial.print(minuutit);
      Serial.print(":");

      // placeholder 0 edessä ennen 10 sekuntia
      if (sekunnit < 10) {
        Serial.print("0");
      }

      Serial.print(sekunnit);
      Serial.print(".");

      Serial.println(kymmenykset);
    }
  }
}

ISR(TIMER2_COMPA_vect) {
  timerMillis++;
}

void ajanAloitus() {
  tila = 1;
}

void ajanLopetus() {
  tila = 0;
}

/*
void blink() {
  Serial.print("State on: ");
  Serial.println(state);
}*/