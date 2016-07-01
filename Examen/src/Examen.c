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
#include "Examen.h"       /* <= own header */
#include "led.h"
#include "DAC.h"
#include "Timers.h"
#include "ADC.h"
#include "Teclas.h"
#include "UART.h"
volatile uint32_t dataADC=0;
volatile uint8_t FLAG_INTERRUPCION=0;

/*==================[macros and definitions]=================================*/

#define INTERVALO_TIMER 100
#define PULSADO 0
#define NO_PULSADO 1
#define ALTO 1
#define BAJO 0
#define DELAY 4000000
#define BAUD 115200
#define MVOLT_DATODIGITAL 0.0032265625
#define TAMANIO_DOBLE 14
#define TAMANIO_MITAD 14
#define TAMANIO_MUDO 4
#define TAMANIO_ORIGINAL 8
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void ServicioInterrupcionRIT(void)
{
	ConvertDataDAC(dataADC);
	toogle(rojo);
	FLAG_INTERRUPCION=1;

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
	edu_ciaa_key Teclado;
	uint8_t FLAG_TECLA1=0;
	uint8_t FLAG_TECLA2=0;
	uint8_t FLAG_TECLA3=0;

	float auxADC=0;
	uint8_t unidad;
	uint8_t decena;
	uint8_t centena;

	 char Doble[]={'D','o','b','l','e',' ','g','a','n','a','n','c','i','a'};
	 char Mitad[]={'M','i','t','a','d',' ','g','a','n','a','n','c','i','a'};
	 char Mudo[]={'M','u','t','e'};
	 char Original[]={'O','r','i','g','n','a','l'};
	 char Lectura_ADC[4];
	 char Volt[]={'V','o','l','t'};

	InitTimer(INTERVALO_TIMER);
    InitDac();
    InitLed();
    InitADC();
    InitTeclas();
    InitUART(BAUD);

	apagarLed(rojo);
	apagarLed(amarillo);
	apagarLed(verde);



   /* perform the needed initialization here */

   while(1) {

if(FLAG_INTERRUPCION==1)
{
	/*cumplido el tiempo, realizo una nueva adquisición*/
	dataADC=ConvertDataADC();

    /* Segun banderas activadas en lectura del teclado, puedo duplicar, dividir o poner a cero el
     * dato leido en ADC (dataADC),antes de enviarlo al DAC
     */
	if(FLAG_TECLA1==ALTO)
	{dataADC=(dataADC*2);
	if(dataADC>1023)
	{dataADC=1023;}

	}

	if(FLAG_TECLA2==ALTO)
	{dataADC=(dataADC/2);}

	if(FLAG_TECLA3==ALTO)
	{dataADC=0;}

	FLAG_INTERRUPCION=0;

}/*DEL IF DEL FLAG*/


leerTeclas(& Teclado);/*leo el teclado*/


/* Miro que tecla se apreto y acciono banderas para luego alterar el dato leido en ADC, para Duplicarlo,
 * dividirlo a la mitad o ponerlo a cero. Ademas saco por UART2 la acción realizada
 */

if(Teclado.Tecla_1==PULSADO)
{
	for(i=DELAY;i!=0;i--)/*Antirrebote*/
	{asm("nop");}

	if(FLAG_TECLA1==BAJO)
	{FLAG_TECLA1=ALTO;
	for (i=0; i<TAMANIO_DOBLE; i++)
	    {
	    WriteUART(Doble[i]);
	    }
	    WriteUART('\n');
	}
	else
	{FLAG_TECLA1=BAJO;
	for (i=0; i<TAMANIO_ORIGINAL; i++)
		{
		 WriteUART(Original[i]);
		}
		WriteUART('\n');
	}
}

if(Teclado.Tecla_2==PULSADO)
{
	for(i=DELAY;i!=0;i--)
	{asm("nop");}

	if(FLAG_TECLA2==BAJO)
	{FLAG_TECLA2=ALTO;
	for (i=0; i<TAMANIO_MITAD; i++)
	    {
	    WriteUART(Mitad[i]);
	    }
	    WriteUART('\n');
	}
	else
	{FLAG_TECLA2=BAJO;
	for (i=0; i<TAMANIO_ORIGINAL; i++)
		{
		 WriteUART(Original[i]);
		}
		WriteUART('\n');
	}
}

if(Teclado.Tecla_3==PULSADO)
{
	for(i=DELAY;i!=0;i--)
	{asm("nop");}

	if(FLAG_TECLA3==BAJO)
	{FLAG_TECLA3=ALTO;
	for (i=0; i<TAMANIO_MUDO; i++)
	    {
	    WriteUART(Mudo[i]);
	    }
	    WriteUART('\n');
	}
	else
	{FLAG_TECLA3=BAJO;
	for (i=0; i<TAMANIO_ORIGINAL; i++)
		{
		 WriteUART(Original[i]);
		}
		WriteUART('\n');
	}
}


/* Ahora miro si se presiono la tecla 4, informo el valor de tension adquirido instantaneo*/
if(Teclado.Tecla_4==PULSADO)
	{

	for(i=DELAY;i!=0;i--)
	{asm("nop");}

	/*MVOLT_DATODIGITAL equivale a 3.3v/1024*/
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

           /*Cargo un vector con el valor de Voltios leidos en ASCII y luego lo mando por UART2*/
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



   }/*DEL WHILE*/


   return 0;


}/*este es el del mail*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

