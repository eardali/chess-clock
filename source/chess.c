	#include <pic.h>  
	#include "delay.h"
	#include "LCD.h"
	#include "LCD_isr.h"

	enum keys{up=1, down, left, right, enter, nokey, undef} key;

	void my_long_delay(unsigned int);
	void my_init(void);
	enum keys my_keyinput(void);
	void my_test_keyinput(void);

	unsigned int value_pl1=90*60,value_pl2=01*60, pl1_min10=0,pl1_min1=0,pl2_min10=0,pl2_min1=0;//test minutes*60 secs
	unsigned int * value;
	unsigned char pl1_tmrlow=0x00,pl1_tmrhi=0x80,pl2_tmrlow=0x00,pl2_tmrhi=0x80;
	unsigned char min=0,sec=0,line=2,LCD_pos=0,LCD_pos_pl1=1,LCD_pos_pl2=8;

	
	void interrupt isr(void)
	{	unsigned char j;
		TMR1H=0x80;
		TMR1IF=0;
		/*//toggle portb.0
		j=PORTB&0b00000001;
		j=~j;
		PORTB=(PORTB|0b00000001)&j;
		//toggle end
		*/
		(*value)--;
		min=(*value)/60;
		sec=(*value)%60;
		isr_LCD_GOTO(2,LCD_pos);
		isr_LCD_PUTUN2(min);
		isr_LCD_GOTO(2,LCD_pos+3);
		isr_LCD_PUTUN2(sec);
	}
	
	void main()
	{
		unsigned char i=0,j=0;
		enum players{player1=1, player2} player=player2;
		//unsigned char arr[]={0x03,0x13,0x23,0x33,0x43,0x53,0x63,0x73,0x83,0x93,0xA3,0xB3,0xC3,0xD3,0xE3,0xF3},

		my_init();

		LCD_INIT();
		LCD_CLEAR();
		LCD_PUTS("ENTER PL1 TIME:");

		LCD_GOTO( line, LCD_pos_pl1);
		LCD_PUTS("00:00");
		LCD_GOTO( line, LCD_pos_pl2);
		LCD_PUTS("00:00");
		LCD_GOTO( line, LCD_pos_pl1);
		
		while(enter!=(key=my_keyinput()))
			{
				if(key==up)
					{
						pl1_min10++;
						pl1_min10=pl1_min10%10;
						LCD_GOTO(line, LCD_pos_pl1);
						LCD_PUTUN(pl1_min10);
						LCD_GOTO( line, LCD_pos_pl1);
						my_long_delay(2);
					}
				if(key==down)
					{
						pl1_min10--;
						pl1_min10=pl1_min10%10;
						LCD_GOTO(line, LCD_pos_pl1);
						LCD_PUTUN(pl1_min10);
						LCD_GOTO(line, LCD_pos_pl1);
						my_long_delay(2);
					}
			}

		//while(left!=(key=my_keyinput()));		//move cursor to left or put here a reasonable delay otherwise "enter" of last section would be valid for "enter" of the next section
		LCD_GOTO( line, LCD_pos_pl1+1);
		my_long_delay(2);
		
		while(enter!=(key=my_keyinput()))
			{
				if(key==up)
					{
						pl1_min1++;
						pl1_min1=pl1_min1%10;
						LCD_GOTO(line, LCD_pos_pl1+1);
						LCD_PUTUN(pl1_min1);
						LCD_GOTO(line, LCD_pos_pl1+1);
						my_long_delay(2);
					}
				if(key==down)
					{
						pl1_min1--;
						pl1_min1=pl1_min1%10;
						LCD_GOTO(line, LCD_pos_pl1+1);
						LCD_PUTUN(pl1_min1);
						LCD_GOTO(line, LCD_pos_pl1+1);
						my_long_delay(2);
					}
			}

		LCD_GOTO(1,1);
		LCD_PUTS("ENTER PL2 TIME:");
		LCD_GOTO( line, LCD_pos_pl2);
		my_long_delay(2);
		
		while(enter!=(key=my_keyinput()))
			{
				if(key==up)
					{
						pl2_min10++;
						pl2_min10=pl2_min10%10;
						LCD_GOTO(line, LCD_pos_pl2);
						LCD_PUTUN(pl2_min10);
						LCD_GOTO(line, LCD_pos_pl2);
						my_long_delay(2);
					}
				if(key==down)
					{
						pl2_min10--;
						pl2_min10=pl2_min10%10;
						LCD_GOTO(line, LCD_pos_pl2);
						LCD_PUTUN(pl2_min10);
						LCD_GOTO(line, LCD_pos_pl2);
						my_long_delay(2);
					}
			}

		LCD_GOTO( line, LCD_pos_pl2+1);
		my_long_delay(2);
		
		while(enter!=(key=my_keyinput()))
			{
				if(key==up)
					{
						pl2_min1++;
						pl2_min1=pl2_min1%10;
						LCD_GOTO(line, LCD_pos_pl2+1);
						LCD_PUTUN(pl2_min1);
						LCD_GOTO(line, LCD_pos_pl2+1);
						my_long_delay(2);
					}
				if(key==down)
					{
						pl2_min1--;
						pl2_min1=pl2_min1%10;
						LCD_GOTO(line, LCD_pos_pl2+1);
						LCD_PUTUN(pl2_min1);
						LCD_GOTO(line, LCD_pos_pl2+1);
						my_long_delay(2);
					}
			}

		LCD_WRITE(0b00001100);	//cursor off
		value_pl1=(10*pl1_min10+pl1_min1)*60;
		value_pl2=(10*pl2_min10+pl2_min1)*60;
		LCD_GOTO(1, 1);
		LCD_PUTS("WAIT PL1 START");

		
		/*LCD_INIT();
		LCD_CLEAR();
		LCD_PUTS("PLAYING");

		//write time values to display
		LCD_GOTO( line, LCD_pos_pl1);
		LCD_PUTUN2(value_pl1/60);
		LCD_GOTO( line, LCD_pos_pl1+2);
		LCD_PUTCH(':');
		LCD_GOTO( line, LCD_pos_pl1+3);
		LCD_PUTUN2(value_pl1%60);

		LCD_GOTO( line, LCD_pos_pl2);
		LCD_PUTUN2(value_pl2/60);
		LCD_GOTO( line, LCD_pos_pl2+2);
		LCD_PUTCH(':');
		LCD_GOTO( line, LCD_pos_pl2+3);
		LCD_PUTUN2(value_pl2%60);
		//end writing time values

		//test for key scan
		my_test_keyinput();*/
		
		//while (RD0==1)
		while (RC2==1)
		//while (0xFF==(PORTC|0xFB))

			{
			}	//wait until pl1 starts the game

		LCD_GOTO(1,1);
		LCD_PUTS("                ");	//clear first row only, ugly :)
		LCD_GOTO(1,1);
		LCD_PUTS("PLAYING: PL2");
		
		TMR1ON=1;	//start time and init of pl2
		value=&value_pl2;
		LCD_pos=LCD_pos_pl2;
		PORTC=PORTC|0b00100000;	//set portc.5
		PORTC=PORTC&0b11101111;	//reset portc.4
			
		//PORTC=PORTC&0b10111111;	//set portc.6 0

		while(1)
		{ 			
			i=PORTC|0xF3;	//0b11110011 read portc.2 and portc.3

			if(RC3==0)
			//if(RD1==0)	//PL2 hits the button
			//if(i==0xF7)	//if portc.3 is 0
				{
					value=&value_pl1;
					LCD_pos=LCD_pos_pl1;
					if(player==player2)
						{
							TMR1ON=0;	
							pl2_tmrhi=TMR1H;	//store player2 timings
							pl2_tmrlow=TMR1L;
							TMR1H=pl1_tmrhi;	//load player1 timings
							TMR1L=pl1_tmrlow+9;	//+3 is the missing time during store/restore it may change, investigate asm code
							TMR1ON=1;
							
							PORTC=PORTC|0b00010000;	//set portc.4
							PORTC=PORTC&0b11011111;	//reset portc.5
							LCD_GOTO(1,10);
							LCD_PUTS("PL1");		//select playing as PL1
							player=player1;
						}
				}
			else if (RC2==0)
			//else if (RD0==0)	//PL1 hits the button
			//else if (i==0xFB)	//if portc.2 is 0
				{	
					value=&value_pl2;
					LCD_pos=LCD_pos_pl2;
					if(player==player1)
						{	
							TMR1ON=0;	
							pl1_tmrhi=TMR1H;	//store player1 timings
							pl1_tmrlow=TMR1L;
							TMR1H=pl2_tmrhi;	//load player2 timings
							TMR1L=pl2_tmrlow+9;	//+3 is the missing time during store/restore it may change, investigate asm code
							TMR1ON=1;	

							PORTC=PORTC|0b00100000;	//set portc.5
							PORTC=PORTC&0b11101111;	//reset portc.4
							LCD_GOTO(1,10);
							LCD_PUTS("PL2");
							player=player2;
						}
				}
			else if ((RC2==0)&(RC3==0))
			//else if ((RD0==0)&(RD1==0))	//if both portc.2 and portc.3 is 0
			//else if (i==0xF3)	//if both portc.2 and portc.3 is 0
				{
					LCD_CLEAR();
					LCD_GOTO(1,1);
					LCD_PUTS("undefined case");
					break;	//should never occur
				}
			else
				{
				
				}
		}
	}

