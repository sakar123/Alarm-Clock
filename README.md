# Alarm-Clock
Alarm Clock Using ATMega 2560

Please add the appropriate zip libraries for the code to run
The Libraries include
DS1302 and
LiquidCrystalI2c

Make sure that you have connected the Real Time Clock Sensor to the proper pins and match it with your code.
uint8_t RST_PIN   = ;  //RST pin attach to.. reset pin of real time clock
uint8_t SDA_PIN   = ;  //IO pin attach to... SDA pin of real time clock
uint8_t SCL_PIN   = ;  //clk Pin attach to.. SCL pin of real time clock


Make sure that you have connected the buzzer to proper pin as well
int buzzerPin = 2;//the pin of the passive buzzer attach to pin31

Set the beginning time and alarm time appropriately

In the setup function to setup initial time of the clock
 Time t(2020, 2, 27, 11 , 53, 00, 5);//initialize the time  //(Y,M,D,H,M,S,Day)  //Sun =1 , Mo=2 , Tus=3  Wed=4  Thu=5  Fri=6   Sat=7
 
 In the loop function to setup an alarm time
 int day_alarm=5;
int yr_alarm=2020;
int mon_alarm=2;
int date_alarm=27;
int hr_alarm=11;
int min_alarm=53;
int sec_alarm=30;

In the loop function, to setup snooze time
sec_alarm=sec_alarm+15;//In this case its 15 seconds

The clock snoozes with one push and turns the alarm off with two push!
 
