#ifndef IR_H_
#define IR_H_

#define th_blk 1600

void IR_init();  //initialize infraed distant sensor

float IR_query(int LR);  //query distance

float IR_normal_rst();//Normalization result

float ADC_polling(int pin);

#endif
