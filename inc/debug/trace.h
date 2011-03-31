#ifndef __MIMOSA_DEBUG_TRACE_H
#define __MIMOSA_DEBUG_TRACE_H
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


#include <retnum.h>
#include <types.h>
#include <error.h>

typedef struct FrameInfo
{
  //TODO: all info about frame, argc,args, others.....;
}frame_info;// should we need pass frame_info pointer to accelerate??

retnum pcall_backtrace(frame_info fi ,u32_t back_count);  




#endif // End of __MIMOSA_DEBUG_TRACE_H;
