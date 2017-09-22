/* 
 * File:   mcu.h
 * Author: MrChunckuee
 *
 * Created on 20 de mayo de 2013, 09:48 PM
 */

#ifndef MCU_H
#define	MCU_H

#define HIGH    1
#define LOW     0
#define INPUT   1
#define OUTPUT  0
#define CLEAR   0x00

#define MOTOR_IZQUIERDA_INA          PORTBbits.RB0
#define TRIS_MOTOR_IZQUIERDA_INA     TRISB0
#define MOTOR_IZQUIERDA_INB          PORTBbits.RB1
#define TRIS_MOTOR_IZQUIERDA_INB     TRISB1

#define MOTOR_DERECHA_INA            PORTBbits.RB4
#define TRIS_MOTOR_DERECHA_INA       TRISB4
#define MOTOR_DERECHA_INB            PORTBbits.RB5
#define TRIS_MOTOR_DERECHA_INB       TRISB5

#define LED_DERECHA                  PORTAbits.RA0
#define TRIS_LED_DERECHA             TRISA0
#define LED_IZQUIERDA                PORTBbits.RB3
#define TRIS_LED_IZQUIERDA           TRISB3

#define TRIG                         PORTAbits.RA4
#define TRIS_TRIG                    TRISA4
#define ECHO                         PORTAbits.RA1
#define TRIS_ECHO                    TRISA1

void MCU_Init(void);
void Delay_MS(unsigned int t);
unsigned int Medir_Distancia(void);
void Navegacion(void);
void Opcion_Movimiento(unsigned char X);

#endif	/* MCU_H */

