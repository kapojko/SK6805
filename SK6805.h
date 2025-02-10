#ifndef SK6805_H
#define SK6805_H

#include  <stdint.h>

// NOTE: LEDs data protocol can be simulated with plain SPI (MOSI only)
// with appropriate timing (1 byte per 1.25us which gives SPI frequency 3.2 MHz),
// where 0 will be encoded with 0x80 and 1 will be encoded with 0xC0
#define SK6805_SPI_FREQ 3200000

// Encoding buffer size for one LED
#define SK6805_LED_ENCODING_SIZE 12

#define SK6805_LEDS_BUFFER_SIZE(ledsNumber) (ledsNumber * SK6805_LED_ENCODING_SIZE)

struct SK6805_Platform {
    void (*spiWrite)(uint8_t *data, uint16_t len);
    void (*delayUs)(uint16_t us);
};

void SK6805_Init(struct SK6805_Platform *platform);

// Encode single LED data to buffer, return pointer to next LED data
uint8_t *SK6805_EncodeLedData(uint32_t grbColor, uint8_t *data);

// Encode and transmit leds colors, buf must have size of SK6805_LEDS_BUFFER_SIZE(ledsNumber)
void SK6805_Transmit(uint32_t grbColors[], int ledsNumber, uint8_t *buf);

#endif // SK6805_H
