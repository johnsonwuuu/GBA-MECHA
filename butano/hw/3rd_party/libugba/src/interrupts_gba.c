// SPDX-License-Identifier: MIT
//
// Copyright (c) 2020 Antonio Niño Díaz

#ifndef __GBA__
    #define __GBA__
#endif

#include <ugba/ugba.h>

#define BIOS_GLOBAL_IRQ_HANDLER     *(irq_vector *)(0x03007FFC)

extern void IRQ_GlobalInterruptHandler(void); // Assembly

irq_vector IRQ_VectorTable[UGBA_IRQ_NUMBER];

void IRQ_Init(void)
{
    REG_IME = 0;

    for (int i = 0; i < UGBA_IRQ_NUMBER; i ++)
        IRQ_VectorTable[i] = NULL;

    BIOS_GLOBAL_IRQ_HANDLER = IRQ_GlobalInterruptHandler;

    REG_IE = 0;
    REG_IF = 0x3FFF; // Clear IF

    // Enable interrupts after clearing the flags
    REG_IME = 1;
}

void IRQ_SetHandler(irq_index index, irq_vector function)
{
    IRQ_VectorTable[index] = function;
}

void IRQ_Enable(irq_index index)
{
    // Entering critical section. Disable interrupts.

    uint16_t old_ime = REG_IME;

    REG_IME = 0;

    if (index == UGBA_IRQ_HBLANK)
        REG_DISPSTAT |= DISPSTAT_HBLANK_IRQ_ENABLE;
    else if (index == UGBA_IRQ_VBLANK)
        REG_DISPSTAT |= DISPSTAT_VBLANK_IRQ_ENABLE;
    else if (index == UGBA_IRQ_VCOUNT)
        REG_DISPSTAT |= DISPSTAT_VCOUNT_IRQ_ENABLE;

    REG_IE |= (1 << index);

    REG_IME = old_ime;
}

void IRQ_Disable(irq_index index)
{
    uint16_t old_ime = REG_IME;

    // Entering critical section. Disable interrupts.

    REG_IME = 0;

    if (index == UGBA_IRQ_HBLANK)
        REG_DISPSTAT &= ~DISPSTAT_HBLANK_IRQ_ENABLE;
    else if (index == UGBA_IRQ_VBLANK)
        REG_DISPSTAT &= ~DISPSTAT_VBLANK_IRQ_ENABLE;
    else if (index == UGBA_IRQ_VCOUNT)
        REG_DISPSTAT &= ~DISPSTAT_VCOUNT_IRQ_ENABLE;

    REG_IE &= ~(1 << index);

    REG_IME = old_ime;
}
