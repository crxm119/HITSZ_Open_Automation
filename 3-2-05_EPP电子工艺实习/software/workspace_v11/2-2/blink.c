
/*
 * ��ʱ1s����led1
 */
#include <msp430.h>				



void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |=BIT0;					// configure P1.0 as output


//	ClockInit();
	while(1)
	{
		P1OUT ^= BIT0;				// toggle P1.0
		__delay_cycles(1e6);     // delay
	}
}

void ClockInit()
{//����MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
     UCSCTL6 &= ~XT1OFF;       //����XT1
     P5SEL |= BIT2 + BIT3;     //XT2���Ź���ѡ��
     UCSCTL6 &= ~XT2OFF;       //��XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;  //DCOƵ�ʷ�Χ��28.2MHZ����
     UCSCTL2 = FLLD_5 + 1;       //D=16��N=1

     //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);
     //DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;

     //ACLK��ʱ��ԴΪDCOCLKDIV,
     //MCLK\SMCLK��ʱ��ԴΪDCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;

     //ACLK��DCOCLKDIV��32��Ƶ�õ���
     //SMCLK��DCOCLK��2��Ƶ�õ�
     UCSCTL5 = DIVA_5 +DIVS_1;
}

