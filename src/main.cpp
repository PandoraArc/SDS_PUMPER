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
  int A_previous_state = HIGH;
  unsigned long A_lastkeyenter;
  unsigned long A_timehold =  2000;
  bool callibate = false;
  
  int switchB = 3;
  int B_state;
  int B_previous_state = HIGH;
  unsigned long B_keyenter;
  unsigned long B_timehold = 2000;
  bool run = true; 

  int switchC = 8;
  int C_state;
  int C_previous_state = HIGH;
  unsigned long C_lastkeyenter;
  
 int A = 1;
 int B = 1;
 int C = 1;
 int gel_type_select;
 int gel_num_select; 
 int gel_num_select_stacking;
 int calpump_select;
 unsigned long caltime_select;
 unsigned long pumpA_time;
 unsigned long pumpB_time;
 unsigned long pumpC_time;
 unsigned long pumpD_time;
//--------------------------------------------------------------function----------------------------------------------------------------------------
void calTimefunction(int caltime){
  switch(caltime){
    case 1:
      lcd.setCursor(0,1);
      lcd.print("Time :");
      lcd.setCursor(9,1);
      lcd.print("5s");
      caltime_select = 5000;
      break;

    case 2:
      lcd.setCursor(0,1);
      lcd.print("Time :");
      lcd.setCursor(9,1);
      lcd.print("10s");
      caltime_select = 10000;
      break;

    case 3:
      lcd.setCursor(0,1);
      lcd.print("Time :");
      lcd.setCursor(9,1);
      lcd.print("20s");
      caltime_select = 20000;
      break;

    case 4:
      lcd.setCursor(0,1);
      lcd.print("Time :");
      lcd.setCursor(9,1);
      lcd.print("40s");
      caltime_select = 40000;
      break;
    
    default :
      C = 1;
      calTimefunction(C);
      break;
    
  }

}
void calFunction(int calpump){                                         //callibrate function
  switch(calpump){
    case 1:
      lcd.clear();
      lcd.home();
      lcd.print("PumpA");
      calTimefunction(C);
      calpump_select = 1;
      break;

    case 2:
      lcd.clear();
      lcd.home();
      lcd.print("PumpB");
      calTimefunction(C);
      calpump_select = 2;
      break;

    case 3:
      lcd.clear();
      lcd.home();
      lcd.print("PumpC");
      calTimefunction(C);
      calpump_select = 3;
      break;
    
    case 4:
      lcd.clear();
      lcd.home();
      lcd.print("PumpD");
      calTimefunction(C);
      calpump_select = 4;
      break;
    
    case 5 :
    A = 1;
    calFunction(A);
    break;
  }
}
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
     lcd.print("4%Stacking");
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
      gelType(A);
      break;
    }
  }
