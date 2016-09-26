#ifndef SHIFTOUT_H
#define SHIFTOUT_H

#include <mbed.h>

class ShiftOut {

    public :
    
        ShiftOut(PinName clk, PinName data, PinName latch, int8_t registerCount = 8) {
            clkout = new DigitalOut(clk);
            dataout = new DigitalOut(data);
            latchout = new DigitalOut(latch);
            this->registerCount = registerCount;
        }
        
        ~ShiftOut() {
            delete clkout;
            delete dataout;
            delete latchout;
        }
        
        void write(int8_t data) {
            *latchout = 0;
            for(int i = registerCount - 1; i >=  0; i--){
                wait_us(20);
                *clkout = 0;
                wait_us(20);
                *dataout = (data & (1 << i)) != 0;
                wait_us(20);
                *clkout = 1;
                wait_us(20);
            }
            wait_us(20);
            *latchout = 1;
            *clkout = 0;
            *dataout = 0 ;
        }
         
    private :
        DigitalOut *clkout;
        DigitalOut *dataout;
        DigitalOut *latchout;
        int8_t registerCount;     
};

#endif