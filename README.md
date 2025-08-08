
# AVR Timer0 Overflow Delay Example

This project demonstrates how to use the **Timer0 overflow** feature of the **ATmega328P** microcontroller to implement a simple delay function in C using direct register access.

## Files

- `main.c`: Source code for toggling an LED using Timer0 overflow delay.
- `README.md`: This file.

## Description

This program:

1. Sets up Timer0 without a prescaler (i.e., clock source = system clock).
2. Uses overflow flag `TOV0` in the `TIFR0` register to detect when the timer overflows.
3. Toggles an LED connected to **PORTB5** (typically the on-board LED on Arduino Uno) every ~62.5 seconds.

## Registers Used

- `TCCR0A` (0x44): Timer/Counter Control Register A
- `TCCR0B` (0x45): Timer/Counter Control Register B
- `TCNT0`  (0x46): Timer/Counter Register (8-bit)
- `TIFR0`  (0x35): Timer/Counter Interrupt Flag Register
- `PORTB`  (0x25): Port B Data Register
- `DDRB`   (0x24): Port B Data Direction Register

## Code Explanation

```c
#define TCCR0A (*(volatile unsigned char*)0x44)
#define TCCR0B (*(volatile unsigned char*)0x45)
#define TCNT0  (*(volatile unsigned char*)0x46)
#define TIFR0  (*(volatile unsigned char*)0x35)
#define DDRB   (*(volatile unsigned char*)0x24)
#define PORTB  (*(volatile unsigned char*)0x25)
#define TOV0 0

void delay_ms(unsigned int ms) {
    while (ms--) {
        TCNT0 = 0;
        TCCR0A = 0;
        TCCR0B = 1; // No prescaling

        while ((TIFR0 & 1) == 0);  // Wait for overflow (TOV0 set)
        TIFR0 |= (1 << TOV0);      // Clear the overflow flag by writing 1
    }
}

int main(void) {
    DDRB |= (1 << 5); // Set PORTB5 as output

    while (1) {
        PORTB ^= (1 << 5); // Toggle LED
        delay_ms(62500);   // Delay ~62.5 seconds using overflow loop
    }
}
```

## Notes

- Each overflow occurs every 256 CPU cycles since Timer0 is 8-bit.
- At 16 MHz CPU frequency, each overflow takes `256 / 16,000,000 = 16 µs`.
- `delay_ms(62500)` results in a total delay of `62500 * 16 µs = 1 second (approx)`.
- This is a low-level implementation that avoids using built-in AVR libraries.

## Author

MD. JESAN
