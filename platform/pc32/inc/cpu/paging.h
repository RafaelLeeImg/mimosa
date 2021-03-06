#ifndef __MIMOSA_PC32_PAGING_H
#define __MIMOSA_PC32_PAGING_H
/*	
 *  Copyright (C) 2010-2012
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

#ifndef __ASSEMBLER__

#include <bsp/bsp_types.h>
#include <bsp/bsp_bits.h>
#include <osconfig.h>
#include "crx.h"

#ifdef __BIT32_PAGING__


#ifdef __BIT32_PAGING_NO_PSE__
typedef __u32_t __laddr_t;

//--- PDE definition;
#define PDE_PRESENT	_B(0)
#define PDE_WRITE	_B(1) // no PTE_READ since any page can be read
#define PDE_USER	_B(2)
#define PDE_WRITE_TH	_B(3)
#define PDE_CACHE_D	_B(4)
#define PDE_ACCESSED	_B(5)
#define PDE_PAGE4MB	_B(6)
#define PDE_GLOBAL	_B(7)
#define PDE_PT_ADDR	FLAG_FIX(20 ,12)

typedef __u32_t __pde_t; // Page Directory Entry;

//--- PTE definition;
#define PTE_PRESENT	_B(0)
#define PTE_WRITE	_B(1) // no PTE_READ since any page can be read
#define PTE_USER	_B(2)
#define PTE_WRITE_TH	_B(3)
#define PTE_CACHE_D	_B(4)
#define PTE_ACCESSED	_B(5)
#define PTE_DIRTY	_B(6)
#define PTE_PAT		_B(7)
#define PTE_GLOBAL	_B(8)
#define PTE_ADDR	FLAG_FIX(20 ,12)

typedef __u32_t __pte_t;


#else //__BIT32_PAGING_PAE__

// TODO: PAE support

#endif // End of __BIT32_PAGING_NO_PAE;__

#endif // End of __BIT32_PAGING__;


//--- definition of Page Fault Error Code;
typedef __u32_t pfec_t; // Page Fault Error Code; 
#define PFEC_P	_B(0) /* 1 caused by page-level-proctection ,
		       * 0 for page-not-present;
		       */
#define PFEC_WR	_B(1) // 1 caused by page-can't-write ,0 for read;
#define PFEC_US	_B(2) // 1 caused by excute-while-CPL=3 ,0 for CPL<3;
#define PFEC_RS	_B(3) /* 1 caused by reserved-bits-not-clear;
		       * this bit is set only-under PFEC_P is set ,
		       * because page-bit check only under page-presented
		       * situation ,
		       * 0: error not caused by reserved bits;
		       */
#define PFEC_ID	_B(4) /* 1 caused by instruction-fetch;
		       * 0: error not caused by instruction-fetch;
		       * NOTE: USELESS UNDER 32BIT-PAGE MODE(CR4.PAE=0 or 
		       * IA32_EFER.NXE=0);
		       */

// page number field of address
#define PPN(la)		(((laddr_t)(la)) >> PTX_SHIFT)
#define VPN(la)		PPN(la)		// used to index into vpt[]

// page directory index
#define PDX(la)		((((laddr_t)(la)) >> PDX_SHIFT) & 0x3FF)
#define VPD(la)		PDX(la)		// used to index into vpd[]

// page table index
#define PTX(la)		((((laddr_t)(la)) >> PTX_SHIFT) & 0x3FF)

// offset in page
#define PGOFF(la)	(((laddr_t)(la)) & 0xFFF)

// next pte addr in pte
#define PTA(pte)	((physaddr_t)(pte) & ~0xFFF)

// construct linear address from indexes and offset
#define PGADDR(d, t, o)	((void*) ((d) << PDX_SHIFT | (t) << PTX_SHIFT | (o)))

#define page_enable()  cr0_set(cr0_get() | CR0_PG)

/* handle paging mode */
#ifdef PG_SIZE
#define PTX_SHIFT PG_SHIFT
#define PDX_SHIFT 22
#endif // End of PG_SIZE;

static inline void global_pages_enable() __true_inline;
static inline void global_pages_disable() __true_inline;

static inline void global_pages_enable()
{
  cr4_set(cr4_get() | CR4_PGE); 
}

static inline void global_pages_disable()
{
  cr4_set(cr4_get() & ~CR4_PGE);
}

#ifdef __486_COMPAT
#define TLB_flush_mem(mem) 	
#else
static inline void TLB_flush_mem(void *mem) __true_inline;
static inline void TLB_flush_mem(void *mem)
{
  __asm__ volatile("invlpg %0\n\t"
		   :
		   :"m" (mem)
		   );
}
#endif //End of __486_COMPAT




#endif // !__ASSEMBLER__

#endif // End of __MIMOSA_PC32_PAGING_H;
