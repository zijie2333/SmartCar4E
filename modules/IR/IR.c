#include "IR.h"
#include <project.h>

void IR_init(){
  CyGlobalIntEnable;
  ADC_SAR_Seq_1_Start();
  ADC_SAR_Seq_1_StartConvert();
}

float IR_query(){

  uint32 ADC_Result = 0;
  float dist;

  for (; ; ) {
    ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);
    ADC_Result = ADC_SAR_Seq_1_GetResult16(0);
    if (ADC_Result>0x7FFF) {
      ADC_Result = 0;
    }
    if (ADC_Result>0) {
      dist = 0.5/(0.00002*ADC_Result-0.00045)-2;
      return dist;
    }
  }
}
