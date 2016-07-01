/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, Gustavo Muro
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

/** \brief Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "Degrade.h"       /* <= own header */
#include "Timers.h"
#include "led.h"
#include "Teclas.h"
volatile uint32_t CONTADOR=0;
volatile uint8_t CONTADOR_20ms=0;
volatile uint8_t CONTADOR_LEDS=0;


/*==================[macros and definitions]=================================*/
#define PERIODO 5000000
#define PULSADO 0
#define NO_PULSADO 1

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void ServicioInterrupcionRIT(void) /* ENTONCES ACA LE DIGO QUE ES LO QUE HACE ESA INTERRUP,
                          que llama a limpiar interrupcion que esta definida en el
                          Timer.h y luego implementada en el Timer.c. Ella borra el flag
                          interno con el que trabaja el micro cuando se interrumpe. Y yo
                          aca adentro incremento un contador. (PONER POCO CODIGO)*/
{

    CONTADOR ++;
    CONTADOR_20ms ++;
    CONTADOR_LEDS ++;
	limpiarInterrupcionRIT();



}
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
int main(void)
{
	uint8_t CICLO_ROJO=0;
	uint8_t CICLO_VERDE=10;
	uint8_t CICLO_AZUL=0;
	uint8_t CONTADOR_16VECES=0;

	uint32_t i;

	InitLed();
	InitTeclas();
	InitTimer(INTERVALO_TIMER);

	edu_ciaa_ledRGB mi_RGB;
	edu_ciaa_key mi_key;

	apagarLed(rojo);
    apagarLed(amarillo);
    prenderLed(verde);
	apagarRGB(& mi_RGB);
	leerTeclas(& mi_key);

   /* perform the needed initialization here */

   while(1) {

leerTeclas(& mi_key);


if (CONTADOR==300)
   {
	 CONTADOR=0;
	 CONTADOR_20ms=0;
	 CICLO_ROJO=CICLO_ROJO+1;
	   if(CICLO_ROJO>10)
	   {CICLO_ROJO=0;}
	 CICLO_VERDE=CICLO_VERDE-1;
	   if(CICLO_VERDE>10)
	   {CICLO_VERDE=0;}
	 CICLO_AZUL=CICLO_AZUL+1;
	   if(CICLO_AZUL>5)
	   {CICLO_AZUL=0;}
	 CONTADOR_16VECES ++;
	   if (CONTADOR_16VECES==20)
		     {CONTADOR_16VECES=0;
		      CICLO_ROJO=0;
		      CICLO_VERDE=10;
		      CICLO_AZUL=0;
		      }
	}

if (CONTADOR_20ms==20)
{CONTADOR_20ms=0;}


if(mi_key.Tecla_1==PULSADO)
		{
	       if (CONTADOR_20ms>0 && CONTADOR_20ms<=CICLO_ROJO)
	       {mi_RGB.LEDrojo=ENCENDIDO;}
	       else{mi_RGB.LEDrojo=APAGADO;}

		   if (CONTADOR_20ms>0 && CONTADOR_20ms<=CICLO_VERDE)
		   {mi_RGB.LEDverde=ENCENDIDO;}
		   else{mi_RGB.LEDverde=APAGADO;}

		   if (CONTADOR_20ms>0 && CONTADOR_20ms<=CICLO_AZUL)
		   {mi_RGB.LEDazul=ENCENDIDO;}
		   else{mi_RGB.LEDazul=APAGADO;}

		   encenderRGB(& mi_RGB);

		}/*del if que evalua si esta apretada la tecla 1*/
 else {
	  apagarRGB(& mi_RGB);
	  if (CONTADOR_LEDS==250)/*el CONTADOR_LEDS cuenta hasta 255 por eso no necesito ver si se
	  rebasó del valor al que quiero que titilen los leds y asi pueda entrar en el ciclo.. estoy ahi
	  nomas 250 vs 255*/
	        {toogle(verde);
	         toogle(amarillo);
	         CONTADOR_LEDS=0;
	        }
	  }



}/*esta es la del while*/

   return 0;
}/*esta es la del MAIN*/




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

