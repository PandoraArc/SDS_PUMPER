#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
LiquidCrystal_PCF8574 lcd(0x27);

 // ----------------------------------------------------------------Setup variable---------------------------------------------------------------
  int pumpA = 4;
  int pumpB = 5;
  int pumpC = 6;
  int pumpD = 7;
 
  int switchA = 2;
  int A_state;
  int A_pervious_state = HIGH;
  unsigned long A_lastkeyenter;
  
  int switchB = 3;
  int B_state;
  int B_pervious_state = HIGH;
  unsigned long B_keyenter;
  unsigned long B_timehold = 2000;
  
  int switchC = 8;
  int C_state;
  int C_pervious_state = HIGH;
  unsigned long C_lastkeyenter;
  
 // Set value
 int A = 1;
 int B = 1;
 int C = 1;
 int gel_type_select;
 int gel_num_select; 
 int gel_num_select_stacking;
 unsigned long pumpA_time;
 unsigned long pumpB_time;
 unsigned long pumpC_time;
 unsigned long pumpD_time;
//--------------------------------------------------------------function----------------------------------------------------------------------------
void gelNumber(int j){                                               //gelNmberfunction
     if(C==1){
     lcd.setCursor(0,1);
     lcd.print("Number: ");
     lcd.setCursor(9,1);
     lcd.print("1");
     gel_num_select = 1;

    }
     else if(C==2){
     lcd.setCursor(0,1);
     lcd.print("Number: ");
     lcd.setCursor(9,1);
     lcd.print("2");
     gel_num_select = 2;
    
    }
     else if(C==3){
     lcd.setCursor(0,1);
     lcd.print("Number: ");
     lcd.setCursor(9,1);
     lcd.print("3");
     gel_num_select = 3;
    
    }
    else if(C==4){
     lcd.setCursor(0,1);
     lcd.print("Number: ");
     lcd.setCursor(9,1);
     lcd.print("4"); 
     gel_num_select = 4;
    }
    else {
      C = 1;
      gelNumber(C);
    }
    
}
void gelType(int i){                                                 //gelTypefunction
    switch (i){
    case 1:
      lcd.clear();
      lcd.home(); 
      lcd.print("Gel: ");
      lcd.setCursor(4,0);
      lcd.print("12%Sperating");
      gelNumber(C);
      gel_type_select = 1; 
      break;
      
    case 2:
     lcd.clear();
     lcd.home();
     lcd.print("Gel: ");
     lcd.setCursor(4,0);
     lcd.print("4%Streaking");
     gelNumber(C);
     gel_type_select = 2; 
     break;
      
    case 3:
      lcd.clear();
      lcd.home(); 
      lcd.print("Gel: ");
      lcd.setCursor(4,0);
      lcd.print("Flush");
      gelNumber(C);
      gel_type_select = 3; 
      break;

    case 4:
      A = 1;
      lcd.clear();
      lcd.home();
      lcd.print("Gel: ");
      lcd.setCursor(4,0);
      lcd.print("12%sperating");
      gel_type_select = 1; 
    }
  }
