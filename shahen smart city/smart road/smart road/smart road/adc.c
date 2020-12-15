/*
 * adc.c
 *
 * Created: 9/13/2017 4:23:31 PM
 *  Author: MOATASEM
 */ 
#include "adc.h"

static char vref=0;
void ADC_Init(Devision_Factor fact, Used_Voltage Used)
{
	ADC_Enable;     //ADEN = 1;
	switch(Used)
	{
		case Internal :		vref=2.56;	Internal_Voltages;	break;
		case ExternalAREF:	vref=5;		AREF_VOLTAGES;		break;
		case EXTERNALAVCC :	vref=5;		AVCC_VOLTAGES;		break;
	}
	
	switch(fact)
	{
		case DevFact2 : DevisionFactor2;break;
		case DevFact4 : DevisionFactor4;break;
		case DevFact8 : DevisionFactor8;break;
		case DevFact16 : DevisionFactor16;break;
		case DevFact32 : DevisionFactor32;break;
		case DevFact64 : DevisionFactor64;break;
		case DevFact128 : DevisionFactor128;break;
	}
}

short int ADC_Read(Input_Pins adc_pin)
{
	Selected_PIN(adc_pin);
	ADC_START_CONVERSTION;
	while(ADC_FLAG);
	return ADC;
}
float ADC_Read_voltage(Input_Pins adc_pin)
{
	float adc_val=ADC_Read(adc_pin);
	adc_val=adc_val*(vref/1024.0);
	return adc_val;
}

/*void adc_update()
{
			/*** task1 ***/
		/*for (int i=0;i<2;i++)
		{
			short int x=ADC_Read(i);
			lcd_out(1,1,convert_data(x));
			_delay_ms(1000);
			lcd_clear();
		}*/
		/** task2 temp sensor **/
/*		int x=(ADC_Read_voltage(ADC0))*100;
			lcd_out(1,1,convert_data(x));
			_delay_ms(1000);
			lcd_clear();
			
}*/
	