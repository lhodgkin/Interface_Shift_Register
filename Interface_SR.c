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

*/

void SR_out(int SRclk , int Rclk , int dataPin, int value , int LSB)
{

    
    for (int i = 0; i < 8 ; i++) 
    {
        // Set output data pin
        // This statment only turns on the the serial pin but dies not turn it off. 
        if(!!(value & 0x01))
        {
            PORTB |= (0x01<< dataPin);
        }
        else 
        {
            PORTB &= ~(0x01<< dataPin);
        }
        value >>= 1 ;        // Bit shift right the value being shifted out to SR



        // Then Toggle the SRclk pin
        //_delay_ms(del);
        PORTB |= (0x01 << SRclk);
        //_delay_ms(del);
        PORTB &= ~(0x01 << SRclk); 



    }
    // Toggle the Rclk pin to putput the value shifted in.
    //_delay_ms(del); 
    PORTB |= (0x01 << Rclk); 
    //_delay_ms(del);
    PORTB &= ~(0x01 << Rclk);
    

}


// This will test the function of the bit shift out to the shift register.

int main()
{
    DDRB = 0b00000111;
    int SRclk = 0; 
    int Rclk = 1; 
    int dataPin = 2; 


    while(1)
    {
        for(int i = 0; i < 256; i++)
        {
            _delay_ms(200);

            SR_out(SRclk , Rclk , dataPin , i , 0); 

        }

    }


    return 0; 
}


