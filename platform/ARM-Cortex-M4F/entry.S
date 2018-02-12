.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.text

.global _start
.extern platform_init /* C function must be declared as .extern in AVR asm code */

_start:
        /* TODO: do something init, maybe stack clean? */
        /* NOTE: AVR asm in gcc seems not support AT&T style */
  mov     r1, #0    /* r1 must be 0 before calling C function */
  bl   platform_init /* `call' is not supported by AVR2 model */


/******************************************************************************/
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr   sp, = __mimosa_MIMOSA_BSP_KSTKTOP     /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, = __init_start
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, = bsp_begin
  ldr  r3, = bsp_end
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =__bss_start
  b  LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4

LoopFillZerobss:
  ldr  r3, = __bss_end
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit

/******************************************************************************/

#include "irq_vectors.S"
