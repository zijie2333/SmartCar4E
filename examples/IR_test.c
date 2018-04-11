#include <project.h>
#include <stdio.h>
#include "IR.h"

void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}

int main()
{
    int dist_int;
    char dist_str[50];
    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Char_Start();
    LCD_Char_LoadCustomFonts(LCD_Char_customFonts);

    IR_init();

    for(;;)
    {
      dist_int = (int)(IR_normal_rst(0,0,0));
      IntToString(dist_str, dist_int);
      LCD_Char_Position(0, 0);
      LCD_Char_PrintString("Left IR Dist is ");
      LCD_Char_Position(1, 0);
      LCD_Char_PrintString("        ");

      LCD_Char_Position(1, 0);
      LCD_Char_PrintString(dist_str);

      CyDelay(500);
    }
    return 0;
}
