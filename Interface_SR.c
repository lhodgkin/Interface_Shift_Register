/* 
 * File:   blink_main.c
 * Author: Luke Hodgkin
 *
 * Created on April 10, 2024
 */



#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


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
    int temp = 0; 
    
    for (int i = 0; i < 8 ; i++) 
    {
        // Set output data pin
        PORTB |= ((value & 0x0001)<< dataPin);
        value >>= 1 ;        // Bit shift right the value vein shifted out to SR



        // Then Toggle the SRclk pin
        PORTB |= (0x0001 << SRclk); 
        PORTB &= ~(0x0001 << SRclk); 



    }
    // Toggle the Rclk pin to putput the value shifted in. 
    PORTB |= (0x0001 << Rclk); 
    PORTB &= ~(0x0001 << Rclk);
    

}


// This will test the function of the bit shift out to the shift register.

int main()
{
    DDRB = 0b00100111;
    int SRclk = 0; 
    int Rclk = 1; 
    int dataPin = 2; 
    int dummy = 0;


    while(1)
    {
        for(int i = 0; i < 256; i++)
        {
            for(int j =0; j < 1000000; j++){PORTB |= 32;}

            SR_out(SRclk , Rclk , dataPin , i , 0); 

        }

    }


    return 0; 
}


