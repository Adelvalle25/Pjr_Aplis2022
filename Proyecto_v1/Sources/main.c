#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdlib.h> /* Para realizar funcion div */


int map(int value, int RIE,int RFE, int RIS, int RFS){
	return (((RFS-RIS)/(RFE-RIE))*(value)+RIS);
}

void init_motor1(void){
	PTBDD_PTBDD5=1;
	TPM1SC=0xB;
	TPM2MOD=1000;
	TPM2C1SC=0x28;
	//PTB5 DIGITAL
	//TPM2CH1 PWM
}
void chPW1(int vel){
	TPM2C1V=vel;
}


void init_motor2(void){
	PTBDD_PTBDD3=1;
	TPM1SC=0xB;
	TPM1MOD=1000;
	TPM1C1SC=0x28;
	//PTB3 DIGITAL
	//TPM1CH0 PWM
}
void chPW2(int vel){
	TPM1C0V=vel;
}

void init_servo(void){
	TPM1SC=0xA;
	TPM1MOD=40000;
	TPM1C1SC=0x28;
	//TPM1CH1 PWM
}
void angle(int ang){
	TPM1C1V=ang;
}

void init_ultrasonico(void){
	ADCCFG = 0xE0;
	APCTL2 = 0x4;
	ADCSC1 = 0x6A;
	//ADP10
}

void init_optico(void){
	ADCCFG = 0xE0;
	APCTL2 = 0x8;
	ADCSC1 = 0x6B;
	//ADP11
}




void main(void) {
  EnableInterrupts;
  SOPT1_COPT=0;
  ICSTRM=175;
  
  init_motor1();
  init_motor2();
  init_servo();
  init_ultrasonico();
  init_optico();

  
  for(;;) {
    __RESET_WATCHDOG();	
  } 
}
