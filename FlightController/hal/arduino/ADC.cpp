#include "ADC.h"

#include <avr/interrupt.h>

namespace Adc
{
    volatile uint16_t readings[N_ADC_CHANNELS];
    volatile uint8_t currentChannel(0);
}

void Adc::init()
{
    // Disable power reduction for ADC
    PRR0 &= ~(1 << PRADC);

    // Select AVCC as source
    ADMUX = (1 << REFS0);

    // Enable ADC, NO Auto-Trigger, Prescaler=128 to keep ADC clock between 50 and 200 kHz,
    // Enable ADC interrupt.
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADIE) |
            (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t Adc::Power::readVoltage()
{
    return readings[ADC_CHANNEL_VOLTAGE];
}

uint16_t Adc::Power::readCurrent()
{
    return readings[ADC_CHANNEL_CURRENT];
}

ISR(ADC_vect)
{
    // Store current reading
    Adc::readings[Adc::currentChannel] = ADCW;

    // Update counter
    Adc::currentChannel++;
    if (Adc::currentChannel >= N_ADC_CHANNELS) // This is faster than using mod, although it looks dummy
    {
        Adc::currentChannel = 0;
    }

    // Update MUX for next conversion
    ADMUX = (ADMUX & MUX_MASK_INV) | Adc::currentChannel;

    // Start new conversion
    ADCSRA |= (1 << ADSC);
}