void pumpTime(int k){
  switch(k){
  case 1:
    pumpA_time =  6623;
    pumpB_time =  9298;
    pumpC_time =  18996;
    pumpD_time =  0;
    break;
  
  case 2:
    pumpA_time =  13246;
    pumpB_time =  18596;
    pumpC_time =  37992;
    pumpD_time =  0;
    break;
  
  case 3:
    pumpA_time =  19869;
    pumpB_time =  27894;
    pumpC_time =  56988;
    pumpD_time =  0;
    break;
  
  case 10:
    pumpA_time =  9597;
    pumpB_time =  0;
    pumpC_time =  2902;
    pumpD_time =  4857;
    break;

  case 20:
    pumpA_time =  2*9597;
    pumpB_time =  0;
    pumpC_time =  2*2902;
    pumpD_time =  2*4857;
    break;

  case 30:
    pumpA_time =  3*9597;
    pumpB_time =  0;
    pumpC_time =  3*2902;
    pumpD_time =  3*4857;
    break;

  default:
    pumpA_time =  0;
    pumpB_time =  0;
    pumpC_time =  0;
    pumpD_time =  0;
    break;
  }
}
void pumpRun() {                                                     //Pump fuction
     switch(gel_type_select){
        case 1:
        pumpTime(gel_num_select);
        break;

        case 2:
        gel_num_select_stacking = gel_num_select*10;
        pumpTime(gel_num_select_stacking);
        break;
  
        case 3:
        pumpA_time =  2000;
        pumpB_time =  2000;
        pumpC_time =  2000;
        pumpD_time =  2000;
        break;
     }
     Serial.println(gel_num_select);
     Serial.println(gel_num_select_stacking);
     Serial.println(pumpA_time);
     Serial.println(pumpB_time);
     Serial.println(pumpC_time);
     Serial.println(pumpD_time);
     Serial.println("--------------------------------");
     lcd.clear();
     lcd.home(); 
     lcd.print("Loading pump A ");
     lcd.blink(); 
     digitalWrite(pumpA, LOW);
     delay(pumpA_time);
     digitalWrite(pumpA, HIGH);
      
     lcd.home();
     lcd.print("Loading pump B ");
     lcd.blink();
     digitalWrite(pumpB, LOW);
     delay(pumpB_time);
     digitalWrite(pumpB, HIGH);
     
     lcd.home();
     lcd.print("Loading pump C ");
     lcd.blink();
     digitalWrite(pumpC, LOW);
     delay(pumpC_time);
     digitalWrite(pumpC, HIGH);
     
     lcd.home();
     lcd.print("Loading pump D ");
     lcd.blink();
     digitalWrite(pumpD, LOW);
     delay(pumpD_time);
     digitalWrite(pumpD, HIGH);

     lcd.clear();
     lcd.noBlink();
     lcd.home();
     lcd.print("Finish");
     delay(500);
     gelType(A);
     gelNumber(C);
    }
void setup() { 
  
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16,2);
  
 //Setup Pin
  pinMode(pumpA, OUTPUT);
  pinMode(pumpB, OUTPUT);
  pinMode(pumpC, OUTPUT);
  pinMode(pumpD, OUTPUT);
  pinMode(switchC, INPUT_PULLUP);
  pinMode(switchA, INPUT_PULLUP);
  pinMode(switchB, INPUT_PULLUP);

 //Say hello
 lcd.setBacklight(225);
 lcd.setCursor(3,0);
 lcd.print ("Welcome to");
 lcd.setCursor(4,1);
 lcd.print("SDS PUMP");
 delay(3000);
 lcd.clear();
 gelType(A);
 gelNumber(C);
 digitalWrite(pumpA,HIGH);
 digitalWrite(pumpB,HIGH);
 digitalWrite(pumpC,HIGH);
 digitalWrite(pumpD,HIGH);
}
void loop() {
    A_state = digitalRead(switchA);                                  //switch A read
  
  if (A_state == LOW){
    delay(200);
    if (A_state == LOW){
     
     A = A+1;
     A_lastkeyenter = millis();
    }
    }
 
   B_state = digitalRead(switchB);                                  //switch B read

  if (B_state == LOW && B_pervious_state == HIGH){
    B_keyenter = millis();
    B_pervious_state = LOW; 
  }
  
  if (B_state == LOW && (millis()-B_keyenter) > B_timehold){
      B = B+1;
      B_pervious_state = HIGH;
  }

  if (B_state == HIGH && (millis()-B_keyenter) < B_timehold){
     B_keyenter = 0;                                                            //NO Need
     B_pervious_state = HIGH;                                                 
  }
    
  C_state = digitalRead(switchC);                                              //switch C read
  
  if (C_state == LOW){
    delay(200);
    if (C_state == LOW){
     
     C = C+1;
     C_lastkeyenter = millis();
    }
    }

    //-----------------------------------------------------------------------------Main function 
                                               
  if(millis()-A_lastkeyenter < 50){
    gelType(A);
  }
  
  if(millis()-C_lastkeyenter < 50)
  {
    gelNumber(C);
  }
  if (B==2){
    pumpRun();
    B=1;
  }
}   