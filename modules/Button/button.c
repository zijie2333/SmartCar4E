# include <project.h>
# include "button.h"

void button_init(){

}

bool button_read(int ID){
     if (Button_Read()>0){
         return 1;
     } else{
         return 0;
     }
}
