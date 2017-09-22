/*******************************************************************************
 *
 *              ROBOT QUE EVITA OBSTACULOS
 *                        MROHCv1
 *
 *******************************************************************************
 * FileName:        mcu.c
 * Processor:       PIC18F1320
 * Complier:        XC8 v1.32
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Robot que evita obstaculos a una distancia de 15cm
 *                  utiliza un sensor ultrasonico HC-SR04
 *                  OSC Interno = 8MHz
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "mcu.h"

#define _XTAL_FREQ 8000000

enum{AVANZAR, RETROCEDER, GIRO_DER, GIRO_IZQ, PARO};

unsigned int DISTANCIA, DISTANCIA_DER, DISTANCIA_IZQ;

void MCU_Init(void){
    OSCCONbits.IRCF=0b111;  //Oscilador interno a 8MHz
    ADCON1=0xFF; //Configuramos entrada/salida digitales

    //Definimos entradas y salidas
    TRIS_MOTOR_IZQUIERDA_INA=OUTPUT;
    TRIS_MOTOR_IZQUIERDA_INB=OUTPUT;
    TRIS_MOTOR_DERECHA_INA=OUTPUT;
    TRIS_MOTOR_DERECHA_INB=OUTPUT;
    TRIS_LED_DERECHA=OUTPUT;
    TRIS_LED_IZQUIERDA=OUTPUT;
    TRIS_TRIG=OUTPUT; //Pin TRIG del HC-SR04 como salida
    TRIS_ECHO=INPUT; //Pin ECHO del HC-SR04 como entrada

    //Limpiamos los puertos
    PORTA=CLEAR;
    PORTB=CLEAR;
}

void Navegacion(void){
    DISTANCIA=Medir_Distancia();
    if(DISTANCIA>15){
        Opcion_Movimiento(AVANZAR);
    }
    else {
        Opcion_Movimiento(PARO);
        Opcion_Movimiento(GIRO_DER);
        Delay_MS(1000);
        Opcion_Movimiento(PARO);
        DISTANCIA_DER=Medir_Distancia();
        Opcion_Movimiento(GIRO_IZQ);
        Delay_MS(2000);
        Opcion_Movimiento(PARO);
        DISTANCIA_IZQ=Medir_Distancia();
        Opcion_Movimiento(GIRO_DER);
        Delay_MS(1000);
        Opcion_Movimiento(PARO);
        if(DISTANCIA_DER>=DISTANCIA_IZQ){
            Opcion_Movimiento(GIRO_DER);
            Delay_MS(1000);
            Opcion_Movimiento(PARO);
        }
        else{
            Opcion_Movimiento(GIRO_IZQ);
            Delay_MS(1000);
            Opcion_Movimiento(PARO);
        }
    }
}

//Rutina para retardos en mS personalizada
void Delay_MS(unsigned int t){
    unsigned int j;
    for(j=0;j<t;j++){
        __delay_ms(1);
    }
}

unsigned int Medir_Distancia(void){
    unsigned int CENTIMETROS=0;
    TRIG=HIGH;
    __delay_us(10); //Retardo de 10uS
    TRIG=LOW;
    while(ECHO==LOW); //Espera flanco de subida por el pin echo
    while(ECHO==HIGH){
        CENTIMETROS++;
        __delay_us(58);
    }
return(CENTIMETROS);
}

void Opcion_Movimiento(unsigned char X){
    switch(X){
        case AVANZAR:
            MOTOR_IZQUIERDA_INA=LOW;
            MOTOR_IZQUIERDA_INB=HIGH;
            MOTOR_DERECHA_INA=LOW;
            MOTOR_DERECHA_INB=HIGH;
        break;
        case RETROCEDER:
            MOTOR_IZQUIERDA_INA=HIGH;
            MOTOR_IZQUIERDA_INB=LOW;
            MOTOR_DERECHA_INA=HIGH;
            MOTOR_DERECHA_INB=LOW;
        break;
        case GIRO_DER:
            MOTOR_IZQUIERDA_INA=LOW;
            MOTOR_IZQUIERDA_INB=HIGH;
            MOTOR_DERECHA_INA=HIGH;
            MOTOR_DERECHA_INB=LOW;
        break;
        case GIRO_IZQ:
            MOTOR_IZQUIERDA_INA=HIGH;
            MOTOR_IZQUIERDA_INB=LOW;
            MOTOR_DERECHA_INA=LOW;
            MOTOR_DERECHA_INB=HIGH;
        break;
        case PARO:
            MOTOR_IZQUIERDA_INA=LOW;
            MOTOR_IZQUIERDA_INB=LOW;
            MOTOR_DERECHA_INA=LOW;
            MOTOR_DERECHA_INB=LOW;
        break;
        default:
        break;
    }
}

