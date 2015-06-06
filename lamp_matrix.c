#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZEOF(n) (sizeof(n) / sizeof(n[0]))
//#define SIZEOF(n) (sizeof(n))


int main(void)
{
  
  if (wiringPiSetup() == -1)
    return 1 ;
  

  int rowPins[8] = {0,2,3,12,13,14,21,22};
  int colPins[3] = {8,9,7};
  int colOutputs[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};

  for(int i = 0; i < SIZEOF(rowPins); i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }
  for(int i = 0; i < SIZEOF(colPins); i++){
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }


  while(1){
//printf("abc\n");
    for(int k = 0; k <= 7; k++)
    {
//printf("p");
//delay(0.1f);
//printf("o");
      //turn all rows off
      //for(int i = 0; i < SIZEOF(rowPins); i++){
      //  digitalWrite(rowPins[i], LOW);
     // }

     //delay(1);

      for(int i = 0; i < 3; i++){
	digitalWrite(colPins[i], colOutputs[k][i]);
      }
     
      for(int i = 0; i < SIZEOF(rowPins); i++){
        //if(k == 0){
          digitalWrite(rowPins[i], HIGH);
        //}
       // else{
        //  digitalWrite(rowPins[i], LOW);
       // }
      }
      
      //if(k == 0){
        delay(15.0f);
     // }
    }
  }

//printf("millis is now %d",millis()-start);

printf("hello world\n");
}
