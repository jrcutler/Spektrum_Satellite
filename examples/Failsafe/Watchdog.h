#ifndef WATCHDOG_H
#define WATCHDOG_H

#ifdef __AVR__

#include <avr/wdt.h>

#if defined(__AVR_AT90CAN32__) \
|| defined(__AVR_AT90CAN64__) \
|| defined(__AVR_AT90CAN128__) \
|| defined(__AVR_AT90PWM1__) \
|| defined(__AVR_AT90PWM2__) \
|| defined(__AVR_AT90PWM216__) \
|| defined(__AVR_AT90PWM2B__) \
|| defined(__AVR_AT90PWM3__) \
|| defined(__AVR_AT90PWM316__) \
|| defined(__AVR_AT90PWM3B__) \
|| defined(__AVR_AT90USB1286__) \
|| defined(__AVR_AT90USB1287__) \
|| defined(__AVR_AT90USB162__) \
|| defined(__AVR_AT90USB646__) \
|| defined(__AVR_AT90USB647__) \
|| defined(__AVR_AT90USB82__) \
|| defined(__AVR_ATmega1280__) \
|| defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega1284P__) \
|| defined(__AVR_ATmega164__) \
|| defined(__AVR_ATmega164P__) \
|| defined(__AVR_ATmega165__) \
|| defined(__AVR_ATmega165P__) \
|| defined(__AVR_ATmega168__) \
|| defined(__AVR_ATmega168P__) \
|| defined(__AVR_ATmega169__) \
|| defined(__AVR_ATmega169P__) \
|| defined(__AVR_ATmega16HVA__) \
|| defined(__AVR_ATmega2560__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega324__) \
|| defined(__AVR_ATmega324P__) \
|| defined(__AVR_ATmega325__) \
|| defined(__AVR_ATmega3250__) \
|| defined(__AVR_ATmega328P__) \
|| defined(__AVR_ATmega329__) \
|| defined(__AVR_ATmega3290__) \
|| defined(__AVR_ATmega3290P__) \
|| defined(__AVR_ATmega32C1__) \
|| defined(__AVR_ATmega32HVB__) \
|| defined(__AVR_ATmega32M1__) \
|| defined(__AVR_ATmega32U4__) \
|| defined(__AVR_ATmega32U6__) \
|| defined(__AVR_ATmega406__) \
|| defined(__AVR_ATmega48__) \
|| defined(__AVR_ATmega48P__) \
|| defined(__AVR_ATmega640__) \
|| defined(__AVR_ATmega644__) \
|| defined(__AVR_ATmega644P__) \
|| defined(__AVR_ATmega645__) \
|| defined(__AVR_ATmega6450__) \
|| defined(__AVR_ATmega649__) \
|| defined(__AVR_ATmega6490__) \
|| defined(__AVR_ATmega8HVA__) \
|| defined(__AVR_ATmega88__) \
|| defined(__AVR_ATmega88P__) \
|| defined(__AVR_ATtiny48__) \
|| defined(__AVR_ATtiny88__) \
|| defined(__AVR_ATtiny167__)

/* Use STS instruction. */
#define wdt_enable_irq(value)   \
    __asm__ __volatile__ ( \
        "in __tmp_reg__,__SREG__" "\n\t" \
        "cli" "\n\t" \
        "wdr" "\n\t" \
        "sts %0,%1" "\n\t" \
        "out __SREG__,__tmp_reg__" "\n\t" \
        "sts %0,%2" "\n\t" \
        : /* no outputs */ \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
        "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDIE) | (value & 0x07)) ) \
        : "r0" \
    )

#else

/* Use OUT instruction. */
#define wdt_enable_irq(value) \
    __asm__ __volatile__ ( \
        "in __tmp_reg__,__SREG__" "\n\t" \
        "cli" "\n\t" \
        "wdr" "\n\t" \
        "out %0,%1" "\n\t" \
        "out __SREG__,__tmp_reg__" "\n\t" \
        "out %0,%2" \
        : /* no outputs */ \
        : "I" (_SFR_IO_ADDR(_WD_CONTROL_REG)), \
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
        "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDIE) | (value & 0x07)) ) \
        : "r0" \
    )

#endif

#endif /* __AVR__ */

#endif /* !WATCHDOG_H */