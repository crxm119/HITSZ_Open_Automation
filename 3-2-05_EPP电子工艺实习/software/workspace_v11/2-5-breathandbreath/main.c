/*
 * ������
 */
#include <msp430.h>
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
int main(void)
{
// stop watchdog timer
WDTCTL = WDTPW | WDTHOLD;
ClockInit();
// ѡ��ʱ��ACLK, ��� TAR��������
TA0CTL = TASSEL_2 + TACLR + MC0;
TA0CCR0 = 1000;   // PWM����
TA0CCTL1 = OUTMOD_7 ;// ���ģʽ7
while(1){

    unsigned int i;
    for( i=1;i<=1e3;i++){

            TA0CCR1 = i;  //ռ�ձ�80%
            P1DIR |= BIT2;    // P1.2 ����Ϊ���
            P1SEL |= BIT2;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
            __delay_cycles(0.25e4);
    }
    for( i=1e3
            ;i>=1;i--){

                TA0CCR1 = i;  //ռ�ձ�80%
                P1DIR |= BIT2;    // P1.2 ����Ϊ���
                P1SEL |= BIT2;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
                __delay_cycles(0.25e4);
        }

}

}
