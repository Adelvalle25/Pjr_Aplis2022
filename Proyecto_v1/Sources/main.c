#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdlib.h> /* Para realizar funcion div */
#define M 50
#define B 200

char c;

int valor, mode;
float dis_ultra,optico_volt,ultra_volt,dis_optico;

double map(double value, double RIE,double RFE, double RIS, double RFS){
	return (((RFS-RIS)/(RFE-RIE))*(value)+RIS);
}

void delay(unsigned char T){
	volatile int x,y;
	x=T*M+B;
	
	while(x--){
		y=x+8;
		y=x/9;
		
	}
}
void sleep(int ms){
  volatile int f=0;
  RTCSC=0x8;
  RTCMOD=0;
    while(f<=ms){
      if(RTCSC_RTIF==1){
        f++;
        RTCSC|=0x80;
      }
    }
    RTCSC=0x0;
    RTCMOD=0;
}

void init_motor1(void){
	PTBDD_PTBDD5=1;
	PTBDD_PTBDD6=1;
	TPM2SC=0xB;
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
	PTBDD_PTBDD2=1;
	
	TPM2C0SC=0x28;
	
	//PTB3 DIGITAL
	//TPM1CH0 PWM
}

void chPW2(int vel){
	TPM2C0V=vel;
}
void stop(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=0;
	PTBD_PTBD3=0;
	PTBD_PTBD2=0;
}

void adelante(void){
	
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=0;
	PTBD_PTBD2=1;
	sleep(700);
}
void atras(void){
	PTBD_PTBD5=1;
	PTBD_PTBD6=0;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
//	sleep(1000);
}
void izquierda(void){
	PTBD_PTBD5=1;
	PTBD_PTBD6=0;
	PTBD_PTBD3=0;
	PTBD_PTBD2=1;
	//sleep(355);
}
void derecha(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
	//sleep(355);
}
void aw(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=0;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
	sleep(200);
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=0;
	PTBD_PTBD2=1;
	sleep(1000);
}
void wd(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=0;
	PTBD_PTBD2=0;
	sleep(200);
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=0;
	PTBD_PTBD2=1;
	sleep(1000);
}
void sd(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=0;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
	sleep(200);
	PTBD_PTBD5=1;
	PTBD_PTBD6=0;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
	sleep(1000);
}
void sa(void){
	PTBD_PTBD5=0;
	PTBD_PTBD6=1;
	PTBD_PTBD3=0;
	PTBD_PTBD2=0;
	sleep(200);
	PTBD_PTBD5=1;
	PTBD_PTBD6=0;
	PTBD_PTBD3=1;
	PTBD_PTBD2=0;
	sleep(1000);
	
}
void init_servo(void){
	SOPT2=0x2;
	TPM1SC=0xA;
	TPM1MOD=40000;
	TPM1C1SC=0x28;
	//TPM1CH1 PWM
}

void angle(int ang){//4500 max- 800 min
	TPM1C1V=ang;
}

void init_ultrasonico(void){
	PTADD_PTADD0=0;
	ADCCFG = 0xE0;
	APCTL1 = 0x1;
	ADCSC1 = 0x20;
	
	//ADP10
}
void config_bluetooth(void){
	SCIBD=52;
	SCIC2=0x2C;
}


void init_optico(void){
	PTCDD_PTCDD3=0;
	ADCCFG = 0xE0;
	APCTL2 = 0x8;
	ADCSC1 = 0x2B;
	
	//ADP11
}


interrupt VectorNumber_Vscirx void re(){
	c=SCID;
	SCIS1=0;
	c=SCID;	
	if(c=='m'){
			mode=0;
		}else{
			mode=1;
		}
}
int h,scase;
void main(void) {
	EnableInterrupts;
	SOPT1_COPT=0;
	ICSTRM=175;
  
	init_motor1();
	init_motor2();
	init_servo();
	config_bluetooth();
 
	stop();
	chPW1(500);
	chPW2(500);
	angle(800);
	sleep(500);
	PTBDD_PTBDD7=0;

  for(;;) {
	  if(PTBD_PTBD7){//bluetooth
	 		 if(c=='w'){
	 			adelante();
	 			c='n';
	 		 }else if(c=='q'){
	 			 aw();
	 			 c='n';
	 		 }else if(c=='e'){
	 			 wd();
	 			 c='n';
	 		 }else if(c=='s'){
	 			 atras();
	 			sleep(700);
	 			 c='n';
	 		 }else if(c=='z'){
	 			 sa();
	 			 c='n';
	 		 }else if(c=='x'){
	 			 sd();
	 			 c='n';
	 		 }else if(c=='d'){
	 			 derecha();
	 			sleep(500);
	 			 c='n';
	 		 }else if(c=='a'){
	 			 izquierda();
	 			sleep(500);
	 			 c='n';
	 		 }else if(c=='n'){
	 			 stop();
	 		 }
	  }else {//manual

  	  	  chPW1(500);
 	  	  chPW2(500);
 		  init_ultrasonico();
 		  sleep(1000);
 		  angle(840);
 		  sleep(500);
 		  ultra_volt=map(ADCR,0,1023,0,5);
 		  dis_ultra=(ultra_volt/0.0098)*2.54;
 		  if(dis_ultra<=5){ 
 			  h=1;
 			  stop();
 			  
 		  }else{
 			  h=0;
 			  adelante();
 			 //sleep(1000);
 			 stop();
 			  
 		  }	  
 		  if(h==1){
 			  init_optico();
 			  sleep(1000);
 			  optico_volt=map(ADCR,0,1023,0,5);
 			   dis_optico=(optico_volt/0.0098)*2.54;
 			   scase=0;
 			   
 		 	 if(dis_optico>=50){
 		 		 angle(4400);
 		 		 
 		 		 sleep(1000);
 		 		 optico_volt=map(ADCR,0,1023,0,5);
 		 		 dis_optico=(optico_volt/0.0098)*2.54;
 		 		 scase=1;
 		 	 }
 		 	 
 		 	 if(dis_optico>=50){
 		 		 angle(2500);
 		 		 sleep(1000);
 		 		 optico_volt=map(ADCR,0,1023,0,5);
 		 		 dis_optico=(optico_volt/0.0098)*2.54;
 		 		 scase=2;
 		 	 }
 		 	
 		 	 
 		  }
 		  if(scase==0){
 			  izquierda();
 			  sleep(500);
 			  stop();
 		  }
 		  
 		  if(scase==1){
 			  derecha();
 			  sleep(500);
 			  stop();
 		  }
 		  if(scase==2){
 			  atras();
 			  sleep(500);
 			  izquierda();
 			  sleep(500);
 			  izquierda();
 			  stop();
 		  }
  } 	
}	
}
	
