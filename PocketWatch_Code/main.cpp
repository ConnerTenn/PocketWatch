

#include <avr/io.h>
#include <avr/interrupt.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

#define SET(port, mask, bits) port = ((port & (~(mask))) | ((bits) & (mask)))

unsigned long long timer = 1;
u8 tube = 0;


ISR(TIMER1_COMPA_vect)
{
	timer++;
}

void SetTimer()
{
	// Compare Match Interrupt Enable for Timer1
	TIMSK1 |= (1<<OCIE1A);
	// set timer1 counter initial value to 0
	TCNT1 = 0x0000;
	// set CTC mode (Allows use of OCR) and prescaler
	//TCCR1A |= (1<<WGM12);
	TCCR1B |= (1<<WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	//set compare register
	OCR1A = 0xAF;
	
	sei();
}

volatile u8 Numbers[10] = 
	{
		0b01111110,//0
		0b00001100,//1
		0b10110110,//2
		0b10011110,//3
		0b11001100,//4
		0b11011010,//5
		0b11111010,//6
		0b00001110,//7
		0b11111110,//8
		0b11011110 //9
	};

int main(void)
{
	SetTimer();
	
	/* Replace with your application code */
	SET(DDRB, 0b00000011, 0b00000011);
	SET(DDRD, 0b11111111, 0b11111111);
	
	SET(PORTB, 0b00000011, 0b00000000);
	//SET(PORTD, 0b11111111, 0b01100001);
	
	u8 i = 0;
	while (1)
	{
		//SET(DDRD, 0b11111111, Numbers[i]);
		SET(PORTD, 0b11111111, ~Numbers[i]);
		
		if (timer % 2 == 0)
		{
			SET(PORTB, 0b00000011, tube);
			tube = (tube < 2-1 ? tube+1 : 0);
		}
		
		if (timer % 500 == 0)
		{
			i++;
			if (i>=10) { i = 0; }
			timer++;
		}
	}
}

