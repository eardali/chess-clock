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

/***************************************************************************
This header and c file has to be dublicated since it does not allow to call the same functions form 
interrupt service routine (isr) and main function!!!!!!!!!!!
***************************************************************************/

void isr_LCD_STROBE(void);
void isr_LCD_NIBBLE_OUT(unsigned char);
void isr_LCD_WRITE(unsigned char);
void isr_LCD_CMD(char);
void isr_LCD_GOTO(char,char);
void isr_LCD_CLEAR(void);
void isr_LCD_PUTCH(char);
void isr_LCD_PUTUN(unsigned int);
void isr_LCD_PUTUN2 (unsigned int c);
void isr_LCD_PUTSN(signed int);
void isr_LCD_PUTS(const char *);
void isr_LCD_INIT(void);