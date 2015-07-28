#ifndef PIN_H
#define PIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

//#include "libs/LPC17xx/sLPC17xx.h" // smoothed mbed.h lib
#include "PinNames.h"

namespace mbed {
    class PwmOut;
    class InterruptIn;
}

class Pin {
    public:
        Pin();

        Pin* from_string(std::string value);

        inline bool connected(){
            return this->valid;
        }

        inline bool equals(const Pin& other) const {
            return (this->pin == other.pin) && (this->port == other.port);
        }

        inline Pin* as_output(){
            if (this->valid)
                this->port->DIR[this->pin] = 1;
            return this;
        }

        inline Pin* as_input(){
            if (this->valid)
                this->port->DIR[this->pin] = 0;
            return this;
        }

        Pin* as_open_drain(void);

        Pin* as_repeater(void);

        Pin* pull_up(void);

        Pin* pull_down(void);

        Pin* pull_none(void);

        inline bool get(){
            if (!this->valid) return false;
            return this->inverting ^ ( this->port->PIN[this->pin]);
        }

        inline void set(bool value)
        {
            if (!this->valid) return;
            if ( this->inverting ^ value )
                this->port->SET[this->pin] = 1;
            else
                this->port->CLR[this->pin] = 1;
        }

        mbed::PwmOut *hardware_pwm();

        mbed::InterruptIn *interrupt_pin();

        // these should be private, and use getters
        LPC_GPIO_T* port;

        uint8_t pin;
        char port_number;
        struct {
            bool inverting:1;
            bool valid:1;
        };
};




#endif
