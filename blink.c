#define TCCR0A (*(volatile unsigned char*)0x44)
#define TCCR0B (*(volatile  unsigned char*)0x45)
#define TCNT0  (*(volatile  unsigned char*)0x46)

#define TIFR0  (*(volatile  unsigned char*)0x35)
#define DDRB   (*(volatile  unsigned char*)0x24)
#define PORTB  (*(volatile  unsigned char*)0x25)
#define TOV0 0

void delay_ms(unsigned int ms) {
    while (ms--) {
        TCNT0 = 0;
        TCCR0A = 0;
        TCCR0B = 1; 

        while ((TIFR0 & 1) == 0); 
        TIFR0 |= (1 << TOV0);               
    }
}

int main(void) {
    DDRB |= (1 << 5);

    while (1) {
        PORTB ^= (1 <<5);
        delay_ms(62500);
    }
}
