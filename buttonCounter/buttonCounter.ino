volatile int laskuri = 0;

void nappi1();
void nappi10();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3), nappi1, FALLING);
  attachInterrupt(digitalPinToInterrupt(2), nappi10, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

  noInterrupts();
  int painallukset = laskuri;
  laskuri = 0;
  interrupts();

  Serial.println(painallukset);
}

void nappi1(){
  laskuri += 1;
}

void nappi10(){
  laskuri += 10;
}