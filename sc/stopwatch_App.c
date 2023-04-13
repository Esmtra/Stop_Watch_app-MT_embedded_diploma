 /******************************************************************************
 *
 * Name      :Stop_Watch_app
 * File Name :Stop_Watch_app.c
 * Author    :Eslam Mtra
 *
******************************************************************************/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char g_tick = 0;
unsigned char count_second_flag = 0;
unsigned char sec_count = 0;
unsigned char min_count = 0;
unsigned char h_count = 0;

ISR(TIMER1_COMPA_vect)// ISR for timer1 compare mode channel A
{
	count_sec_flag = 1;
}

void Timer1_Init_CTC_Mode(unsigned short tick)
{
	TCNT1 = 0; //timer initial value
	OCR1A  = tick; //compare value
	TIMSK |= (1<<OCIE1A); //enable compare interrupt for channel A
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

ISR(INT0_vect)// External INT0 ISR
{
	sec_count = 0;
	min_count = 0;
	h_count = 0;
}


ISR(INT1_vect)// External INT1 ISR
{
	// Pause the stop watch by disable the timer
	// Clear the timer clock bits (CS10=0 CS11=0 CS12=0) to stop the timer clock.
	TCCR1B &= 0xF8;
}

ISR(INT2_vect)// External INT2 ISR
{
	// resume the stop watch by enable the timer through the clock bits.
	TCCR1B |= (1<<CS10) | (1<<CS12);
}

void INT0_Init(void)// INT0 Enable
{
	// Configure INT0/PD2 as input pin
	DDRD  &= (~(1<<PD2));
	// Enable internal pull up resistor at INT0/PD2 pin
	PORTD |= (1<<PD2);
	// Trigger INT0 with the falling edge
	MCUCR &= ~(1<<ISC00);
	MCUCR |= (1<<ISC01);
	// Enable external interrupt pin INT0
	GICR  |= (1<<INT0);
}

void INT1_Init(void)//  INT1 Enable
{
	// Configure INT1/PD3 as input pin
	DDRD  &= (~(1<<PD3));
	// Trigger INT1 with the raising edge
	MCUCR |= (1<<ISC10);
	MCUCR |= (1<<ISC11);
	// Enable external interrupt pin INT1
	GICR  |= (1<<INT1);
}

void INT2_Init(void)//  INT2 Enable
{
	// Configure INT2/PB2 as input pin
	DDRB   &= (~(1<<PB2));
	// Enable internal pull up resistor at INT2/PB2 pin
    PORTB |= (1<<PB2);
	// Trigger INT2 with the falling edge
	MCUCSR &= !(1<<ISC2);
	// Enable external interrupt pin INT2
	GICR   |= (1<<INT2);
}

int main(void)
{
	// set 6 pins in PORTA as output
    DDRA |= 0x3F;

    // set first 4 pins of PORTC as output
	DDRC |= 0x0F;

	// Enable the 7-Segments
	PORTA |= 0x3F;
	PORTC &= 0xF0;

	// Enable global interrupts
	SREG  |= (1<<7);

	// Start timer1 to generate compare interrupt every 1000 MiliSeconds(1 Second)
	Timer1_Init_CTC_Mode(1000);

	// Activate external interrupt INT0
	INT0_Init();

	// Activate external interrupt INT1
	INT1_Init();

	// Activate external interrupt INT2
	INT2_Init();

    while(1)
    {
    	if(count_sec_flag == 1)
    	{
    		//enter here every one second
    		//increment seconds count
    		sec_count++;

    		if(sec_count == 60)
    		{
    			sec_count = 0;
    			min_count++;
    		}
    		if(min_count == 60)
    		{
    			min_count = 0;
    			h_count++;
    		}
    		if(h_count == 24)
    		{
    			h_count = 0;
    		}
    	    // reset the flag again
    	    count_sec_flag = 0;
    	}
    	else
    	{
    		// out the number of seconds
    		PORTA = (PORTA & 0xC0) | 0x01;
    		PORTC = (PORTC & 0xF0) | (sec_count%10);

    		// make small delay to see the changes in the 7-segment
    		// 2Miliseconds delay will not effect the seconds count
    		_delay_ms(2);

    		PORTA = (PORTA & 0xC0) | 0x02;
    		PORTC = (PORTC & 0xF0) | (sec_count/10);

    		_delay_ms(2);

    		// out the number of minutes
    		PORTA = (PORTA & 0xC0) | 0x04;
    		PORTC = (PORTC & 0xF0) | (min_count%10);

    		_delay_ms(2);

    		PORTA = (PORTA & 0xC0) | 0x08;
    	    PORTC = (PORTC & 0xF0) | (min_count/10);

    	    _delay_ms(2);

    	    // out the number of hours
    	    PORTA = (PORTA & 0xC0) | 0x10;
    	    PORTC = (PORTC & 0xF0) | (h_count%10);

    	    _delay_ms(2);

    	    PORTA = (PORTA & 0xC0) | 0x20;
    	    PORTC = (PORTC & 0xF0) | (h_count/10);

    	    _delay_ms(2);
    	}
    }
}
