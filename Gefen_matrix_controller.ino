const int pinBtn1 =  0;
const int pinBtn2 =  1;
const int pinBtn3 =  2;
const int pinBtn4 =  3;
const int pinLedBtn1 =  10;
const int pinLedBtn2 =  11;
const int pinLedBtn3 =  12;

void setup() {
  pinMode(pinBtn1, INPUT_PULLUP);
  pinMode(pinBtn2, INPUT_PULLUP);
  pinMode(pinBtn3, INPUT_PULLUP);
  pinMode(pinBtn4, INPUT_PULLUP);
  
  pinMode(pinLedBtn1, OUTPUT);
  pinMode(pinLedBtn2, OUTPUT);
  pinMode(pinLedBtn3, OUTPUT);
  pinMode(pinLedBtn4, OUTPUT);
}

int button1 = 0;    
int button2 = 0;    
int button3 = 0;    
int button4 = 0;    

// the loop function runs over and over again forever
void loop() {
  button1 = digitalRead(pinBtn1);
  button2 = digitalRead(pinBtn2);
  button3 = digitalRead(pinBtn3);
  button4 = digitalRead(pinBtn4);
  
  if (button1 == HIGH) {
    digitalWrite(pinLedBtn1, LOW);
  } else {
    digitalWrite(pinLedBtn1, HIGH);
  }
  
  if (button2 == HIGH) {
    digitalWrite(pinLedBtn2, LOW);
  } else {
    digitalWrite(pinLedBtn2, HIGH);
  }
  
  if (button3 == HIGH) {
    digitalWrite(pinLedBtn3, LOW);
  } else {
    digitalWrite(pinLedBtn3, HIGH);
  }
  
  if (button4 == HIGH) {
    digitalWrite(pinLedBtn4, LOW);
  } else {
    digitalWrite(pinLedBtn4, HIGH);
  }
}
