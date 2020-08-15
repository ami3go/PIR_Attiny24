/*
 * PIRv0.c
 *
 * Created: 28.03.2018 19:40:25
 * Author : Ami_go
 */ 

// ATMEL ATTINY24 / ARDUINO
//                                           Actual PINOUT
//                                               +-\/-+
//                                         VCC  1|    |14  GND
//[*position 1] (1min )            (D  0)  PB0  2|    |13  AREF (D 10)   (60 min)    [*position 4]
//[*position 2] (5min)             (D  1)  PB1  3|    |12  PA1  (D  9)   (SPARE)
//             *Reset              (D 11)  PB3  4|    |11  PA2  (D  8)   AC line sync 
//             (pirout) PWM  INT0  (D  2)  PB2  5|    |10  PA3  (D  7)   (triac)
//[*position 3](30 min) PWM        (D  3)  PA7  6|    |9   PA4  (D  6)            *SCK
//             *MOSI    PWM        (D  4)  PA6  7|    |8   PA5  (D  5)        PWM *MISO
/*
 Positions (1,2,3,4) mean a 4 position switch where common contact is connected to gnd. 
 Reading switch position take following action:
 
    1. internal pull up resistors of all pins, which connected to switch, should be turned on
	2. pin state should be read, 
	3. than turned off all pull ups to save the power

For the delay software is using AC line IRQ: 
AC line syncs each 20 ms, so a simple down counter is ready.
It is better than use Timer because it drain less power, because times is off. 
 
 
 
*/


#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>


//macros definition
#define SET_BIT(PORT_NR,BIT) (PORT_NR |= (1<<BIT))
#define CLEAR_BIT(PORT_NR,BIT) (PORT_NR &= ~(1<<BIT))
#define bit_is_clear(sfr,bit) (!(_SFR_BYTE(sfr) & _BV(bit)))


//Switch soldering definition
#define SW0B   PINB0  /*POSITION 1 - 1 minutes;  SW0 <-> SWCOM */
#define SW1B   PINB1  /*POSITION 2 - 5 minutes;  SW1 <-> SWCOM */
#define SW2A   PINA7  /*POSITION 3 - 30 minutes; SW2 <-> SWCOM */
#define SW3A   PINA0  /*POSITION 4 - 60 minutes; SW3 <-> SWCOM */
#define SW4A   PINA1 /*NOT USED in current project*/
#define light  PORTA3
#define comp_in PINA2   

//#define one_minute_const 3000  // one tick is equal of 20 ms 
#define one_minute_const 3000  // one tick is equal of 20 ms 
//************************************************
// Global variable structure
//************************************************

typedef struct
{
   uint8_t  light_enable;
   uint16_t one_min_counter; // 3000 TIMES
   uint8_t min_counter; 
 
   
}global_var;

//************************************************
// Global variable declaration
//************************************************
volatile global_var gvar;


//functions prototypes 

//void analogCompInt(void);
uint8_t  time_selection(void);
void GPIOInt(void);
void SleepInt(void);
void Sleep_on(void);
void Sleep_off(void);
void PCIntIRQInt(void);
//Interrupt service request part 


ISR(PCINT0_vect){
	cli();
		Sleep_off();
		if (gvar.light_enable == 1) {
			
			if(bit_is_clear(PINA, comp_in)){
				
				gvar.one_min_counter--;
				
				if(gvar.one_min_counter == 0){
					
					gvar.one_min_counter = one_minute_const;
					gvar.min_counter--;
					
					if (gvar.min_counter == 0) gvar.light_enable = 0;
					
					}
				
				_delay_us(250);
				SET_BIT(PORTA,light);
				_delay_us(700);
				CLEAR_BIT(PORTA, light);
			}
			
			else {
				
				SET_BIT(PORTA,light);
				_delay_us(700);
				CLEAR_BIT(PORTA, light);
			}
			Sleep_on();
		}
		sei();
}

// if pir detected any movement
ISR(PCINT1_vect){
	
	Sleep_off();
	gvar.light_enable = 1;
	gvar.min_counter = time_selection();
	Sleep_on();
	
}


//************************************************
// MAIN SOFTWARE PART
//************************************************

int main(void)
{
    GPIOInt(); 
    PCIntIRQInt();
	sei();
	SleepInt();
	
	gvar.light_enable = 0;
	gvar.one_min_counter = one_minute_const;
	gvar.min_counter = 1; 
	
	Sleep_on();
    /* Replace with your application code */
    while (1) 
    {
	 //gvar.light_enable = 1;
   }
}

void GPIOInt (void){
	
	SET_BIT(DDRA,light);  //triac pin as output
	
	//switch pins configured as input. 	
	CLEAR_BIT(DDRB, SW0B);
	CLEAR_BIT(DDRB, SW1B);
	CLEAR_BIT(DDRA, SW2A);
	CLEAR_BIT(DDRA, SW3A);
}

void SleepInt(void){
	//disable burnout detector sequence 
	SET_BIT(MCUCR,BODS); 
	SET_BIT(MCUCR,BODSE); 
	_delay_us(1);
	SET_BIT(MCUCR,BODS); 
	CLEAR_BIT(MCUCR,BODSE); 
	_delay_us(5);
	
	//SET IDLE sleep mode
//	CLEAR_BIT(MCUCR,SM0);
//	CLEAR_BIT(MCUCR,SM1);
	
	//set power down mode
	  CLEAR_BIT(MCUCR,SM0);
	  SET_BIT(MCUCR,SM1);
}
void Sleep_on (void){
	SET_BIT(MCUCR,SE); 
}
void Sleep_off(void){
	CLEAR_BIT(MCUCR,SE); 
}

uint8_t time_selection(void ){
	
	uint8_t time = 0;
	
	
	//Turn on internal pull-up resistors
	SET_BIT(PORTA,SW2A);
	SET_BIT(PORTA,SW3A);
	SET_BIT(PORTB,SW0B);
	SET_BIT(PORTB,SW1B); 
		
	_delay_us(500);
	
	//Reading switch
	if(bit_is_clear(PINB, SW0B))  time = 1;
	if(bit_is_clear(PINB, SW1B))  time = 5;
	if(bit_is_clear(PINA, SW2A))  time = 30;
	if(bit_is_clear(PINA, SW3A))  time = 60;
	
	//Turn on internal pull-up resistors
	CLEAR_BIT(PORTA,SW2A);
	CLEAR_BIT(PORTA,SW3A);
	CLEAR_BIT(PORTB,SW0B);
	CLEAR_BIT(PORTB,SW1B);

	return time;
	
}



void PCIntIRQInt(void){
	
	CLEAR_BIT(MCUCR,ISC01); //any logical changes 
	SET_BIT(MCUCR,ISC00);
	
	SET_BIT(PCMSK0,PCINT2); // comparator pin
	
	SET_BIT(PCMSK1,PCINT10); //  pir pin
	
	SET_BIT(GIMSK,PCIE0); // comparator pin
	SET_BIT(GIMSK,PCIE1); // pir pin
	 
}

