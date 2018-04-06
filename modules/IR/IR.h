#ifndef IR_H_
#define IR_H_

void IR_init();  //initialize infraed distant sensor

float IR_query(int LR);  //query distance

float IR_normal_rst(float th_blk, float th_low, float th_high);//Normalization result

float ADC_polling(int pin);

#endif
