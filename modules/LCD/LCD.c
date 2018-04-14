#include "LCD.h"
#include <project.h>

void LCD_init(){
    LCD_Char_Start();
    LCD_Char_LoadCustomFonts(LCD_Char_customFonts);

}

void LCD_disp(const char* str){
    LCD_Char_Position(0, 0);
    //LCD_Char_PrintString("error: ");
    //LCD_Char_Position(1, 0);
    LCD_Char_PrintString(str);
}
