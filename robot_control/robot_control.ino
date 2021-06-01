#include <Arduino.h>
#include "WisdomElement.h"
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
WisdomElement wisdomelement;
WisdomElement_Sensor sensor1;
WisdomElement_Sensor sensor4;
WisdomElement_Sensor sensor2;

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

void setup(){
    wisdomelement.WaitBegin();
    sensor1.Begin(1);
    sensor4.Begin(4);
    sensor2.Begin(2);
    sensor2.US_ContinuMode();
    wisdomelement.MoveModeSet(2);
    Serial.begin(115200);
    
}

void loop()
{
    if(Serial.available())
    { 
      int num= Serial.read();
      switch (num)
      {
          case 97:    //a
             Serial.println("move_forward for 500ms");
             wisdomelement.MoveControl(0,20,0,500);
             _delay(1);
             break;

          case 115:   //s  直行
             wisdomelement.MoveControl(0,20,0,200);
             while(1){
               if((sensor2.US_Read_CM()) < (30)){
                 _delay(1);
               }
               else{
                 if((sensor1.COLOR_Read(2)) < ((sensor4.COLOR_Read(2)) - (10))){
                     wisdomelement.MoveControl(5,20,30,100);
                     _delay(0.1);
                  }
                  else{
                     if((sensor1.COLOR_Read(2)) > ((sensor4.COLOR_Read(2)) + (10))){
                         wisdomelement.MoveControl(355,20,-30,100);
                         _delay(0.1);
                     }
                     else{
                         wisdomelement.MoveControl(0,20,0,100);
                         _delay(0.1);
                     }
                 }
                 if(((sensor1.COLOR_Read(2)) > (70)) && ((sensor4.COLOR_Read(2)) > (70))){
                      wisdomelement.MoveControl(0,20,0,200);
                      _delay(0.4);
                      break;
                 }  
               }
              }
              Serial.println("move_forward until in white");
              break;

          case 114:  //r  右转
              Serial.println("turn right");
              wisdomelement.MoveControl(0,0,-100,1730);
              _delay(2.0);
              wisdomelement.MoveControl(0,20,0,200);
              _delay(0.2);
              break;

          case 108:  //l  左转
              Serial.println("turn left");
              wisdomelement.MoveControl(0,0,100,1730);
              _delay(1.8);
              wisdomelement.MoveControl(0,20,0,200);
              _delay(0.2);
              break;

          case 98:   //b  180度
              Serial.println("turn back");
              wisdomelement.MoveControl(0,0,200,1730);
              _delay(1.8);
              break;

          case 109:   //m  循迹前进一小段
              Serial.println("move_forward until the midpoint");
              for(int i = 0; i<10; i++)
              {
                 if((sensor1.COLOR_Read(2)) < ((sensor4.COLOR_Read(2)) - (10)))
                 {
                     wisdomelement.MoveControl(5,20,30,100);
                     _delay(0.1);
                  }
                  else
                 {
                     if((sensor1.COLOR_Read(2)) > ((sensor4.COLOR_Read(2)) + (10)))
                     {
                         wisdomelement.MoveControl(355,20,-30,100);
                         _delay(0.1);
                     }
                     else
                     {
                         wisdomelement.MoveControl(0,20,0,100);
                         _delay(0.1);
                     }
                  }
               }
               break;
              
             
          default:
               Serial.println("no such command");
               break;
         }
     }

     //else
     //{
         // wisdomelement.MoveControl(0,0,-2,500);
         // _delay(1);
    // }
     
     _loop();
}
