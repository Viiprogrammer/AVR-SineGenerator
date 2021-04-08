//***************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru   
//
//  Target(s)...: ATMega
//
//  Compiler....: IAR, GCC, CodeVision
//
//  Description.: ???? ??? ???????????? ????????, ?????????? ?????????
//
//  Data........: 20.07.13
//
//***************************************************************************

#ifndef COMPILERS_H
#define COMPILERS_H

#include <stdint.h>

#include "config.h"

/*****************************************************************************/

#ifdef  __ICCAVR__

#include <ioavr.h>
#include <inavr.h>
#include <intrinsics.h>

#define STRINGIFY(a) #a   
#define ISR(vect) _Pragma(STRINGIFY(vector = vect))\
                  __interrupt void vect##_func(void)
#define INLINE _Pragma(STRINGIFY(inline = forced))

#define delay_us(us) 	__delay_cycles((F_CPU / 1000000) * (us))
#define delay_ms(ms) 	__delay_cycles((F_CPU / 1000) * (ms))
#endif

/*****************************************************************************/

#ifdef  __GNUC__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define __save_interrupt()       SREG
#define __restore_interrupt(var) SREG = (var)
#define __disable_interrupt()    cli()
#define __enable_interrupt()     sei()
#define __delay_cycles(var)      _delay_us((uint16_t)(var)/(F_CPU/1000000))
#define delay_us(us) 	         _delay_us(us)
#define delay_ms(ms)             _delay_ms(ms)	
#define __swap_nibbles(x)        (((x<<4)&0xf0)|((x>>4)&0x0f))

#define INLINE inline
#endif

/*****************************************************************************/

#ifdef __CODEVISIONAVR__

#include <io.h>
#include <delay.h>

#define __save_interrupt()       SREG
#define __restore_interrupt(var) SREG = (var)
#define __disable_interrupt()    #asm("cli")
#define __enable_interrupt()     #asm("sei")
#define __delay_cycles(var)      delay_us((unsigned int)(var)/(_MCU_CLOCK_FREQUENCY_/1000000))
#define __swap_nibbles(x)        (((x<<4)&0xf0)|((x>>4)&0x0f))

#define ISR(vect) interrupt [vect] void vect##_func(void)
#define INLINE inline
#endif

/*****************************************************************************/


#endif //COMPILERS_H