void pumpTime(int k){
  switch(k){
  case 1:
    pumpA_time =  8037;
    pumpB_time =  7819;
    pumpC_time =  17198;
    pumpD_time =  0;
    break;
  
  case 2:
    pumpA_time =  8037*2;
    pumpB_time =  7819*2;
    pumpC_time =  17198*2;
    pumpD_time =  0;
    break;
  
  case 3:
    pumpA_time =  8037*3;
    pumpB_time =  7819*3;
    pumpC_time =  17198*3;
    pumpD_time =  0;
    break;
  
  case 4 :
    pumpA_time =  8037*4;
    pumpB_time =  7819*4;
    pumpC_time =  17198*4;
    pumpD_time =  0;
    break;
  
  case 10:                                               //for stacking gel
    pumpA_time =  11472;
    pumpB_time =  0;
    pumpC_time =  2779;
    pumpD_time =  6228;
    break;

  case 20:
    pumpA_time =  11472*2;
    pumpB_time =  0;
    pumpC_time =  2779*2;
    pumpD_time =  6228*2;
    break;

  case 30:
    pumpA_time =  11472*3;
    pumpB_time =  0;
    pumpC_time =  2779*3;
    pumpD_time =  6228*3;
    break;

  case 40:
    pumpA_time =  11472*4;
    pumpB_time =  0;
    pumpC_time =  2779*4;
    pumpD_time =  6228*4;
    break;

  default:
    pumpA_time =  0;
    pumpB_time =  0;
    pumpC_time =  0;
    pumpD_time =  0;
    break;
  }
}
void pumpRun() {                                                    //Pump fuction
  if(run == true){
     switch(gel_type_select){
        case 1:
          pumpTime(gel_num_select);
        break;

        case 2:
          gel_num_select_stacking = gel_num_select*10;
          pumpTime(gel_num_select_stacking);
        break;
  
        case 3:
          pumpA_time =  3000;
          pumpB_time =  3000;
          pumpC_time =  3000;
          pumpD_time =  3000;
          break;
     }}
  else{
      switch(calpump_select){
        case 1:
          pumpA_time = caltime_select;
          pumpB_time = 0;
          pumpC_time = 0;
          pumpD_time = 0;
          break;

        case 2:
          pumpA_time = 0;
          pumpB_time =caltime_select;
          pumpC_time = 0;
          pumpD_time = 0;
          break;

        case 3:
          pumpA_time = 0;
          pumpB_time = 0;
          pumpC_time = caltime_select;
          pumpD_time = 0;
          break;

        case 4:
          pumpA_time = 0;
          pumpB_time = 0;
          pumpC_time = 0;
          pumpD_time = caltime_select;
          break;

      }
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
  if (run == true){
     gelType(A);
     gelNumber(C);
  }
  else{
    calFunction(A);
  }
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
if (callibate == true){
    run = false;

  A_state = digitalRead(switchA);                                                 //switch A read
  
    if (A_state == LOW && A_previous_state == HIGH){
        A_previous_state = LOW;
        A_lastkeyenter = millis();
    }
   
    if(A_state == HIGH && millis()-A_lastkeyenter < A_timehold){
      A = A+1;
      calFunction(A);
      A_previous_state = HIGH;
      A_lastkeyenter = 0;
    }

    if(A_state == LOW && (millis()-A_lastkeyenter) > A_timehold){
      callibate = false;
      A_previous_state = HIGH;
      gelType(A);
    }

  B_state = digitalRead(switchB);                                                //switch B read

  if (B_state == LOW && B_previous_state == HIGH){
    B_keyenter = millis();
    B_previous_state = LOW; 
  }
  
  if (B_state == LOW && (millis()-B_keyenter) > B_timehold){
      B = B+1;
      B_previous_state = HIGH;
  }

  if (B_state == HIGH && (millis()-B_keyenter) < B_timehold){
     B_keyenter = 0;                                                            
     B_previous_state = HIGH;                                                 
  }
  
  if (B==2){
    pumpRun();
    B = 1;
  }

  C_state = digitalRead(switchC);                                              //switch C read
  
  if (C_state == LOW){
    delay(200);
    if (C_state == LOW){
     
     C = C+1;
     C_lastkeyenter = millis();
    }
  }
  
  if(millis()-C_lastkeyenter < 50)
  {
    calFunction(A);
  }
}

else{
  run = true;
  A_state = digitalRead(switchA);                                                 //switch A read
  
    if (A_state == LOW && A_previous_state == HIGH){
        A_previous_state = LOW;
        A_lastkeyenter = millis();
    }
   
    if(A_state == HIGH && millis()-A_lastkeyenter < A_timehold){
      A = A+1;
      gelType(A);
      A_previous_state = HIGH;
      A_lastkeyenter = 0;
    }

    if(A_state == LOW && (millis()-A_lastkeyenter) > A_timehold){
      callibate = true;
      A_previous_state = HIGH;
      calFunction(A);
    }
 
  B_state = digitalRead(switchB);                                               //switch B read

  if (B_state == LOW && B_previous_state == HIGH){
    B_keyenter = millis();
    B_previous_state = LOW; 
  }
  
  if (B_state == LOW && (millis()-B_keyenter) > B_timehold){
      B = B+1;
      B_previous_state = HIGH;
  }

  if (B_state == HIGH && (millis()-B_keyenter) < B_timehold){
     B_keyenter = 0;                                                            
     B_previous_state = HIGH;                                                 
  }
    
  C_state = digitalRead(switchC);                                              //switch C read
  
  if (C_state == LOW){
    delay(200);
    if (C_state == LOW){
     
     C = C+1;
     C_lastkeyenter = millis();
    }
    }                   

  if(millis()-C_lastkeyenter < 50){
    gelNumber(C);
  }
  if (B==2){
    pumpRun();
    B=1;
  }
}
}