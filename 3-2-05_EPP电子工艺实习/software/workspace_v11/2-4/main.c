#include <msp430.h>
int main(void)
{
// stop watchdog timer
WDTCTL = WDTPW | WDTHOLD;

// ѡ��ʱ��ACLK, ��� TAR��������
TA0CTL = TASSEL_2 + TACLR + MC0;

TA0CCR0 = 512;   // PWM����

TA0CCTL1 = OUTMOD_7 ;// ���ģʽ7
TA0CCR1 = 410;  //ռ�ձ�80%

TA0CCTL2 = OUTMOD_7; // ���ģʽ7;
TA0CCR2 = 51;  //ռ�ձ�10%

P1DIR |= BIT2;    // P1.2 ����Ϊ���
P1SEL |= BIT2;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
P1DIR |= BIT3;    // P1.3 ����Ϊ���
P1SEL |= BIT3;   // P1.3�˿�Ϊ���裬��ʱ��TA0.2
}
