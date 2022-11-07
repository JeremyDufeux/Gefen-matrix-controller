const int pinBtn1 =  2;
const int pinBtn2 =  3;
const int pinBtn3 =  4;
const int pinBtn4 =  5;
const int pinLedBtn1 =  10;
const int pinLedBtn2 =  11;
const int pinLedBtn3 =  12;
const int pinLedBtn4 =  13;

int button1State = HIGH;
int button2State = HIGH;
int button3State = HIGH;
int button4State = HIGH;
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;
int lastButton4State = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(pinBtn1, INPUT_PULLUP);
  pinMode(pinBtn2, INPUT_PULLUP);
  pinMode(pinBtn3, INPUT_PULLUP);
  pinMode(pinBtn4, INPUT_PULLUP);
  pinMode(pinLedBtn1, OUTPUT);
  pinMode(pinLedBtn2, OUTPUT);
  pinMode(pinLedBtn3, OUTPUT);
  pinMode(pinLedBtn4, OUTPUT);
}

void loop() {
  checkButtonsStates();
}

void checkButtonsStates(){
  button1State = digitalRead(pinBtn1);
  button2State = digitalRead(pinBtn2);
  button3State = digitalRead(pinBtn3);
  button4State = digitalRead(pinBtn4);

  if (button1State != lastButton1State) {
    if (button1State == HIGH) {
      Serial.println("1 off");
    } else {
      Serial.println("1 on");
    }
    delay(50);
  }

  if (button2State != lastButton2State) {
    if (button2State == HIGH) {
      Serial.println("2 off");
    } else {
      Serial.println("2 on");
    }
    delay(50);
  }

  if (button3State != lastButton3State) {
    if (button3State == HIGH) {
      Serial.println("3 off");
    } else {
      Serial.println("3 on");
    }
    delay(50);
  }

  if (button4State != lastButton4State) {
    if (button4State == HIGH) {
      Serial.println("4 off");
    } else {
      Serial.println("4 on");
    }
    delay(50);
  }
  
  lastButton1State = button1State;
  lastButton2State = button2State;
  lastButton3State = button3State;
  lastButton4State = button4State;
}

void sendMatrixPreset(){
  
}
