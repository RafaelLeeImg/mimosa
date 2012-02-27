#ifndef __MIMOSA_PC32_TRAP_H
#define __MIMOSA_PC32_TRAP_H
/*	
 *  Copyright (C) 2012
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

// Trap numbers
// These are processor defined:
#define T_DIVIDE     0		// divide error
#define T_DEBUG      1		// debug exception
#define T_NMI        2		// non-maskable interrupt
#define T_BRKPT      3		// breakpoint
#define T_OFLOW      4		// overflow
#define T_BOUND      5		// bounds check
#define T_ILLOP      6		// illegal opcode
#define T_DEVICE     7		// device not available 
#define T_DBLFLT     8		// double fault
/* #define T_COPROC  9 */	// reserved (not generated by recent processors)
#define T_TSS       10		// invalid task switch segment
#define T_SEGNP     11		// segment not present
#define T_STACK     12		// stack exception
#define T_GPFLT     13		// genernal protection fault
#define T_PGFLT     14		// page fault
/* #define T_RES    15 */	// reserved
#define T_FPERR     16		// floating point error
#define T_ALIGN     17		// aligment check
#define T_MCHK      18		// machine check
#define T_SIMDERR   19		// SIMD floating point error

// These are arbitrarily chosen, but with care not to overlap
// processor defined exceptions or interrupt vectors.
#define T_SYSCALL   48		// system call
#define T_DEFAULT   500		// catchall

#ifndef __ASSEMBLER__

#include <bsp/bsp_types.h>

struct PushRegs {
  /* registers as pushed by pusha */
  __u32_t reg_edi;
  __u32_t reg_esi;
  __u32_t reg_ebp;
  __u32_t reg_oesp;		/* Useless */
  __u32_t reg_ebx;
  __u32_t reg_edx;
  __u32_t reg_ecx;
  __u32_t reg_eax;
};

struct Trapframe {
  struct PushRegs tf_regs;
  __u16_t tf_es;
  __u16_t tf_padding1;
  __u16_t tf_ds;
  __u16_t tf_padding2;
  __u32_t tf_trapno;
  /* below here defined by x86 hardware */
  __u32_t tf_err;
  __uintptr_t tf_eip;
  __u16_t tf_cs;
  __u16_t tf_padding3;
  __u32_t tf_eflags;
  /* below here only when crossing rings, such as from user to kernel */
  __uintptr_t tf_esp;
  __u16_t tf_ss;
  __u16_t tf_padding4;
};


#endif // End of !__ASSEMBLER__

// Must equal 'sizeof(struct Trapframe)'.
// A static_assert in kern/trap.c checks this.
#define SIZEOF_STRUCT_TRAPFRAME	0x44

#endif // End of __MIMOSA_PC32_TRAP_H;
