/* 
 * File:   blink_main.c
 * Author: Luke Hodgkin
 *
 * Created on April 10, 2024
 */



#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#define del 10 

/*
    This source file will implement an interface to the TI SN74HC595N 8 - Bit Shift Register
    This will utilize the SR as an output I/O Exapnsion. 
    We will use a integer to store the data which will be shifted out into the register to be output. 
    This will use 3 output pins. 
    This function will work on PORTB Pins 
    The first time we will assume shifting out the LSB 

    Revised: April 16, 2024 Luke Hodgkin
    Added functionality option to output either
    LSB First and MSB First to the shift register. 

*/

void SR_out(int SRclk , int Rclk , int dataPin, int value , int LSB)
{
 
    if(LSB == 1) 
        for (int i = 0; i < 8 ; i++) 
        {
                // Outputs using LSB first
            
                if(!!(value & 0x01)) PORTB |= (0x01<< dataPin); // Set output data pin
                else PORTB &= ~(0x01<< dataPin);
                value >>= 1 ;       // Bit shift right the value being shifted out to SR
            
                    // Then Toggle the SRclk pin
            PORTB |= (0x01 << SRclk);
            PORTB &= ~(0x01 << SRclk); 

        }

    else if(LSB == 0)       // Outputs using MSB first
    {   
        value <<= 8;

        for (int i = 0; i < 8 ; i++)
        {
            if(!!(value & 0x8000)) PORTB |= (0x01<< dataPin); // Set output data pin
            else PORTB &= ~(0x01<< dataPin);
            value <<= 1 ;
        
        // Then Toggle the SRclk pin
        PORTB |= (0x01 << SRclk);
        PORTB &= ~(0x01 << SRclk); 
        }
    }

    
    // Toggle the Rclk pin to putput the value shifted in.
    PORTB |= (0x01 << Rclk); 
    PORTB &= ~(0x01 << Rclk);

}


// This will test the function of the bit shift out to the shift register.

int main()
{
    DDRB = 0b00000111;      // Set the Output Pins
    int SRclk = 0; 
    int Rclk = 1; 
    int dataPin = 2; 
    int LSB = 1; 

    while(1)
    {
        LSB ^= 0x01;  // Toggle the mode of the SR between MSB and LSB after counting to 256. 
        for(int i = 0; i < 256; i++)
        {
            _delay_ms(200);

            SR_out(SRclk , Rclk , dataPin , i , LSB); 

        }

    }


    return 0; 
}


