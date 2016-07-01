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
#include "SerieConUART2.h"       /* <= own header */
#include "led.h"
#include "ADC.h"
#include "Teclas.h"

/*==================[macros and definitions]=================================*/
#define BAUD 115200
#define a 97
#define r 114
#define v 118
#define PULSADO 0
#define NO_PULSADO 1
#define MVOLT_DATODIGITAL 0.0032265625
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
int main(void)
{

    char texto[]={'H','o','l','a',' ','M','u','n','d','o'};
    char Lectura_ADC[4];
    char Volt[]={'V','o','l','t'};
    InitTeclas();
	InitLed();
	InitADC();
	InitUART(BAUD);
    uint16_t dataADC=0;
    float auxADC=0;
    uint8_t DatoSerie=0;
    uint8_t unidad;
    uint8_t decena;
    uint8_t centena;
    uint32_t i=0;
	apagarLed(rojo);
	apagarLed(amarillo);
	apagarLed(verde);
	edu_ciaa_key Teclado;


   /* perform the needed initialization here */

   while(1) {


   DatoSerie = ReadUART();

   switch(DatoSerie)
   {
   case a:
	   toogle (amarillo);
	   for (i=0; i<10; i++)
	        {
	        WriteUART(texto[i]);
	        }
	   break;

   case r:
	   toogle (rojo);
	   for (i=0; i<10; i++)
	   	    {
	   	    WriteUART(texto[i]);
	   	    }
	   break;

   case v:
	   toogle(verde);
	   for (i=0; i<10; i++)
	   	    {
	   	    WriteUART(texto[i]);
	   	    }
	   WriteUART('\n');
	   break;
   }



/* leo el teclado y espero unos miliseg para evitar el rebote*/
   leerTeclas(& Teclado);
   for (i=4000000; i!=0; i--)
           {
           asm ("nop");
           }

   if(Teclado.Tecla_1==PULSADO)
  	 {
	   /*recordar que la funcion que manda a convertir al ADC
	   espera que termine de convertir y luego envia el dato*/
	   dataADC=ConvertDataADC();

	   /*transformo el dato digital leido a miliVoltios*/
	   auxADC=dataADC*MVOLT_DATODIGITAL;

	   /* me guardo la unidad, con floor que trunca hacia abajo*/
	   unidad=floor(auxADC);

	   /* quito la unidad, y me guardo la decena y centena siguiendo los mismos pasos*/
       auxADC=auxADC-unidad;
       auxADC=auxADC*10;
       decena=floor(auxADC);
       auxADC=auxADC-decena;
       auxADC=auxADC*10;
       centena=floor(auxADC);


       Lectura_ADC[0]=(unidad+48);
       Lectura_ADC[1]=',';
       Lectura_ADC[2]=(decena+48);
       Lectura_ADC[3]=(centena+48);
       for (i=0; i<4; i++)
       	   	    {
       	   	    WriteUART(Lectura_ADC[i]);
      	   	    }
       for (i=0; i<4; i++)
                {
                WriteUART(Volt[i]);
                }
       WriteUART('\n');
  	   }

   }


   return 0;


}/*este es el del mail*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

