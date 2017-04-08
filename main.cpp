#include "mbed.h"

void onPulseInterrupt();
uint32_t calculateRPM();
void startRPMTimer();

DigitalOut led(LED1);
InterruptIn pulse(BTN0);
Timer timer;
int counter = 0;
#define ONE_SECOND  1000000
typedef struct
{
  bool counting;
  uint32_t startTime;
  uint32_t passTime;
}Time_;

Time_ anemoTime;

int main() {

  anemoTime.counting = false;
  pulse.rise(&onPulseInterrupt);
  

  while(true){
    wait(5.0);
     printf("alive\r\n");
     led = 1;
     wait(2.0);
     led = 0;
    
    if(!anemoTime.counting)
    {
      printf("RPM: %u\r\n", calculateRPM());
    }
    else sleep();
  }
}

uint32_t calculateRPM()
{
  uint32_t timeOneRound = anemoTime.passTime - anemoTime.startTime;
  
  return  ONE_SECOND * 60 / timeOneRound; 

}

void startRPMTimer()
{
  timer.start();
  anemoTime.counting = true;
}
void onPulseInterrupt()
{
  counter++;
  if (!anemoTime.counting)
  {
    timer.reset();
    anemoTime.counting = true;
    anemoTime.startTime = timer.read_us();
    
  }
  else
  {
    anemoTime.passTime = timer.read_us();
    anemoTime.counting = false;

  }
}