void my_init(void)
	{
		//these regs may be investigated and may be left as it is after reset
		//OPTION REG
		//OPTION=0x00;
		RBPU=0;    //disable portb pull ups, depend applicaiton
		INTEDG=0;      //don't care
		T0CS=0;        //don't care
		T0SE=0;        //don't care
		PSA=0;         //don't care
		PS2=0;         //don't care
		PS1=0;         //don't care
		PS0=0;         //don't care
	
	
		//INTCON REG
		//INTCON=0xC0;
		GIE=1;		 //enable global int.
		PEIE=1;        //enable pheripheral int.
		TMR0IE=0;      //T0 int disable
		INTE=0;        //ext int. disable
		RBIE=0;        //portb chaneg int. disable
		TMR0IF=0;      //T0 int flag
		INTF=0;	     //ext int. flag
		RBIF=0;	     //Portb change int. flag
		
		//PIE1 REG
		//PIE1=0x01;
		PSPIE=0;		//par. port int. disable
		ADIE=0;		//ADC int. disable
		RCIE=0;		//USART rx int. disable
		TXIE=0;		//USART tx int. disable
		SSPIE=0;		//serial port int. disable
		CCP1IE=0;		//CCP module int. disable
		TMR2IE=0;		//T2 int. disable
		TMR1IE=1;		//T1 int. enable
		
		//PIR1 REG
		//PIR1=0x00;
		PSPIF=0;		//par. port int. flag
		ADIF=0;		//ADC int. flag
		RCIF=0;		//USART rx int. flag
		TXIF=0;		//USART tx int. flag
		SSPIF=0;		//serial port int. flag
		CCP1IF=0;		//CCP moduke int. flag
		TMR2IF=0;		//T2 int. flag
		TMR1IF=0;		//T1 int. flag, clear by sw after overflow int!!!
		
		//PIE2 REG
		//PIE2=0x00;
		CMIE=0;		//comp. int. dis
		EEIE=0;		//eeprom int. dis
		BCLIE=0;		//bus collision int. dis
		CCP2IE=0;		//CCP int. dis
		
		//PIR2 REG
		//PIR2=0x00;
		CMIF=0;		//comp. int flag
		EEIF=0;		//eeprom int. flag
		BCLIF=0;		//bus collision int. flag
		CCP2IF=0;		//CCP int. flag
		
		//PCON REG
		//PCON=0x03;
		POR=1;	//no power on reset occured after first por
		BOR=1;	//no bor reset occured
		
		TMR1L=0x00;	//set timer regs
		TMR1H=0x80;	//set timer regs
		
		//Timer1 CON
		T1CKPS0=0;	//no prescaling
		T1CKPS1=0;	//no prescaling
		T1OSCEN=1;	//enable ext osc. it should be 32.768khz
		T1SYNC=1;	//no need to sync ext clk
		TMR1CS=1;		//sel ext osc
		TMR1ON=0;		//run/stop=1/0 timer1, start just after all inits
		
		TRISB=0xFF;	//all portb input
		
		TRISC=0x8F;    //portc.0, portc.1, portc.2 and portc.3 and portc.7 input, others output
		//PORTC=PORTC|0b01000000;	//set portc.6 zero
		
		TRISD=0x03;	//portd.0 and portd.1 input, all others output
		//PORTD=0X00;
	}

