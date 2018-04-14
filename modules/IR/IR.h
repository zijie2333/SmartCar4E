#ifndef IR_H_
#define IR_H_

void IR_init();  //initialize infraed distant sensor

float IR_query(int LR);  //query distance

float ADC_polling(int pin);

#endif
