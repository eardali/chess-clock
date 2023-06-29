/*
		     USER'S ROUTINES DESCRIPTION:			
									
LCD_INIT() ----------->	initilalize the LCD. 				
			You must call it the first time you use the LCD	
			and before any other LCD routines.		
									
LCD_CLEAR() ---------->	Clears and Home LCD.			
									
LCD_CMD('char')	------>	Send a command to the LCD.			
			See LCD datasheet for the complete
			list of commands.
			
LCD_GOTO(line,pos) --->	Set the Cursor to a specified Line and position.
			Lines available are from 1 to 4. Pos available 
			starts from 1 to max available on your LCD.
			
LCD_PUTCH('char') ---->	Write a character on LCD (ASCII representation).

LCD_PUTS("string") --->	Write a string on LCD.

LCD_PUTUN(number)  --->	Write an Unsigned Number on LCD.
			It works both with INT (16bit) and CHAR (8bit).
			
LCD_PUTSN(number)  --->	Write a Signed Number on LCD (with Sign if <0).
			It works both with INT (16bit) and CHAR (8bit).
*/

void LCD_STROBE(void);
void LCD_NIBBLE_OUT(unsigned char);
void LCD_WRITE(unsigned char);
void LCD_CMD(char);
void LCD_GOTO(char,char);
void LCD_CLEAR(void);
void LCD_PUTCH(char);
void LCD_PUTUN(unsigned int);
void LCD_PUTUN2 (unsigned int c);
void LCD_PUTSN(signed int);
void LCD_PUTS(const char *);
void LCD_INIT(void);