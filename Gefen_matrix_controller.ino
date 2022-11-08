#include <TelnetClient.h>

#include <SPI.h>
#include <Ethernet.h>

byte remoteMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress remoteIp(192, 168, 10, 200);
IPAddress matrixIp(192, 168, 10, 201);

EthernetClient client;

const int pinBtn1 = 32;
const int pinBtn2 = 34;
const int pinBtn3 = 36;
const int pinBtn4 = 38;

const int pinLedBtn1 = 10;
const int pinLedBtn2 = 11;
const int pinLedBtn3 = 12;
const int pinLedBtn4 = 13;

int activeState = 0;

int button1State = HIGH;
int button2State = HIGH;
int button3State = HIGH;
int button4State = HIGH;

int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;
int lastButton4State = HIGH;

enum MatrixPreset{
  GuiMain,
  GuiSpare,
  AllMain,
  AllSpare
};

void setup() {
  Ethernet.begin(remoteMac, remoteIp);
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
    if (button1State == LOW) {
      digitalWrite(pinLedBtn1, HIGH);
      activeState = 1;
      sendMatrixPreset(GuiMain);
    } else {
      digitalWrite(pinLedBtn1, LOW);
    }
    delay(50);
  }

  if (button2State != lastButton2State) {
    if (button2State == LOW) {
      digitalWrite(pinLedBtn2, HIGH);
      activeState = 2;
      sendMatrixPreset(AllMain);
    } else {
      digitalWrite(pinLedBtn2, LOW);
    }
    delay(50);
  }

  if (button3State != lastButton3State) {
    if (button3State == LOW) {
      digitalWrite(pinLedBtn3, HIGH);
      activeState = 3;
      sendMatrixPreset(GuiSpare);
    } else {
      digitalWrite(pinLedBtn3, LOW);
    }
    delay(50);
  }

  if (button4State != lastButton4State) {
    if (button4State == LOW) {
      digitalWrite(pinLedBtn4, HIGH);
      activeState = 4;
      sendMatrixPreset(AllSpare);
    } else {
      digitalWrite(pinLedBtn4, LOW);
    }
    delay(50);
  }
  
  lastButton1State = button1State;
  lastButton2State = button2State;
  lastButton3State = button3State;
  lastButton4State = button4State;
}

void sendMatrixPreset(MatrixPreset preset){
  switch(preset){
  case GuiMain: 
    Serial.println("Switching GUI to Main...");
    if(client.connect(matrixIp, 23)){ 
      client.println("r 1 1");
      Serial.println("...Done");
    } else {
      Serial.println("...Failed");
    }
    Serial.println("");
    break;  
  case GuiSpare: 
    Serial.println("Switching GUI to Spare...");
    if(client.connect(matrixIp, 23)){ 
      client.println("r 5 1");
      Serial.println("...Done");
    } else {
      Serial.println("...Failed");
    }
    Serial.println("");
    break;
  case AllMain: 
    Serial.println("Switching All to Main...");
    if(client.connect(matrixIp, 23)){ 
      client.println("#callpreset 1");
      Serial.println("...Done");
    } else {
      Serial.println("...Failed");
    }
    Serial.println("");
    break;
  case AllSpare: 
    Serial.println("Switching All to Spare...");
    if(client.connect(matrixIp, 23)){ 
      client.println("#callpreset 2");
      Serial.println("...Done");
    } else {
      Serial.println("...Failed");
    }
    Serial.println("");
    break;
  }
}
