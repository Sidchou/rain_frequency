/*
  http://arduino.cc/en/Tutorial/SimpleRTC
*/

#include <RTCZero.h>

/* Create an rtc object */
RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;

/* Change these values to set the current initial date */
const byte day = 15;
const byte month = 6;
const byte year = 15;

unsigned int data[4] = {0,0,0,0};
int i = 0;
int millisOffset = 0;

void setup()
{
  Serial.begin(9600);

  rtc.begin(); // initialize RTC

  // Set the time & date
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);
  
  //Set miilis offset
  millisOffset = millis();
 
  // reset index
  if (i != 0){
  i = ceil(rtc.getSeconds()/15) - 1; 
  }
  //reset data
  data[i] = 0;


}

void loop()
{
  // Print date...
  print2digits(rtc.getDay());
  Serial.print("/");
  print2digits(rtc.getMonth());
  Serial.print("/");
  print2digits(rtc.getYear());
  Serial.print(" ");

  // ...and time
  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());

  Serial.println();


  //reset every 15 second (use 32 bit)
  if (rtc.getSeconds()%15 == 0){ 
     int d =  pow(2,(15)*2) *(floor(rtc.getSeconds()/15) - 1) ;
    //add time signature for first 2 bit
    data[i] += d;
    Serial.print(i,BIN); // print index
    Serial.print(": "); 
    Serial.println(data[i],BIN); // print data
    Serial.print("int : "); 
    Serial.println(data[i]); // print data

    i = rtc.getSeconds()/15; // reset index
    data[i] = 0; // reset data
    Serial.print("rest : "); 
    Serial.println(data[i]); // print data
  }

  //data
  if (rtc.getSeconds()%5 == 0){
    // temp data fist half second
    unsigned int d =  pow(2,(rtc.getSeconds()%15)*2); 
    
    data[i] += d;
    // temp data second half second
    d =  pow(2,(rtc.getSeconds()%15)*2+1);
    
    data[i] += d;
  }


  // log data
//  if (rain){
//    //Calculate first or second half of sec(0 or 1)
//    int t = floor(((millis()-millisOffset)%1000)/500); 
//    
//    unsigned int d =  pow(2,(rtc.getSeconds()%15)*2+t); 
//    data[i] += d;
//    }
  


  
  delay(1000);
}



void print2digits(int number) {
  if (number < 10) {
    Serial.print("0"); // print a 0 before if the number is < than 10
  }
  Serial.print(number);
}
