#include <msp430.h> 
#include "ADC12.h"

unsigned int icnt;
void IO_Init(void)
{
    P8DIR |= BIT1;                          // ����P8.1��Ϊ���ģʽ  ����LED��
    P8OUT &= ~BIT1;                          // ѡ��P8.1Ϊ�����ʽ
    P3DIR |= BIT7;
    P3OUT &= ~BIT7;

    P3DIR |= BIT6;                          // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;                          // ѡ��P3.6Ϊ�����ʽ

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
}

int apInterface_Key( void )
{
   return 0;
}

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    ADInit(ADC12INCH_2);

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CCTL0 = CCIE;                        //�Ƚ����ж�ʹ��
    TA0CCR0  = 50000;                       //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����
    __enable_interrupt();

    unsigned int ivalue = 0;              //�����жϱ���
    while(1)
    {
        //  ivalue = GetAD();               //û������˲�
        ivalue = Filter( );                 //����˲�
        if(ivalue>=2500)
        {
            P8OUT |= BIT1;
            P3OUT |= BIT7;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt=0;
        }
    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt++;
    if(icnt==200)
    {//10s�ص�
       P8OUT &= ~BIT1;
       P3OUT &= ~BIT7;
       icnt=0;
    }
}
