#include <project.h>
#include <stdio.h>
#include "IR.h"

void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}

int main()
{
    int dis;
    char string[50];
    CyGlobalIntEnable; /* Enable global interrupts. */

    LCD_Char_Start();
    LCD_Char_LoadCustomFonts(LCD_Char_customFonts);

    IR_init();

    for(;;)
    {
      dis = (int)(IR_query());
      IntToString(string, dis);
      LCD_Char_Position(0, 0);
      LCD_Char_PrintString("The IR Distant is ");
      LCD_Char_Position(1, 0);
      LCD_Char_PrintString("        ");
      LCD_Char_Position(1, 0);
      LCD_Char_PrintString(string);

      CyDelay(500);
    }
    return 0;
}
