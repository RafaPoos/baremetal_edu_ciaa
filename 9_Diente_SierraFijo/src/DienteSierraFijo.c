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
#include "DienteSierraFijo.h"       /* <= own header */
#include "led.h"
#include "DAC.h"
#include "Timers.h"
volatile uint32_t CONTADOR=0;

/*==================[macros and definitions]=================================*/
#define SALTO_RAMPA 9
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void ServicioInterrupcionRIT(void) /* ENTONCES ACA LE DIGO QUE ES LO QUE HACE ESA INTERRUP,
                          que llama a limpiarInterrupcion() que esta definida en el
                          Timer.h y luego implementada en el Timer.c. Ella borra el flag
                          interno con el que trabaja el micro cuando se interrumpe. Y yo
                          aca adentro incremento un contador. (PONER POCO CODIGO)
                          Ademas alla en el archivo Vector de "esta aplicacion" le
                          puse en la linea correspondiente a la interrupcion del
                          RITimer, de micro NXP, que cuando salte la interrup, se venga a
                          mirar esta funcion que esta acá. Le puse el mismo nombre de
                          función*/
{
	ConvertDataDAC(CONTADOR);
    CONTADOR=CONTADOR + SALTO_RAMPA;
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
	uint32_t i;

    InitTimer(INTERVALO_TIMER);
    InitDac();
    InitLed();


	apagarLed(rojo);
	apagarLed(amarillo);
	apagarLed(verde);



   /* perform the needed initialization here */

   while(1) {

	   /* La consigna dice que la rampa debe tener 3v de amplitud y 100ms de periodo,
	    * entonces como la interrupcion del timer esta cada 1ms, seran 100 datos pasados
	    * al DAC para que convierta.
	    * 3,3/2^10=3,223mv -----> 3v/3,223mv=931 cuentas
	    * 931/100= 9,31 es el incremento que debo ponerle en cada conversion
	    * Pero le voy a poner cada 9 porque nose bien como tratar los flotantes aca
	    * "PREGUNTAR"
	    */
if (CONTADOR==900)
{CONTADOR=0;}
/* miro el contador si llego a 900 mi cuenta máxima y lo reinicio,
 * como tengo poco codigo, para que sea mas preciso, le mando a convertir arriba
 * cuando interrumpe
 */


   }


   return 0;


}/*este es el del mail*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

