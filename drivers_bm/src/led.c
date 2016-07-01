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
#include "led.h"


/*esto*/









/*==================[macros and definitions]=================================*/
#define LED1_PORT 2 /* este es el puerto fisico en la conexion*/
#define LED2_PORT 2
#define LED3_PORT 2
#define LED0_R_PORT 2
#define LED0_G_PORT 2
#define LED0_B_PORT 2

#define LED1_PORT_NUM 0 /* este es el puerto GPIO"X"*/
#define LED2_PORT_NUM 1
#define LED3_PORT_NUM 1
#define LED0_R_PORT_NUM 5
#define LED0_G_PORT_NUM 5
#define LED0_B_PORT_NUM 5

#define LED1_PIN 10 /*que pin del puerto fisico es*/
#define LED2_PIN 11
#define LED3_PIN 12
#define LED0_R_PIN 0
#define LED0_G_PIN 1
#define LED0_B_PIN 2

#define LED1_BIT_NUM 1<<14 /*que desplazamiento hay hasta el pin GPIO[X]*/
#define LED2_BIT_NUM 1<<11
#define LED3_BIT_NUM 1<<12
#define LED0_R_BIT_NUM 1<<0
#define LED0_G_BIT_NUM 1<<1
#define LED0_B_BIT_NUM 1<<2

#define LED1_BITValue 14 /*este es el num de bit en el GPIO[X]*/
#define LED2_BITValue 11
#define LED3_BITValue 12
#define LED0_R_BITValue 0
#define LED0_G_BITValue 1
#define LED0_B_BITValue 2

#define SALIDA 0x01
#define ENTRADA 0x00



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

void InitLed()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);


	Chip_SCU_PinMux(LED1_PORT,LED1_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED2_PORT,LED2_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED3_PORT,LED3_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED0_R_PORT,LED0_R_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED0_G_PORT,LED0_G_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LED0_B_PORT,LED0_B_PIN,MD_PUP,FUNC4);


	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED1_PORT_NUM, LED1_BIT_NUM, SALIDA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED2_PORT_NUM, LED2_BIT_NUM, SALIDA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED3_PORT_NUM, LED3_BIT_NUM, SALIDA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED0_R_PORT_NUM, LED0_R_BIT_NUM, SALIDA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED0_G_PORT_NUM, LED0_G_BIT_NUM, SALIDA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED0_B_PORT_NUM, LED0_B_BIT_NUM, SALIDA );

	 /*deberia devolver un TRUE si pudo realizar bien estas funciones y un FALSE si no lo hizo.. luego sacar un error por consola o algo */
}
uint8_t prenderLed(uint8_t led)
{
     switch (led)
     {
     case rojo :
	 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED1_PORT_NUM,LED1_BITValue);
	 break;

     case amarillo :
     	 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED2_PORT_NUM,LED2_BITValue);
     break;
     case verde :
     	 Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED3_PORT_NUM,LED3_BITValue);
     break;
     }

/*tambien se deberia devolver un TRUE O FALSE y desp interpretar eso*/

}
uint8_t apagarLed(uint8_t led )
{
	switch (led)
	     {
	     case rojo :
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED1_PORT_NUM,LED1_BITValue);
		 break;
	     case amarillo :
	     Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED2_PORT_NUM,LED2_BITValue);
	     break;
	     case verde :
	     Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED3_PORT_NUM,LED3_BITValue);
	     break;
	     }


}
uint8_t toogle(uint8_t led)
{
	switch (led)
	     {
	     case rojo :
	    	 Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED1_PORT_NUM, LED1_BITValue);
         break;
	     case amarillo :
	    	 Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED2_PORT_NUM, LED2_BITValue);
	    break;
	     case verde :
	    	 Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED3_PORT_NUM, LED3_BITValue);
	    break;
	     }


}

uint8_t encenderRGB(edu_ciaa_ledRGB *ledRGB)
{
	if (ledRGB->LEDrojo==ENCENDIDO)
		{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED0_R_PORT_NUM,LED0_R_BITValue);
		}
	else
	{Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_R_PORT_NUM,LED0_R_BITValue);}

	if (ledRGB->LEDverde==ENCENDIDO)
		{
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED0_G_PORT_NUM,LED0_G_BITValue);
		}
	else
		{Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_G_PORT_NUM,LED0_G_BITValue);}

	if (ledRGB->LEDazul==ENCENDIDO)
	    {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED0_B_PORT_NUM,LED0_B_BITValue);
	    }
	else
		{Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_B_PORT_NUM,LED0_B_BITValue);}
}
uint8_t apagarRGB(edu_ciaa_ledRGB *ledRGB)
	{

			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_R_PORT_NUM,LED0_R_BITValue);

			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_G_PORT_NUM,LED0_G_BITValue);

			Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED0_B_PORT_NUM,LED0_B_BITValue);

}

uint8_t toogleRGB(edu_ciaa_ledRGB *ledRGB)
	{
		if (ledRGB->LEDrojo==ENCENDIDO)
			{
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_R_PORT_NUM,LED0_R_BITValue);
			}
		if (ledRGB->LEDverde==ENCENDIDO)
			{
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_G_PORT_NUM,LED0_G_BITValue);
			}
		if (ledRGB->LEDazul==ENCENDIDO)
		    {
			Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, LED0_B_PORT_NUM,LED0_B_BITValue);
		    }
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

