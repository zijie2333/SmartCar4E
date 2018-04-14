#include <project.h>
#include <stdio.h>
#include "encoder.h"

void IntToString(char *str, int number)
{
	sprintf(str, "%d", number);
}


int main()
{
	float v;
	char v_char[50];

	LCD_Char_Start();
	LCD_Char_LoadCustomFonts(LCD_Char_customFonts);

	encoder_init();

	for(;;)
	{
		v = (int)(10*encoder_query(0));
		IntToString(v_char, v);
		LCD_Char_Position(0, 0);
		LCD_Char_PrintString("encoder ");
		LCD_Char_Position(1, 0);
		LCD_Char_PrintString("        ");

		LCD_Char_Position(1, 0);
		LCD_Char_PrintString(v_char);

		CyDelay(500);
	}
	return 0;
}
