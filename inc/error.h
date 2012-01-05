#ifndef __MIMOSA_ERROR_H
#define __MIMOSA_ERROR_H
/*	
 *  Copyright (C) 2010-2011  
 *	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <types.h>
#include <retval.h>

#ifndef __KERN_DEBUG__
//#include <console.h>
/* FIXME: 1. if no debug, panic must be halted
 *        2. use _panic if cprintf is done
 */
//#define panic(...)  _panic(__FILE__ ,__LINE__ ,__VA_ARGS__)
#define panic(...)
#else
#include <debug/display.h>
// FIXME: I need format!
#define panic(str)  \
  do{ msg_print(str); halt(); }while(0);

#endif

#define ASSERT_OUTFMT "func:%s in file:%s Assert:\"%s\" failed!\n"

#define __assert_print(p)	\
  panic(ASSERT_OUTFMT ,__FUNCTION__ ,__FILE__ ,#p)

#define assert(p)	\
  do{ if(!(p)) __assert_print(p); }while(0);

/*
#define assert(x)		\
	do { if (!(x)) panic("assertion failed: %s", #x); } while (0)
*/

/* FIXME: use these functions while finished format printf;
#define warn(...) _warn(__FILE__, __LINE__, __VA_ARGS__)
#define panic(...) _panic(__FILE__, __LINE__, __VA_ARGS__)


// func declaration;
static void _warn(const char*, int, const char*, ...);
static void _panic(const char*, int, const char*, ...) no_return;
*/

static inline void halt();
static inline void halt()
{
  while(1);
}

static void print_errmsg(retval rv);


//void _panic(const char *file, int line, const char *fmt,...);
//void _warn(const char *file, int line, const char *fmt,...);

#endif // End of __MIMOSA_ERROR_H;



