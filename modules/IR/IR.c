#include "IR.h"
#include <project.h>

void IR_init(){
  CyGlobalIntEnable;
  ADC_SAR_Seq_1_Start();
  ADC_SAR_Seq_1_StartConvert();
}

// 0 for left; 2 for middle; 1 for right; 10 for left_distant; 11 for right_distant
float IR_query(ID){

  //uint32 ADC_Result = 0;
  //float dist;
  if(ID==0 || ID==1 || ID==2){
    return ADC_polling(ID);
  } else if(ID==10 || ID==11){
    return ADC_polling(ID-10);
  } else { }

/*
  for (; ; ) {
    ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);
    ADC_Result = ADC_SAR_Seq_1_GetResult16(ID);
    if (ADC_Result>0x7FFF) {
      ADC_Result = 0;
    }
    if (ADC_Result>0) {
      dist = 0.5/(0.00002*ADC_Result-0.00045)-2;
      return dist;
    }
  }
*/

}

float ADC_polling(pin){
  uint32 ADC_Result = 0;
  float value;
  for (; ; ) {
    ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);
    ADC_Result = ADC_SAR_Seq_1_GetResult16(pin);
    if (ADC_Result>0x7FFF) {
      ADC_Result = 0;
    }
    if (ADC_Result>0) {
      value = (float)ADC_Result;
      return value;
    }
  }
}
