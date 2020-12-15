
//fatma gamal
/*
 * adc.h
 *
 * Created: 9/13/2018 4:23:17 PM
 *  Author: MOATASEM
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "micro.h"

/*********************** referance and pin select **************************************/
#define Internal_Voltages		ADC_MULTIPLEXER |= (1<<ADC_Referance0) | (1<<ADC_Referance1)
#define	AREF_VOLTAGES			ADC_MULTIPLEXER &= (~(1<<ADC_Referance0)) | (~(1<<ADC_Referance1))
#define	AVCC_VOLTAGES			PIN_WRITE(ADC_MULTIPLEXER,ADC_Referance0,GPIO_HIGH),PIN_WRITE(ADC_MULTIPLEXER,ADC_Referance1,GPIO_LOW)
#define Selected_PIN(pin)		ADC_MULTIPLEXER=(ADC_MULTIPLEXER&0xE0)|((pin)&0x1f);
/*********************** reading process **************************************/
#define ADC_FLAG				ADC_CONTROL &  (1<<ADC_START_BIT)
#define ADC_START_CONVERSTION	ADC_CONTROL |= (1<<ADC_START_BIT)
#define ADC_Enable				ADC_CONTROL |= (1<<ADC_enable_bit)
#define ADC_disable				ADC_CONTROL &= (~(1<<ADC_enable_bit))
/*********************** presecalar values **************************************/
#define DevisionFactor2		ADC_CONTROL|=(1<<adc_prescalar0)
#define DevisionFactor4		ADC_CONTROL|=(1<<adc_prescalar1)
#define DevisionFactor8		ADC_CONTROL|=(1<<adc_prescalar0)|(1<<adc_prescalar1)
#define DevisionFactor16	ADC_CONTROL|=(1<<adc_prescalar2)
#define DevisionFactor32	ADC_CONTROL|=(1<<adc_prescalar0)|(1<<adc_prescalar2)
#define DevisionFactor64	ADC_CONTROL|=(1<<adc_prescalar1)|(1<<adc_prescalar2)
#define DevisionFactor128	ADC_CONTROL|=(1<<adc_prescalar0)|(1<<adc_prescalar1)|(1<<adc_prescalar2)
/*********************** names of inputs **************************************/
typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
	}Input_Pins;

typedef enum
{
	DevFact2,
	DevFact4,
	DevFact8,
	DevFact16,
	DevFact32,
	DevFact64,
	DevFact128
	}Devision_Factor;

typedef enum
{
	Internal,
	ExternalAREF,
	EXTERNALAVCC
	}Used_Voltage;
	
/*********************** prototypes of functions **************************************/	
void ADC_Init(Devision_Factor fact, Used_Voltage Used);
short int ADC_Read(Input_Pins pin);
float ADC_Read_voltage(Input_Pins adc_pin);
void adc_update();	



#endif /* ADC_H_ */