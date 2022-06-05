#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void init_motor1(void){
	//PTB5 DIGITAL
	//TPM2CH1 PWM
}
int chPW1(int vel){
	return 1;
}


void init_motor2(void){
	//PTB3 DIGITAL
	//TPM1CH0 PWM
}
int chPW2(int vel){
	return 1;
}

void init_servo(void){
	//TPM1CH1 PWM
}
void angle(int ang){
	
}

void init_ultrasonico(void){
	//ADP10
}

void init_optico(void){
	//ADP11
}

int map(int value, int RIE,int RFE, int RIS, int RFS){
	return (((RFS-RIS)/(RFE-RIE))*(value)+RIS);
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
