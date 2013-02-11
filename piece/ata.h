#ifndef STDINC_H_INCLUDED
#include "stdinc.h"
#define STDINC_H_INCLUDED
#endif

#ifndef TIMER_H_INCLUDED
#include "timer.h"
#define TIMER_H_INCLUDED
#endif

BOOL ata_wait_until_not_busy(uint32_t timeout_ms);
void ata_send_command(unsigned char command);
void ata_select_drive(uint8_t drive);
void ata_interrupt_enable(BOOL enable);
BOOL ata_read_lba28(uint32_t LBA, uint8_t sectorCount, void* dest);

