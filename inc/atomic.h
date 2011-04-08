#ifndef	__MIMOSA_ATOMIC_H
#define __MIMOSA_ATOMIC_H
/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
   
 * NalaGinrut <NalaGinrut@gmail.com>
 
 * May Lord Bless!Happy Hacking!
 
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
 
 * You should have read the GNU General Public License before start "RTFSC".
 
 * If not,see <http://www.gnu.org/licenses/>
 */


#include <now/bsp_atomic.h>

#define atomic_set_bit(l ,o)	__atomic_set_bit(l ,o)
#define atomic_clear_bit(l ,o)	__atomic_clear_bit(l ,o)

#endif // End of __MIMOSA_ATOMIC_H;