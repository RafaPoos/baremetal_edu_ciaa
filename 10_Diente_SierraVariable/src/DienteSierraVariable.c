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
#include "DienteSierraVariable.h"       /* <= own header */
#include "led.h"
#include "DAC.h"
#include "Timers.h"
#include "Teclas.h"
volatile uint32_t CONTADOR=0;
volatile float SALTO_RAMPA=0;
/*==================[macros and definitions]=================================*/

#define PULSADO 0
#define NO_PULSADO 1
#define SALTO_AMPLITUD 0.3
#define SALTO_PERIODO 100
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
    CONTADOR=floor(CONTADOR + SALTO_RAMPA);
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
	uint16_t periodo=1000;
	float amplitud=0;
	float cuentas;
    edu_ciaa_key Teclado;
    InitTimer(INTERVALO_TIMER);
    InitDac();
    InitLed();
    InitTeclas();


	apagarLed(rojo);
	apagarLed(amarillo);
	apagarLed(verde);



   /* perform the needed initialization here */

   while(1) {

	   /* En este ejercicio puedo cambiar con las teclas, la amplitud y la frecuencia,
	    * entonces tengo dos variables "amplitud" y "periodo", que voy a modificar.
	    * Luego a partir de estos dos datos actualizados, realizo los calculos para obtener
	    * el SALTO_RAMPA y el LIMITE_CUENTAS. Teniendo en cuenta que el RITimer siempre lo uso a
	    * un tiempo de conteo fijo de 1ms. Ello determina entonces que el maximo periodo sera de 1024ms
	    * Los limites de amplitud quedan determinados segun la Vdd del micro que es 0 y 3,3V.
	    *
	    * Tambien podria modificar el valor derebaso del RITimer y eso me permitiria tener periodos
	    * mayores. Por ejemplo si hago los calculos para que el periodo sea 100ms con el timer rebasando
	    * a 1ms, me daría para una amplitud de 3V:

	    * 3,3/2^10=3,223mv -----> 3v/3,223mv=931 cuentas
	    * 931/100= 9,31 es el incremento que debo ponerle en cada conversion
	    *
	    * Pero ahora si mi timer rebasa cada 2ms, pero quiero mantener los 100ms de periodo
	    *
	    * 931/50=18,6 es el incremento que debo ponerle en cada conversion
	    */

leerTeclas(& Teclado);
for (i=4000000; i!=0; i--)
           {
           asm ("nop");
           }

   if(Teclado.Tecla_1==PULSADO)/*para aumentar la amplitud, ademas miro si me pasé la pongo a 3.3*/
  	 {
	  amplitud=amplitud+SALTO_AMPLITUD;
	  if(amplitud==3.6)
	  {amplitud=3.3;}
	  toogle(rojo);
	 }
   if(Teclado.Tecla_2==PULSADO)/*para baja la amplitud, ademas miro si me pasé la pongo a 0*/
     {
   	  amplitud=amplitud-SALTO_AMPLITUD;
   	  if((amplitud==0)|(amplitud>3.3))
   	  {amplitud=0;}
   	 toogle(amarillo);
     }
   if(Teclado.Tecla_3==PULSADO)/*para aumentar la el periodo, ademas miro si me pasé la pongo a 1000*/
     {
   	  periodo=periodo+SALTO_PERIODO;
   	  if(periodo==1100)
   	  {periodo=1000;}
   	toogle(verde);
     }
   if(Teclado.Tecla_4==PULSADO)/*para bajar la periodo, ademas miro si me pasé la pongo a 0*/
    {
   	  periodo=periodo-SALTO_PERIODO;
   	  if((periodo==0)|(periodo>1000))
   	  {periodo=100;}
   	toogle(verde);
    }

   cuentas=amplitud/(3.3/1024);

   SALTO_RAMPA=cuentas/periodo;





   if (CONTADOR>=cuentas)
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

