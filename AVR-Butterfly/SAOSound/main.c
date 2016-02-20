/* Name: main.c
 * Author: Kiral Poon
 * Copyright: All copyright belongs to author
 * License:  normal public license
 * Freq_ref: http://www.phy.mtu.edu/~suits/notefreqs.html
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <lcd_functions.h>
#include <lcd_driver.h>

#include <stdio.h>
#include <inttypes.h>

int InitButterfly( void );
int InitSound( void );
#define beat 160 //default 500
#define volume 500 //default 500
int
InitButterfly( void )
{
  PCMSK0 = 0x00;
  PCMSK1 = 0x00;

  DIDR0 = 0x00;
  DIDR1 = 0x00;
  return 0;
}

int
InitSound( void )
{
  // Enable PortB5 output
  DDRB = DDRB | ( 1 << PB5 );
  // Set output pin Port B5 to 0
  PORTB = ( PORTB & ( ~ ( 1 << PB5 ) ) ) | ( 0 << PB5 );
  // Enable output compare toggle mode
  TCCR1A = ( TCCR1A & (~ ( ( 1 << COM1A1 ) | (1 << COM1A0) ) ) ) | ( ( 1 << COM1A1 ) | ( 0 << COM1A0 ) );
  // Enable phase and frequency correct mode, WGM=1000
  TCCR1B = ( TCCR1B & (~ ( ( 1 << WGM13 ) | (1 << WGM12) ) ) ) | ( ( 1 << WGM13 ) | ( 0 << WGM12 ) );
  TCCR1A = ( TCCR1A & (~ ( ( 1 << WGM11 ) | (1 << WGM10) ) ) ) | ( ( 0 << WGM11 ) | ( 0 << WGM10 ) );

  // Set clock to prescalar of 1
  TCCR1B = ( TCCR1B & (~ ( ( 1 << CS12 ) | ( 1 << CS11 ) | ( 1 << CS10 ) ) ) ) | ( ( 0 << CS12 ) | ( 0 << CS11 ) | ( 1 << CS10 ) );
  return 0;
}

int
noSound(void)
{
  OCR1A = 0;
  _delay_ms(50);
  return 0;
}
void my_delay_ms(int ms)
{
  while (0 < ms)
  {  
    _delay_ms(1);
    --ms;
  }
}
int
mute(int duration)
{
  OCR1A = 0;
  duration= duration * beat;
  my_delay_ms(duration);
  return 0;
}
int
not_mute(int duration)
{
  OCR1A = volume;
  duration= duration * beat;
  my_delay_ms(duration);
  noSound();
  return 0;
}
int
tone(uint16_t key)
{
  ICR1 = key;
  OCR1A = volume;
  _delay_ms(beat);
  noSound();
  return 0;
}
#define E_329 ( (uint16_t) ( 2000000UL / (329UL*2) ) )
#define F_349 ( (uint16_t) ( 2000000UL / (349UL*2) ) )
#define G_392 ( (uint16_t) ( 2000000UL / (392UL*2) ) )
#define A_440 ( (uint16_t) ( 2000000UL / (440UL*2) ) )
#define B_494 ( (uint16_t) ( 2000000UL / (494UL*2) ) )
#define C_523 ( (uint16_t) ( 2000000UL / (523UL*2) ) )
#define D_587 ( (uint16_t) ( 2000000UL / (587UL*2) ) )
#define E_659 ( (uint16_t) ( 2000000UL / (659UL*2) ) )
int main(void)
{
  cli();
  InitButterfly();
  LCD_Init();
  InitSound();
  sei();
    
  /* insert your hardware initialization here */
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "ICR1: %d", A_440);
  LCD_puts(buffer, 0);

  for(;;)
    {
      
      tone(C_523);
      tone(C_523);
      tone(C_523);
      tone(C_523);
      tone(B_494);
      tone(A_440);
      ICR1 = C_523;
      OCR1A = volume;
      not_mute(4);
      noSound();
      mute(4);

      mute(1);
      ICR1 = E_329;
      OCR1A = volume;
      _delay_ms(beat/4);
      noSound();
      tone(E_329);
      mute(1);
      tone(E_329);
      tone(E_329);
      tone(C_523);
      //tone(B_494);
      ICR1 = B_494;
      OCR1A = volume;
      not_mute(5);
      noSound();
      ICR1 = A_440;
      OCR1A = volume;
      not_mute(4);
      noSound();

      //2nd
      ICR1 = G_392;
      OCR1A = volume;
      not_mute(5);
      noSound();
      ICR1 = F_349;
      OCR1A = volume;
      not_mute(4);
      noSound();

      ICR1 = G_392;
      OCR1A = volume;
      not_mute(5);
      noSound();
      ICR1 = D_587;
      OCR1A = volume;
      not_mute(4);
      noSound();

      ICR1 = G_392;
      OCR1A = volume;
      not_mute(5);
      noSound();
      ICR1 = D_587;
      OCR1A = volume;
      not_mute(4);
      noSound();

      ICR1 = E_659;
      OCR1A = volume;
      _delay_ms(beat/4);
      noSound();
      tone(D_587);
      tone(C_523);
      ICR1 = B_494;
      OCR1A = volume;
      not_mute(4);
      noSound();
      ICR1 = C_523;
      OCR1A = volume;
      not_mute(5);
      noSound();

      //end
      mute(8);
    }
  return 0;   /* never reached */
}
