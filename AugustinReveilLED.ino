  // Date and time functions using a RX8025 RTC connected via I2C and Wire lib
  
  #include <Wire.h>
  #include "Sodaq_DS3231.h"
  
  int PinLedRouge=13;
  int PinLedVerte=12;
  int HeureLeve=0;
  int HeureCouch=21;
   int ActualDay    ;
  int ActualHours   ;
  int ActualMinutes ;
  char weekDay[][9] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };
  
  //year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
  //writing any non-existent time-data may interfere with normal operation of the RTC.
  //Take care of week-day also.
  //DateTime dt(2017, 04, 01, 10, 02, 0, 0);
  
  
  void setup () 
  {
  Serial.begin(57600);
  Wire.begin();
  rtc.begin();
  //rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PinLedRouge, OUTPUT);
  pinMode(PinLedVerte, OUTPUT);
  }
  
  void loop () 
  {
  delay(1000);
  DateTime now = rtc.now(); //get the current date-time
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.date(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.print(weekDay[now.dayOfWeek()]);
  Serial.println();
  
  ActualDay     = (int)weekDay[now.dayOfWeek()];
  ActualHours   = now.hour();
  ActualMinutes = now.minute();
  
  
  
  
    if(ActualHours > 0 && ActualHours <12){
     ModeMatin();
    }
    else{
     ModeSoir();
    }
 
   
    
  }
    
    void ModeMatin(){
      if(ActualDay ==0 || ActualDay==6)
        {
          HeureLeve=8;
        }
        else{
          HeureLeve=7;
        }
       
       if( ActualHours < HeureLeve-1 || ActualHours > HeureLeve+1 ){
         ModeStop();
         }
       else{
         
            if(ActualHours <  HeureLeve )
            {
              digitalWrite(PinLedRouge, HIGH);
              digitalWrite(PinLedVerte, LOW);
            }
            else
            {
              digitalWrite(PinLedVerte, HIGH);
              digitalWrite(PinLedRouge, LOW);
            }
       }
    }
    
    void ModeStop(){
      Serial.print("NUIT");
      digitalWrite(PinLedRouge, LOW);
      digitalWrite(PinLedVerte, LOW);
    }
    
    void ModeSoir(){
      
      if( ActualHours  == HeureCouch-1 ){
          digitalWrite(PinLedVerte, HIGH);
          digitalWrite(PinLedRouge, LOW);
      }
      else if(HeureCouch== ActualHours ){
        digitalWrite(PinLedRouge, HIGH);
        digitalWrite(PinLedVerte, LOW);
      }
      else{
      ModeStop();
      }
      
    }
