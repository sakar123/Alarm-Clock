
#include <DS1302.h>

#include <LiquidCrystal_I2C.h>

/*****************************************************
 * name:Real-time Clock Module 
 * function:you can see the current date and time displayed on the I2C LCD1602.
 ******************************************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

//include the libraries
#include <stdio.h>
#include <string.h>
#include "pitches.h"
#include <Wire.h> 


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t RST_PIN   = 49;  //RST pin attach to
uint8_t SDA_PIN   = 51;  //IO pin attach to
uint8_t SCL_PIN   = 53;  //clk Pin attach to
/* Create buffers */
char buf[50];
char day[10];
int button=1;//reading the button
/* SetUp buzzer Pin for sound indication*/
int buzzerPin = 2;//the pin of the active buzzer attach to pin31
/* Create a DS1302 object */
DS1302 rtc(RST_PIN, SDA_PIN, SCL_PIN);//create a variable type of DS1302


// notes in the melody:
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4};

//save the state of the button
int button_state=0;


int Buzzer_tone ()
{
  int check=1;// iterate over the notes of the melody:
  while(check){
  for (int thisNote = 4; thisNote < 6; thisNote++) 
        {
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1400 / noteDurations[thisNote];
          tone(buzzerPin, melody[thisNote], noteDuration);
          // to distinguish the notes, set a minimum time between them.// the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.05;
          button=digitalRead(7);
          delay(pauseBetweenNotes);
          noTone(buzzerPin);    // stop the tone playing:
           button=digitalRead(7);
         }
      if (button==0){
        check=0;
        button_state=button_state+1;
      }
  }   
 }
void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();//read time
  /* Name the day of the week */
  memset(day, 0, sizeof(day));
          switch (t.day)
          {
          case 1: 
            strcpy(day, "Sun"); 
            break;
          case 2: 
            strcpy(day, "Mon"); 
            break;
          case 3: 
            strcpy(day, "Tue"); 
            break;
          case 4: 
            strcpy(day, "Wed"); 
            break;
          case 5: 
            strcpy(day, "Thu"); 
            break;
          case 6: 
            strcpy(day, "Fri"); 
            break;
          case 7: 
            strcpy(day, "Sat"); 
            break;
          }
  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);
  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
  lcd.setCursor(2,0);
  lcd.print(t.yr);
  lcd.print("-"); 
  lcd.print(t.mon/10);
  lcd.print(t.mon%10);
  lcd.print("-");
  lcd.print(t.date/10);
  lcd.print(t.date%10);
  lcd.print(" ");
  lcd.print(day);
  lcd.setCursor(4,1);
  lcd.print(t.hr);
  lcd.print(":");
  lcd.print(t.min/10);
  lcd.print(t.min%10);
  lcd.print(":");
  lcd.print(t.sec/10);
  lcd.print(t.sec%10);
  

}


void alarm()
{
 
        lcd.noBacklight();
        delay(1000);
        lcd.backlight();
        if(button_state==2){
          loop();
        }
        else
        {
          Buzzer_tone ();
        }
      
  
}

void setup()
{
  Serial.begin(9600);
  pinMode(buzzerPin,OUTPUT);//set the buzzer as as OUTPUT
  pinMode(7,INPUT);
  rtc.writeProtect(false);
  rtc.halt(false);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  Time t(2020, 2, 27, 11 , 53, 00, 5);//initialize the time  //(Y,M,D,H,M,S,Day)  //Sun =1 , Mo=2 , Tus=3  Wed=4  Thu=5  Fri=6   Sat=7
  rtc.time(t);    /* Set the time and date on the chip */
}

void loop()
{

  /* print the current time */
 print_time();
Time tx=rtc.time();

//alarm time
int day_alarm=5;
int yr_alarm=2020;
int mon_alarm=2;
int date_alarm=27;
int hr_alarm=11;
int min_alarm=53;
int sec_alarm=30;
  /*check time for alarm*/
 // button=digitalRead(7);
       // initial setting   (2020, 2, 17, 8 , 19, 0, 2)
  if (   (tx.day==day_alarm)&& (tx.yr==yr_alarm)&& ( tx.mon==mon_alarm)&& ( tx.date==date_alarm)&& ( tx.hr==hr_alarm )&& ( tx.min==min_alarm)&& (tx.sec==sec_alarm)&& button_state==0)
  alarm();
  
  else if(button_state==1 )
  {
    sec_alarm=sec_alarm+15;
    if (   (tx.day==day_alarm)&& (tx.yr==yr_alarm)&& ( tx.mon==mon_alarm)&& ( tx.date==date_alarm)&& ( tx.hr==hr_alarm )&& ( tx.min==min_alarm)&& (tx.sec==sec_alarm)     )
    alarm();
  }
  else{
    date_alarm=tx.date-1;
  }
  
}
