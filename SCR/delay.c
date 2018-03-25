#include "delay.h"

void delay500ns(void)
{
		
   int i=1;  
   while(i) 
   { 
     i--; 
   }  
}

void delay1us(void)
{
		
   int i=9;  
   while(i) 
   { 
     i--; 
   }  
}

void delay5us(void)
{
		
   int i=48;  
   while(i) 
   { 
     i--; 
   }  
}

void delay100us(void)
{
		
   int i=1200;  
   while(i) 
   { 
     i--; 
   }  
}



void delay5ms(void)
{
		
   long int i=60000;  
   while(i) 
   { 
     i--; 
   }  
}

void delay1ms(void)
{
	int i=12000;
	while(i)
	{
		i--;
	}
}

void delay50ms(void)
{
	int i=10;
	while(i)
	{
		delay5ms();
		i--;
	}
}

void delay100ms(void)
{
	delay50ms();
	delay50ms();
}

void delay1s(void)
{
	int i=10;
	while(i)
	{
		delay100ms();
		i--;
	}
}
