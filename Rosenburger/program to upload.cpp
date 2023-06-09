#include <Arduino.h>
int out0 = 2;  // yellow 
int out1 = 3;  // orange 
int out2 = 4;  // red 
int out3 = 5;  // brown

int inp0 = 8;
int inp1 = 9;
int inp2 = 10;
int inp3 = 11;
int inp4 = 12;
int inp5 = 13;

int count = 0;
bool latch = false;
bool clamp_active = false;
// INPUT 0 == PHOTO SENSOR INPUT
// INPUT 1 == OK 
// INPUT 2 == NG

// OUT 0 == CLAPING CYINDER
// OUT 1 == CUTTING CYLINDER

void activate(int i){
  digitalWrite(i,LOW);
}

void deactivate(int i ){
  digitalWrite(i, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  //Output
  pinMode(out0, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  // Input
  pinMode(inp0,INPUT_PULLUP);
  pinMode(inp1,INPUT_PULLUP);
  pinMode(inp2,INPUT_PULLUP);
  pinMode(inp3,INPUT_PULLUP);
  pinMode(inp4,INPUT_PULLUP);
  pinMode(inp5,INPUT_PULLUP);
  // Deactivating all the output at the setup
  deactivate(out0);
  deactivate(out1);
  deactivate(out2);
  deactivate(out3);

  Serial.begin(9600);
  delay(2000);
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(inp0) == HIGH && digitalRead(inp1) == HIGH && latch == false){   // Proximity Conformation / Clamp Conformation 
      delay(100);
      activate(out0);
      activate(out2);
      latch = true;
      count = 0;
      Serial.println("Status : Clamped");
    } 

  if (digitalRead(inp2) == LOW && latch == true && count == 0){     // OK Conformation 
    deactivate(out0);
    deactivate(out2);
    Serial.println("Status : OK Conformation... Unclamping ");
    count = 1 ;

  }

  if(digitalRead(inp3) == LOW && latch == true && count == 0){  // NOK Confromation
    activate(out1);
    delay(1000);
    deactivate(out1);
    deactivate(out0);
    deactivate(out2);
    Serial.println("Status : NOK Confromation... Unclamping after Cutting");
    count = 1;
  }

  if (digitalRead(inp4) == LOW){  // Reset
    deactivate(out0);
    deactivate(out1);
    deactivate(out2);
    Serial.println("Status : Reset Confromation");
  }

  if (digitalRead(inp0) == LOW && digitalRead(inp1) == LOW && latch == true){
    latch = false;
    delay(2000);
    Serial.println("Latch Unlock");
  }
}

