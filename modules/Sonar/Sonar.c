#include <project.h>
#include "Sonar.h"
uint16 count=0;
char string[20];

void Sonar_init(){
	CyGlobalIntEnable;
	isr_Start();
	isr_Disable();
	isr_SetVector(InterruptHandler);
	isr_Enable(); 
}

CY_ISR(InterruptHandler)
{
	Timer_ReadStatusRegister();
    trigger_Write(0);
    Timer_Stop();
}

float Sonar_query()
{
    Timer_1_WriteCounter(10000);   
    CyDelay(40);
    trigger_Write(1);    
    Timer_Enable();
    Timer_Start();
    for(;;)
    {
        if(receiver_Read()==1) 
        {
    		Timer_1_Enable();
	        Timer_1_Start();
        	break;
        }
   	}
    for(;;)
    {
        if(receiver_Read()==0)
        {
        	Timer_1_Stop();
	    	break;
        }
    }
    uint32 dist;
	dist=(10000-Timer_1_ReadCounter())/6;
	dist=dist*10;
	if(float>=0) return (float)dist; else return -10086;
}

