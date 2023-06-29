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

#include<pic.h>
#include "delay.h"
#include "LCD.h"

/************************************************************************/
/* LCD Definitions
/************************************************************************/

#define	LCD_RS		RD2		// Register select
#define	LCD_EN		RD3		// Enable
#define	LCD_D4		RD4		// LCD data 4
#define	LCD_D5		RD5 	// LCD data 5
#define	LCD_D6		RD6		// LCD data 6
#define	LCD_D7		RD7		// LCD data 7



/************************************************************************/
/*  LCD Rows and Columns number	 	*/
/************************************************************************/

#define LCD_ROWS	2	// valid numbers are: 1,2
				// (set to 2 for 2 or more rows)
#define LCD_COLS	16	// valid numbers are: 8,16,20

#define LCD_CLR		0x01 // Clear Display
#define LCD_HOME		0x02 // Cursor to Home position

/************************************************************************/
#if (LCD_COLS==20)
	#define LCD_line1	0x80 // Line 1 position 1
	#define LCD_line2	0xC0 // Line 2 position 1
	#define LCD_line3	0x94 // Line 3 position 1 (20 char LCD)
	#define LCD_line4	0xD4 // Line 4 position 1 (20 char LCD)
#else
	#define LCD_line1	0x80 // Line 1 position 1
	#define LCD_line2	0xC0 // Line 2 position 1
	#define LCD_line3	0x90 // Line 3 position 1 (16 char LCD)
	#define LCD_line4	0xD0 // Line 4 position 1 (16 char LCD)
#endif
/************************************************************************/



/****************************************/
/* 	 Enable LCD to read data	*/
/****************************************/
void LCD_STROBE (void)
{
LCD_EN = 1;
DelayUs(1);
LCD_EN=0;
}


/****************************************/
/* 	Write a nibble to the LCD	*/
/****************************************/
void LCD_NIBBLE_OUT (unsigned char c )
{
if ( c & 0b10000000 )
        LCD_D7=1;
else LCD_D7=0;
if ( c & 0b01000000 )
        LCD_D6=1;
else LCD_D6=0;
if ( c & 0b00100000 )
        LCD_D5=1;
else LCD_D5=0;
if ( c & 0b00010000 )
        LCD_D4=1;
else LCD_D4=0;
LCD_STROBE();
}


/****************************************/
/* Write a byte to the LCD (4 bit mode) */
/****************************************/
void LCD_WRITE (unsigned char c)
{
LCD_NIBBLE_OUT(c);
c <<= 4;
LCD_NIBBLE_OUT(c);
DelayUs(50);
}


/****************************************/
/*       send a command to the LCD      */
/****************************************/
void LCD_CMD (char c)
{
LCD_RS = 0;	// write command
LCD_WRITE(c);
}


/****************************************/
/*  GoTO specified line and position    */
/****************************************/
void LCD_GOTO (char line,char pos)
{
switch(line)
	{
	case 1: LCD_CMD((LCD_line1-1)+pos);
		break;
	case 2: LCD_CMD((LCD_line2-1)+pos);
		break;
	case 3: LCD_CMD((LCD_line3-1)+pos);
		break;
	case 4: LCD_CMD((LCD_line4-1)+pos);
	}
}


/****************************************/
/*           Clear and Home LCD         */
/****************************************/
void LCD_CLEAR (void)
{
LCD_CMD(LCD_CLR);
DelayMs(3);
}


/****************************************/
/*     Write one character to the LCD   */
/****************************************/
void LCD_PUTCH (char c)
{
LCD_RS = 1;	// write characters
LCD_WRITE(c);
}


/****************************************/
/*        Write numbers to the LCD      */
/****************************************/
void LCD_PUTUN (unsigned int c)
{
unsigned char t1,i,wrote;
unsigned int k;

wrote=0;
for (i=4;i>=1;i--)
	{
	switch(i){
	case 4: k=10000;
		break;
	case 3: k=1000;
		break;
	case 2: k=100;
		break;
	case 1: k=10;
	}
	t1=c/k;
	if((wrote)||(t1!=0))
		{
		LCD_PUTCH(t1+'0');
		wrote=1;
		}
	c-=(t1*k);
	}
LCD_PUTCH(c+'0');
}
/********************************************************/
/*   Write numbers to the LCD      							*/
/*	isr_LCD_PUTUN(number) sends only one character to the LCD	*/
/*	if the number is one figure (i.e. 8)							*/
/*	isr_LCD_PUTUN2(number) send 2 chars to the LCD			*/
/*	i.e. if number is 8, send 0 and 8 chard to LCD				*/
/* 	good for clock display actions							*/
/********************************************************/
void LCD_PUTUN2 (unsigned int c)
{
unsigned char t1,i,wrote;
unsigned int k;

wrote=0;
for (i=4;i>=1;i--)
	{
	switch(i){
	case 4: k=10000;
		break;
	case 3: k=1000;
		break;
	case 2: k=100;
		break;
	case 1: k=10;
	}
	t1=c/k;
	if((wrote)||(t1!=0)||i==1)
		{
		LCD_PUTCH(t1+'0');
		wrote=1;
		}
	c-=(t1*k);
	}
LCD_PUTCH(c+'0');
}
/****************************************/
void LCD_PUTSN (signed int c)
{
if(c<0)
	{
	LCD_PUTCH('-');
	c*=(-1);
	}
LCD_PUTUN(c);
}


/****************************************/
/*       Write a string to the LCD      */
/****************************************/
void LCD_PUTS (const char * s)
{
LCD_RS = 1;	// write characters
while(*s)
	LCD_WRITE(*s++);
}

/****************************************/
/*             Initialize LCD           */
/****************************************/
void LCD_INIT (void)
{
LCD_RS = 0;		// write control bytes
DelayMs(15);		// power on delay
LCD_D4=1;
LCD_D5=1;
LCD_D6=0;
LCD_D7=0;
LCD_STROBE();
DelayMs(5);
LCD_STROBE();
DelayUs(100);
LCD_STROBE();
DelayMs(5);
LCD_D4=0;		// set 4 bit mode
LCD_STROBE();
DelayUs(40);

#if (LCD_ROWS==1)
LCD_WRITE(0b00100000);	// 4 bit mode, 1 line, 5x8 font
#else
LCD_WRITE(0b00101000);	// 4 bit mode, 2 or more lines, 5x8 font
#endif

LCD_WRITE(0b00001000);	// display off
//LCD_WRITE(0b00001100);	// display on, curson off, blink off
LCD_WRITE(0b00001110);	// display on, curson on, blink off
LCD_WRITE(0b00000110);	// shift entry mode, display not shifted

/*display control command
0b00001dcb
d:display on/off
c:cursor on/off
b:blinking on/off
*/
}

