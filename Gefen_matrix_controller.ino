#include <TelnetClient.h>

#include <SPI.h>
#include <Ethernet.h>

byte remoteMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress remoteIp(192, 168, 10, 200);
IPAddress matrixMainIp(192, 168, 10, 201);
IPAddress matrixSpareIp(192, 168, 10, 202);

EthernetClient client;

const int pinBtnGuiMain = 32;
const int pinBtnAllMain = 34;
const int pinBtnGuiSpare = 36;
const int pinBtnAllSpare = 38;

const int pinLedBtnGuiMain = 24;
const int pinLedBtnAllMain = 26;
const int pinLedBtnGuiSpare = 28;
const int pinLedBtnAllSpare = 30;

int buttonGuiMainState = HIGH;
int buttonAllMainState = HIGH;
int buttonGuiSpareState = HIGH;
int buttonAllSpareState = HIGH;

int lastButtonGuiMainState = HIGH;
int lastButtonAllMainState = HIGH;
int lastButtonGuiSpareState = HIGH;
int lastButtonAllSpareState = HIGH;

enum MatrixPreset{
  None,
  GuiMain,
  AllMain,
  GuiSpare,
  AllSpare
};

MatrixPreset currentPreset = None;
int telnetCommandDelay = 10;

void setup() {
  Ethernet.begin(remoteMac, remoteIp);
  Serial.begin(9600);
  
  pinMode(pinBtnGuiMain, INPUT_PULLUP);
  pinMode(pinBtnAllMain, INPUT_PULLUP);
  pinMode(pinBtnGuiSpare, INPUT_PULLUP);
  pinMode(pinBtnAllSpare, INPUT_PULLUP);
  pinMode(pinLedBtnGuiMain, OUTPUT);
  pinMode(pinLedBtnAllMain, OUTPUT);
  pinMode(pinLedBtnGuiSpare, OUTPUT);
  pinMode(pinLedBtnAllSpare, OUTPUT);
}

void loop() {
  checkButtonsStates();
}

void checkButtonsStates(){
  buttonGuiMainState = digitalRead(pinBtnGuiMain);
  buttonAllMainState = digitalRead(pinBtnAllMain);
  buttonGuiSpareState = digitalRead(pinBtnGuiSpare);
  buttonAllSpareState = digitalRead(pinBtnAllSpare);

  
  if (buttonGuiMainState != lastButtonGuiMainState) {
    if (buttonGuiMainState == LOW) {
      currentPreset = GuiMain;
      updateLedState();
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);  
    }
    delay(50);
  }

  if (buttonAllMainState != lastButtonAllMainState) {
    if (buttonAllMainState == LOW) {
      currentPreset = AllMain;
      updateLedState();
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    }
    delay(50);
  }

  if (buttonGuiSpareState != lastButtonGuiSpareState) {
    if (buttonGuiSpareState == LOW) {
      currentPreset = GuiSpare;
      updateLedState();
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    }
    delay(50);
  }

  if (buttonAllSpareState != lastButtonAllSpareState) {
    if (buttonAllSpareState == LOW) {
      currentPreset = AllSpare;
      updateLedState();
      sendMatrixPreset(matrixMainIp);
      sendMatrixPreset(matrixSpareIp);
    } 
    delay(50);
  }
  
  
  lastButtonGuiMainState = buttonGuiMainState;
  lastButtonAllMainState = buttonAllMainState;
  lastButtonGuiSpareState = buttonGuiSpareState;
  lastButtonAllSpareState = buttonAllSpareState;
}

void updateLedState(){
  switch(currentPreset){
  case GuiMain: 
      digitalWrite(pinLedBtnGuiMain, HIGH);
      digitalWrite(pinLedBtnAllMain, LOW);
      digitalWrite(pinLedBtnGuiSpare, LOW);
      digitalWrite(pinLedBtnAllSpare, LOW);
    break;
  case AllMain: 
      digitalWrite(pinLedBtnGuiMain, LOW);
      digitalWrite(pinLedBtnAllMain, HIGH);
      digitalWrite(pinLedBtnGuiSpare, LOW);
      digitalWrite(pinLedBtnAllSpare, LOW);
    break;
  case GuiSpare: 
      digitalWrite(pinLedBtnGuiMain, LOW);
      digitalWrite(pinLedBtnAllMain, LOW);
      digitalWrite(pinLedBtnGuiSpare, HIGH);
      digitalWrite(pinLedBtnAllSpare, LOW);
    break;
  case AllSpare:
      digitalWrite(pinLedBtnGuiMain, LOW);
      digitalWrite(pinLedBtnAllMain, LOW);
      digitalWrite(pinLedBtnGuiSpare, LOW);
      digitalWrite(pinLedBtnAllSpare, HIGH);
    break;
  default:
      digitalWrite(pinLedBtnGuiMain, LOW);
      digitalWrite(pinLedBtnAllMain, LOW);
      digitalWrite(pinLedBtnGuiSpare, LOW);
      digitalWrite(pinLedBtnAllSpare, LOW);
    break;
  }
}

void sendMatrixPreset(IPAddress ip){
  switch(currentPreset){
  case GuiMain:
    Serial.println("Switching GUI to Main...");
    if(client.connect(ip, 23)){
      client.println("r 1 1");
      delay(telnetCommandDelay);
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;  
  case AllMain:
    Serial.println("Switching All to Main...");
    if(client.connect(ip, 23)){
      client.println("r 1 1 6 7 8");
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
  case GuiSpare:
    Serial.println("Switching GUI to Spare...");
    if(client.connect(ip, 23)){ 
      client.println("r 5 1");
      delay(telnetCommandDelay);
      Serial.println("...done!");
    } else {
      Serial.println("...failed!");
    }
    Serial.println("");
    break;
  case AllSpare:
    Serial.println("Switching All to Spare...");
    if(client.connect(ip, 23)){ 
      client.println("r 5 1 6 7 8");
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
