/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "ADC.h"


/*esto*/









/*==================[macros and definitions]=================================*/

static ADC_CLOCK_SETUP_T ADCSetup; /*me creo una variable de tipo estructura, que el
la estructura definida ya en la lpc open como ADC_CLOCK_SETUP_T*/

#define ADC_ID 0
#define CHANNEL_ADC 1 /* hice este define.. pero puedo usar un campo del enum que ya esta
dfinido y se llama ADC_CH1 que ya anda. */
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */


void InitADC()
{
	Chip_SCU_ADC_Channel_Config(ADC_ID,ADC_CH1);
	Chip_ADC_Init(LPC_ADC0, & ADCSetup);/* aca debo pasarle un puntero a LPC_DAC_T que es un tipo de dato definido con typedef*/
	Chip_ADC_EnableChannel(LPC_ADC0,ADC_CH1,ENABLE);/*ADC_CH1 Y ENABLE son parte de un enum y corresponden a numeros que definen
	el canal que estoy usando "el 1" y habilitando ese canal*/
    Chip_ADC_SetSampleRate(LPC_ADC0, &ADCSetup,ADC_MAX_SAMPLE_RATE);


}

uint16_t ConvertDataADC(void)
{
	uint16_t dataADC;
    /*disparo conversion del ADC0, con Start Now*/
	Chip_ADC_SetStartMode(LPC_ADC0,ADC_START_NOW,ADC_TRIGGERMODE_RISING);
	/* ahora me quedo mirando un flag del registro del ADC0 que se va a poner a 1
	 * cuando termine de convertir. Entonces mientras sea diferente de 1, queda esperando*/

	while(Chip_ADC_ReadStatus(LPC_ADC0,ADC_CH1,ADC_DR_DONE_STAT)!=SET)
	{}

    Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, & dataADC);
    return dataADC;
}


void limpiarInterrupcionADC(void)

{

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

