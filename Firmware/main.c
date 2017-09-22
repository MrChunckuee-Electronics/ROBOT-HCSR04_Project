/*******************************************************************************
 *
 *              ROBOT QUE EVITA OBSTACULOS
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F1320
 * Complier:        XC8 v1.32
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Robot que evita obstaculos a una distancia de 15cm
 *                  utiliza un sensor ultrasonico HC-SR04
 *                  OSC Interno = 8MHz
 *******************************************************************************
 * Rev.         Date            Comment
 *   v1.00      20/05/2013      Creación del firmware
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "mcu.h"
#include "word_config.h"

#define _XTAL_FREQ 8000000

void main(void){
    MCU_Init();
    while(1){
        Navegacion();
    }
}

