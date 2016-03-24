#include <stdio.h>

#include "LPC8xx.h"
#include "mrt.h"
#include "uart.h"

#define TXDATCTL_EOT        (1<<20)
#define TXDATCTL_RX_IGNORE  (1<<22)
#define TXDATCTL_FSIZE(s)   ((s) << 24)
#define CFG_ENABLE          (1<<0)
#define CFG_MASTER          (1<<2)
#define STAT_RXRDY          (1<<0)
#define STAT_TXRDY          (1<<1)

//#define mLed 1
#define mDIN_H 2
#define mDIN_L 3
#define mBit_MAX 8
#define mLED_MAX 3
#define mWait_US 5

void SwitchMatrix_Init() {
    /* Enable SWM clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
    /* Pin Assign 8 bit Configuration */
    /* U0_TXD */
    /* U0_RXD */
    LPC_SWM->PINASSIGN0 = 0xffff0004UL;
    /* Pin Assign 1 bit Configuration */
    /* RESET */
    LPC_SWM->PINENABLE0 = 0xffffffbfUL;
}

//
unsigned int pow_get(int src, int iPnum){
    int ret=1;
    if(iPnum > 0){
        ret=src;
        for(int i=0; i<iPnum-1; i++){
          ret=ret * src;
        }
    }
    return ret;
}
unsigned int transUInt(unsigned char c){
    if('0'<=c && '9'>=c) return (c-0x30);//0x30は'0'の文字コード
    if('A'<=c && 'F'>=c) return (c+0x0A-0x41);//0x41は'A'の文字コード
    if('a'<=c && 'f'>=c) return (c+0x0A-0x61);//0x61は'a'の文字コード
    return 0;
}

//
unsigned int hexToUInt(char *str)
{
    unsigned int i,j=0;
    char*str_ptr=str+strlen(str)-1;
    for(i=0;i<strlen(str);i++){
        j+=transUInt(*str_ptr--)*pow_get(16, i);
    }
    return j;
}

//
void LED_Low_Bit() {
  GPIOSetBitValue( 0, mDIN_H, 0 );
  GPIOSetBitValue( 0, mDIN_L, 0 );
  mrtDelay(1 );

  GPIOSetBitValue( 0, mDIN_H, 0 );
  GPIOSetBitValue( 0, mDIN_L, 1 );
  mrtDelay(1 );
}

void LED_Hi_Bit() {
  GPIOSetBitValue( 0, mDIN_H, 1 );
  GPIOSetBitValue( 0, mDIN_L, 1 );
  mrtDelay(1 );
  GPIOSetBitValue( 0, mDIN_H, 0 );
  GPIOSetBitValue( 0, mDIN_L, 1 );
  mrtDelay(1 );
}

//
void LED_Set() {
  GPIOSetBitValue( 0, mDIN_H, 0 );
  GPIOSetBitValue( 0, mDIN_L, 1 );
  mrtDelay(1 );
}
//
void LED_Init() {
  GPIOSetBitValue( 0, mDIN_H, 0 );
  GPIOSetBitValue( 0, mDIN_L, 1 );
  mrtDelay(10 );
}
//
int Is_bitPosition(int src , int Position){
    int iRet=0;
        int    iLen=mBit_MAX;
        char    buff[mBit_MAX+1];
        int     bin;
        int     i1;

        bin = src;
        buff[iLen] = '\0';
        for(int j = 0; j < iLen; j++){
            buff[j]='0';
        }
        for(i1 = 0; i1 < iLen; i1++){
                if(i1 != 0 && bin == 0)
                        break;
                if(bin % 2 == 0)
                        buff[(iLen-1)-i1] = '0';
                else
                        buff[(iLen-1)-i1] = '1';
                bin = bin / 2;
        }
//printf(">>>%s\n", buff );
    if(strlen(buff) >= 8 ){
      if(buff[Position]=='1'){ iRet=1; }
    }
   return iRet;
}
//
void LED_Color_RGB(unsigned int led_r, unsigned int led_g, unsigned int led_b) {
	  //blue
	  for (int k = 0; k < mBit_MAX; k++){
	      if( Is_bitPosition(led_b , k)==1){
	          LED_Hi_Bit();
	      }else{
	          LED_Low_Bit();
	      }
	  }
	  //green
	  for (int k = 0; k < mBit_MAX; k++){
	      if( Is_bitPosition(led_g , k)==1){
	          LED_Hi_Bit();
	      }else{
	          LED_Low_Bit();
	      }
	  }
	  //red
	  for (int k = 0; k < mBit_MAX; k++){
	      if( Is_bitPosition(led_r , k)==1){
	          LED_Hi_Bit();
	      }else{
	          LED_Low_Bit();
	      }
	  }
}
void display_color(char* sRGB)
{
    int iSt=4;
    char s16_r[2+1];
    char s16_g[2+1];
    char s16_b[2+1];
    s16_r[0]=sRGB[iSt];
    s16_r[1]=sRGB[iSt+1];
    s16_r[2]='\0';
    s16_g[0]=sRGB[iSt+2];
    s16_g[1]=sRGB[iSt+3];
    s16_g[2]='\0';
    s16_b[0]=sRGB[iSt+4];
    s16_b[1]=sRGB[iSt+5];
    s16_b[2]='\0';
    unsigned int i_R= hexToUInt(s16_r);
    unsigned int i_G= hexToUInt(s16_g);
    unsigned int i_B= hexToUInt(s16_b);
    //
    for(int n=0;n< mLED_MAX;n++){
      LED_Color_RGB(0x00, 0x00, 0x00);
    }
    LED_Set();
    mrtDelay( 500 );
    //
    for(int n=0;n< mLED_MAX;n++){
     LED_Color_RGB(i_R, i_G, i_B );
    }
    LED_Set();
//    mrtDelay( 2000);
}
void init_proc(){
    GPIOSetBitValue( 0, mDIN_H, 0 );
    GPIOSetBitValue( 0, mDIN_L, 1 );
    LED_Init();
    mrtDelay(10 );
}

//
int main (void) 
{                       /* Main Program */
	SystemCoreClockUpdate();
	SwitchMatrix_Init();
    GPIOSetDir( 0, mDIN_H, 1 );
    GPIOSetDir( 0, mDIN_L, 1 );
//    uart0Init( 115200 );
    uart0Init( 9600 );

	mrtInit(__SYSTEM_CLOCK/1000);
	init_proc();
	uart0puts("#Main-Start 9600" );
	uart0puts("\n\r");

	char readbuf[10 +1];
	char c;
	int iMaxStr=10;
	int bufpos=0;
	while(1)
	{
		bufpos=0;
		for(int i = 0 ; i <= iMaxStr ; i++) readbuf[i]=0;
		while(1)
	    {
			if(!uart0test()) continue;
			c = uart0read();
			readbuf[bufpos]= c;
			bufpos++;
//			mrtDelay(1);
			if(strlen(readbuf) >= iMaxStr){
				//readbuf[iMaxStr]='\0';
uart0puts("readbuf=" );
uart0puts(readbuf );
uart0puts("\n\r");
				char sHead[4+1];
				strncpy(sHead, readbuf ,4);
				sHead[4]='\0';
//uart0puts("sHead=" );
//uart0puts(sHead );
//uart0puts("\n\r");
				if(strcmp(sHead , "rgb=")==0){
					display_color(readbuf);
				}
				break;
			}else if(strlen(readbuf) >0){
				if(strncmp(readbuf , "r", 1)!=0 ){
					for(int i = 0 ; i <= iMaxStr ; i++) readbuf[i]=0;
					break;
				}
			}
	    } //end_while_2
  } //end_while_1

}
