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

int data[30][4] = {{},{}}; 
int i = 0;
int j = 0;
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
 
    // reset data
    resetData();
    
     // reset index
    resetIndex();

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


  //reset every 2 min
  if (rtc.getMinutes()%2 == 0&&rtc.getSeconds()==0){ 
    // int d =  pow(2,(15)*2) *(floor(rtc.getSeconds()/15) - 1) ;
    // //add time signature for first 2 bit
    // data[j][i] += d;
    printData();

    // reset data
    resetData();
    
     // reset index
    resetIndex();


  }

  //data
  if (rtc.getSeconds()%5 == 0){
    // select index
     j = rtc.getMinutes()%2;
     i = floor(rtc.getSeconds()/15);
    //1 << (rtc.getSeconds()%4)*2;
    data[j][i] += 1 << (rtc.getSeconds()%15)*2;

    // temp data second half second  
    data[j][i] += 1 << (rtc.getSeconds()%15)*2+1;

  }


  // log data
//  if (rain){
//     // calculate index
//     j = rtc.getMinutes()%30;
//     i = floor(rtc.getSeconds()/15);
//    //Calculate first or second half of sec(0 or 1)
//    int t = floor(((millis()-millisOffset)%1000)/500); 
//    data[i] += 1 << (rtc.getSeconds()%15)*2+t;
//    }
  


  
  delay(1000);
}



void print2digits(int number) {
  if (number < 10) {
    Serial.print("0"); // print a 0 before if the number is < than 10
  }
  Serial.print(number);
}

void resetData(){
  
  for (j = 0; j < 2; j++){
      for (i = 0; i < 16; i++){
        data[j][i] = 0;
      }
    }
  }

void resetIndex(){
   i = floor(rtc.getSeconds()/4);
   j = rtc.getMinutes()%2;
  }
void printData(){
  Serial.println("data: ");
    for (j = 1; j >= 0; j--){
      for (i = 3; i >= 0; i--){
        printAll(data[j][i]);
        Serial.println("");
      }
      
    }
   Serial.println("");

  }

void printAll(int n) {
  for (int bits = 31; bits > -1; bits--) {
    // Compare bits 7-0 in byte
    if (n & (1 << bits)) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
  }
}
