#include <TelnetClient.h>

#include <SPI.h>
#include <Ethernet.h>

byte remoteMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress remoteIp(192, 168, 10, 200);
IPAddress matrixMainIp(192, 168, 10, 201);
IPAddress matrixSpareIp(192, 168, 10, 201);

EthernetClient client;

const int pinBtn1 = 32;
const int pinBtn2 = 34;
const int pinBtn3 = 36;
const int pinBtn4 = 38;

const int pinLedBtn1 = 46;
const int pinLedBtn2 = 48;
const int pinLedBtn3 = 50;
const int pinLedBtn4 = 52;

int button1State = HIGH;
int button2State = HIGH;
int button3State = HIGH;
int button4State = HIGH;

int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;
int lastButton4State = HIGH;

enum MatrixPreset{
  None,
  GuiMain,
  GuiSpare,
  AllMain,
  AllSpare
};

MatrixPreset currentPreset = None;
int telnetCommandDelay = 10;

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
      currentPreset = GuiMain;
      digitalWrite(pinLedBtn1, HIGH);
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    } else {
      digitalWrite(pinLedBtn1, LOW);
    }
    delay(50);
  }

  if (button2State != lastButton2State) {
    if (button2State == LOW) {
      currentPreset = AllMain;
      digitalWrite(pinLedBtn2, HIGH);
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    } else {
      digitalWrite(pinLedBtn2, LOW);
    }
    delay(50);
  }

  if (button3State != lastButton3State) {
    if (button3State == LOW) {
      currentPreset = GuiSpare;
      digitalWrite(pinLedBtn3, HIGH);
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    } else {
      digitalWrite(pinLedBtn3, LOW);
    }
    delay(50);
  }

  if (button4State != lastButton4State) {
    if (button4State == LOW) {
      currentPreset = AllSpare;
      digitalWrite(pinLedBtn4, HIGH);
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
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

void sendMatrixPreset(IPAddress ip){
  switch(currentPreset){
  case GuiMain: 
    Serial.println("Switching GUI to Main...");
    if(client.connect(ip, 23)){ 
      client.println("r 1 1");
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;  
  case GuiSpare: 
    Serial.println("Switching GUI to Spare...");
    if(client.connect(ip, 23)){ 
      client.println("r 5 1");
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;
  case AllMain: 
    Serial.println("Switching All to Main...");
    if(client.connect(ip, 23)){ 
      //client.println("#callpreset 1");
      client.println("r 1 1");
      delay(telnetCommandDelay);
      client.println("r 2 2");
      delay(telnetCommandDelay);
      client.println("r 3 3");
      delay(telnetCommandDelay);
      client.println("r 4 4");
      delay(telnetCommandDelay);
      client.println("r 4 5");
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;
  case AllSpare: 
    Serial.println("Switching All to Spare...");
    if(client.connect(ip, 23)){ 
      //client.println("#callpreset 2");
      client.println("r 5 1");
      delay(telnetCommandDelay);
      client.println("r 6 2");
      delay(telnetCommandDelay);
      client.println("r 7 3");
      delay(telnetCommandDelay);
      client.println("r 8 4");
      delay(telnetCommandDelay);
      client.println("r 8 5");
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;
  }
}
