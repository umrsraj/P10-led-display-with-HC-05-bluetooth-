/*
 * BLUETOOTH BASED P10 LED DISPLAY
 * https://create.arduino.cc/projecthub/abhijitbrain/wireless-notice-board-arduino-uno-dmd-9ff29e
 * https://www.youtube.com/watch?v=FnxmLO6P7lA * 
 * 
 */

#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
//#include <SoftwareSerial.h>// import the serial library
#define testserial Serial
//SoftwareSerial testserial(2, 3); // RX, TX
//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 4 // number of displays -----
#define DISPLAYS_DOWN 1 //1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
//number max of characters in your message
#define max_char 200
char message[max_char];    // stores you message
char msg[max_char];    // stores you message
char raj[max_char];    // stores you message
//char mess[max_char];
char r_char;               // reads each character
byte index = 0;            // defines the position into your array
int i;  
char rr;          
//char greeting[] = "AMBEST TECHNOLOGIES(#F-9)-INNOVATIVE LIVE PROJECTS -MTECH,BTECH,DIPLOMA&MCA.***(ECE/EEE/CSE/MECH/CIVIL)***Cont:+91-9700726611/33/88.";
char greeting[] = "AMBEST TECHNOLOGIES ";

void ScanDMD()
{  
  dmd.scanDisplayBySPI();
}

void setup(void)
{

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5s) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   testserial.begin(9600); //Software serial initialization
   Serial.begin(9600);
strcpy(message,greeting);
 Serial.println("kit started");
 testserial.println("kit started"); delay(2000);
}


//----------------------------------------------------
void loop(void)
{
   //check if serial is avaible an before reading a new message delete's the old message
    
   if(testserial.available())
   {       
   
    Serial.println("data deleting");
        for(i=0; i<199; i++){
            message[i] = '\0';
            Serial.print(message[i]);
            delay(5); //-------------------------
        } 
        //resests the index        
        index=0;
//********************************************************
dmd.clearScreen( true );
    //while is reading the message 
    while(testserial.available() > 0){
       //the message can have up to 100 characters 
       
       if(index < (max_char-1)) 
       {         
           r_char = testserial.read();      // Reads a character
           msg[index] = r_char;     // Stores the character in message array
           index++;                     // Increment position      
       } 
   }
   Serial.print("msg: "); Serial.println(msg);

if ((msg[0]!='+')&&(msg[1]!='D')&&(msg[2]!='I'))
{
  strcpy(raj,msg);
  strcpy(message,raj);   
}
else
{
 
   Serial.print("raj: "); Serial.println(raj); 
   
  strcpy(message,raj);
  Serial.println("device disconnected");
}

   Serial.print("message: "); Serial.println(message);
//********************************************************    
    }
   

 //prepares the display to print our message
   dmd.selectFont(Arial_Black_16);
   //displays the message
   dmd.drawMarquee(message ,max_char,(32*DISPLAYS_ACROSS)-1 ,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+30) < millis()) {   //60 
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
}