enum keys my_keyinput(void)
	{	
		char port_latch;
		enum keys key1;
		while (PORTB==0xFF)
			{
			}	//wait until any key is pressed

			DelayMs(5);	//wait for hw switch debouncing, adjust according to applicaiton. Long delay cause to miss the key hit ("nokey")
			port_latch=PORTB;
		switch(port_latch)
			{
				case 0xFE:
					key1=up;
					break;
				case 0xFD:
					key1=down;
					break;
				case 0xFB:
					key1=left;
					break;
				case 0xF7:
					key1=right;
					break;
				case 0xEF:
					key1=enter;
					break;
				case 0xFF:
					key1=nokey;
					break;
					//"nokey" means, any key hit is so short that it canot be detected!!!port changed its state to high meanwhile
				default:
					key1=undef;
					break;
					//undefined case
			}
		return key1;
	}



void my_test_keyinput(void)
	{char c;
		LCD_CLEAR();
		while(1)
			{	
				for (c=0;c<5;c++)
					DelayMs(256);	//clear lcd after a while
				LCD_CLEAR();
				
				key=my_keyinput();
				switch (key)
					{
						case up:
							LCD_PUTS("UP_OK");
							break;
						case down:
							LCD_PUTS("DOWN_OK");
							break;
						case left:
							LCD_PUTS("LEFT_OK");
							break;
						case right:
							LCD_PUTS("RIGHT_OK");
							break;
						case enter:
							LCD_PUTS("ENTER_OK");
							break;
						case nokey:
							LCD_PUTS("NO_KEY");
							break;
						default:
							LCD_PUTS("UPS WHATS UP? UNDEF");
							break;
					}
			}
	}

void my_long_delay(unsigned int c)
	{unsigned int i;
		for (i=0;i<c;i++)
			DelayMs(256);
	}

/*change value on bit765432 while bit10 are the same
i=PORTC|0xFC;	//0b11111100
PORTC=data&i;
//here last 2 bit of data must be high such as 0bxxxxxx11*/
