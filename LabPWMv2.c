/* Ejemplo PWM
 * Laboratorio de Sistemas de Control II
 * Prof. Omar Pinzón-Ardila
 */

//  External Connections
//  - EPWM1A is on GPIO0
//  - EPWM1B is on GPIO1
//  - EPWM2A is on GPIO2
//  - EPWM2B is on GPIO3
//  - EPWM3A is on GPIO4
//  - EPWM3B is on GPIO5

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Defines that configure the period for each timer
//
#define EPWM1_TIMER_TBPRD  3000  // Registro del perido
#define EPWM1_CMPA         1500
#define EPWM1_CMPB         1500

void setupPWM()
{

    InitSysCtrl();  // Inicializa los registros del control del sistema - habilita el reloj de perifericos
    //  External Connections
    //  - EPWM1A is on GPIO0
    //  - EPWM1B is on GPIO1
    InitEPwm1Gpio(); // Inicializa los pines del GPIO

    EALLOW;
    // Configura Módulo EPWM 1
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Modo asimétrico contador en modo up
    EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD; // Establecer el periodo del PWM
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Phase loading disabled
    EPwm1Regs.TBPHS.half.TBPHS =  0x0000; // Set Phase register to zero
    EPwm1Regs.TBCTR = 0x0000;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;  // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV2;

    //Inicializa los registros de sombra en cero
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Habilitar el sombreado del registro CMPA*
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Asignar valores de comparación
    EPwm1Regs.CMPA.half.CMPA = EPWM1_CMPA;    // Set compare A value
    EPwm1Regs.CMPB = EPWM1_CMPB;              // Set Compare B value

    // Set actions
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;      // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;    // Clear PWM1A on event A, up count

    EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;      // Set PWM1B on Zero
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;    // Clear PWM1B on event B, up count

    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EDIS;
}

int main(void)
{
    setupPWM();  // Configurar el PWM

    while (1)
    {
    // Realizar otras tareas si es necesario
    }
}
