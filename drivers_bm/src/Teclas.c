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
#include "Teclas.h"


/*esto*/









/*==================Definiciones para el Teclado de la CIAA=======================*/

#define KEY1_PORT 1 /* este es el puerto fisico en la conexion*/
#define KEY2_PORT 1
#define KEY3_PORT 1
#define KEY4_PORT 1

#define KEY1_PIN 0 /*que pin del puerto fisico es*/
#define KEY2_PIN 1
#define KEY3_PIN 2
#define KEY4_PIN 6

/*ESTOS DOS DE ARRIBA SE USAN PARA EL PINmux UNA SOLA VEZ Y DESP SIGO
 * USANDO SIEMPRE LOS VALORES QUE ESTAN EN EL GPIOX[X] PARA CONFIGURAR
 * Y LO QUE SEA
 */

#define KEY1_GPIOPORT_NUM 0 /* este es el puerto GPIO"X"*/
#define KEY2_GPIOPORT_NUM 0
#define KEY3_GPIOPORT_NUM 0
#define KEY4_GPIOPORT_NUM 1



#define KEY1_GPIOBITmk_NUM 1<<4 /*que desplazamiento hay hasta el pin GPIO[X]*/
#define KEY2_GPIOBITmk_NUM 1<<8
#define KEY3_GPIOBITmk_NUM 1<<9
#define KEY4_GPIOBITmk_NUM 1<<9


#define KEY1_GPIOBIT_NUM 4 /*este es el num de bit en el GPIO[X]*/
#define KEY2_GPIOBIT_NUM 8
#define KEY3_GPIOBIT_NUM 9
#define KEY4_GPIOBIT_NUM 9

#define SALIDA 0x01
#define ENTRADA 0x00



/*==================Definiciones para el Teclado matricial==============================*/

#define FIL0_PORT 4 /* este es el puerto fisico en la conexion*/
#define FIL1_PORT 4
#define FIL2_PORT 4
#define FIL3_PORT 4
#define COL0_PORT 1
#define COL1_PORT 7
#define COL2_PORT 7

#define FIL0_PIN 0 /*que pin del puerto fisico es*/
#define FIL1_PIN 1
#define FIL2_PIN 2
#define FIL3_PIN 3
#define COL0_PIN 5
#define COL1_PIN 4
#define COL2_PIN 5

/*ESTOS DOS DE ARRIBA SE USAN PARA EL PINmux UNA SOLA VEZ Y DESP SIGO
 * USANDO SIEMPRE LOS VALORES QUE ESTAN EN EL GPIOX[X] PARA CONFIGURAR
 * Y LO QUE SEA
 */

#define FIL0_GPIOPORT_NUM 2 /* este es el puerto GPIO"X"*/
#define FIL1_GPIOPORT_NUM 2
#define FIL2_GPIOPORT_NUM 2
#define FIL3_GPIOPORT_NUM 2
#define COL0_GPIOPORT_NUM 1
#define COL1_GPIOPORT_NUM 3
#define COL2_GPIOPORT_NUM 3


#define FIL0_GPIOBITmk_NUM 1<<0 /*que desplazamiento hay hasta el pin GPIO[X]*/
#define FIL1_GPIOBITmk_NUM 1<<1
#define FIL2_GPIOBITmk_NUM 1<<2
#define FIL3_GPIOBITmk_NUM 1<<3
#define COL0_GPIOBITmk_NUM 1<<8 /*que desplazamiento hay hasta el pin GPIO[X]*/
#define COL1_GPIOBITmk_NUM 1<<12
#define COL2_GPIOBITmk_NUM 1<<13

#define FIL0_GPIOBIT_NUM 0 /*este es el num de bit en el GPIO[X]*/
#define FIL1_GPIOBIT_NUM 1
#define FIL2_GPIOBIT_NUM 2
#define FIL3_GPIOBIT_NUM 3
#define COL0_GPIOBIT_NUM 8 /*este es el num de bit en el GPIO[X]*/
#define COL1_GPIOBIT_NUM 12
#define COL2_GPIOBIT_NUM 13

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

void InitTeclas()
{

	Chip_GPIO_Init(LPC_GPIO_PORT);


	Chip_SCU_PinMux(KEY1_PORT,KEY1_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/*mapea P1_0 en GPIO 0[4], SW1*/
	Chip_SCU_PinMux(KEY2_PORT,KEY2_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/*mapea P1_1 en GPIO 0[8], SW2*/
	Chip_SCU_PinMux(KEY3_PORT,KEY3_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/*mapea P1_2 en GPIO 0[9], SW3*/
	Chip_SCU_PinMux(KEY4_PORT,KEY4_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/*mapea P1_6 en GPIO 1[9], SW4*/


	Chip_GPIO_SetDir(LPC_GPIO_PORT, KEY1_GPIOPORT_NUM, KEY1_GPIOBITmk_NUM, ENTRADA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, KEY2_GPIOPORT_NUM, KEY2_GPIOBITmk_NUM, ENTRADA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, KEY3_GPIOPORT_NUM, KEY3_GPIOBITmk_NUM, ENTRADA );
	Chip_GPIO_SetDir(LPC_GPIO_PORT, KEY4_GPIOPORT_NUM, KEY4_GPIOBITmk_NUM, ENTRADA );
	/*estas funciones usan ahora el puerto mapeado en GPIOx[x] y primero le doy el valor
	 * del numero de puerto que es GPIOX y luego el bit que es GPIO[X].. en forma de mascara
	 *  << (32 bits)
	 */

	 /*deberia devolver un TRUE si pudo realizar bien estas funciones y un FALSE si no lo hizo.. luego sacar un error por consola o algo */
}

uint8_t leerTeclas(edu_ciaa_key *key)
{

	key-> Tecla_1 = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, KEY1_GPIOPORT_NUM, KEY1_GPIOBIT_NUM);
	key-> Tecla_2 = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, KEY2_GPIOPORT_NUM, KEY2_GPIOBIT_NUM);
	key-> Tecla_3 = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, KEY3_GPIOPORT_NUM, KEY3_GPIOBIT_NUM);
	key-> Tecla_4 = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, KEY4_GPIOPORT_NUM, KEY4_GPIOBIT_NUM);

/*tambien se deberia devolver un TRUE O FALSE y desp interpretar eso*/

}

uint8_t leerMatricial(uint8_t modo_lectura, uint8_t TU, uint8_t TL, uint8_t TC  )

{

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

