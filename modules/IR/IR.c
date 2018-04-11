#include "IR.h"
#include <project.h>

void IR_init(){
  CyGlobalIntEnable;
  ADC_SAR_Seq_1_Start();
  ADC_SAR_Seq_1_StartConvert();
}

// 0 for left; 2 for middle; 1 for right; 10 for left_distant; 11 for right_distant
float IR_query(ID){

  if(ID==0 || ID==1 || ID==2){
    return ADC_polling(ID);
  } else if(ID==10 || ID==11){
    return ADC_polling(ID-10);
  } else {
      return -10086;
  }
}

float IR_normal_rst(){
    float th_blk_l = 1800;

    float IR_left = IR_query(0);
    float IR_mid = IR_query(2);
    float IR_right = IR_query(1);

    if (IR_right>th_blk && IR_mid<th_blk && IR_left<th_blk_l) {
      return 1;
    } else if (IR_right>th_blk && IR_mid>th_blk && IR_left<th_blk_l) {
      return 0.5;
    } else if (IR_right<th_blk && IR_mid>th_blk && IR_left<th_blk_l) {
      return 0;
    } else if (IR_right<th_blk && IR_mid>th_blk && IR_left>th_blk_l) {
      return -0.5;
    } else if (IR_right<th_blk && IR_mid<th_blk && IR_left>th_blk_l) {
      return -1;
    } else {
      return -10086;
    }
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
