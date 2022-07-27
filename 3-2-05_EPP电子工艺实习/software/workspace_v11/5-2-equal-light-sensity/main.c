/*
 * p6.1-����AO
 * p6.2-ǰ�÷Ŵ���OPA_OUT
 */
#include <msp430.h> 
#include "ADC12.h"
#include <stdio.h>
unsigned int icnt;
unsigned int flag;
void ClockInit()
{ //����MCLK:16MHz,   SMCLK:8MHz,   ACLK:32KHz
    UCSCTL6 &= ~XT1OFF;          //����XT1
    P5SEL |= BIT2 + BIT3;             //XT2���Ź���ѡ��
    UCSCTL6 &= ~XT2OFF;          //��XT2
    __bis_SR_register(SCG0);
    UCSCTL0 = DCO0 + DCO1 + DCO2 + DCO3 + DCO4;
    UCSCTL1 = DCORSEL_4;       //DCOƵ�ʷ�Χ��28.2MHZ����
    UCSCTL2 = FLLD_5 + 1;          //D=16��N=1

    //n=8,FLLREFCLKʱ��ԴΪXT2CLK��
    //DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
    UCSCTL3 = SELREF_5 + FLLREFDIV_3;
    //ACLK��ʱ��ԴΪDCOCLKDIV,MCLK\SMCLK��ʱ��ԴΪDCOCLK
    UCSCTL4 = SELA_4 + SELS_3 + SELM_3;
    //ACLK��DCOCLKDIV��32��Ƶ�õ���SMCLK��DCOCLK��2��Ƶ�õ�
    UCSCTL5 = DIVA_5 + DIVS_1;
}
void IO_Init(void)
{
    P8DIR |= BIT1;                          // ����P8.1��Ϊ���ģʽ  ����LED��
    P8OUT &= ~BIT1;                          // ѡ��P8.1Ϊ�����ʽ
    P3DIR |= BIT7;
    P3OUT &= ~BIT7;
    P7DIR |= BIT4;                          // ����P8.1��Ϊ���ģʽ  ����LED��
    P7OUT &= ~BIT4;                          // ѡ��P8.1Ϊ�����ʽ
    P6DIR |= BIT3;
    P6OUT &= ~BIT3;
    P6DIR |= BIT4;                          // ����P8.1��Ϊ���ģʽ  ����LED��
    P6OUT &= ~BIT4;                          // ѡ��P8.1Ϊ�����ʽ
    P3DIR |= BIT5;
    P3OUT &= ~BIT5;

    P3DIR |= BIT6;                          // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;                          // ѡ��P3.6Ϊ�����ʽ

//    P1DIR |= BIT0;                          // ����P8.1��Ϊ���ģʽ  ����LED��
//    P1OUT &= ~BIT0;                          // ѡ��P8.1Ϊ�����ʽ

    P2DIR &= ~(BIT3 + BIT6);
    P2REN |= BIT3 + BIT6;
    P2OUT |= BIT3 + BIT6;

    P1DIR &= ~( BIT3 + BIT2);
    P1REN = BIT3 + BIT2;
    P1OUT |= BIT3 + BIT2;

    //����led
    P1DIR |= BIT5; //p8.1 output/L1
    P1OUT |= BIT5;
    P2DIR |= BIT4; //p8.1 output/L1
    P2OUT &= ~BIT4;
}

int apInterface_Key(void)
{
    return 0;
}

/**
 * main.c
 */

int main(void)
{
//    ClockInit();
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    InitAD();

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CCTL0 = CCIE;                        //�Ƚ����ж�ʹ��
    TA0CCR0 = 0.5 * 50000;                       //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����

    //����led pwm
    TA2CTL = TASSEL_2 + TACLR + MC0;
    unsigned int period = 4095;
    TA2CCR0 = period;   // PWM����
    TA2CCTL2 = OUTMOD_7;   // ���ģʽ7
    __enable_interrupt();

    unsigned int ivalue = 0;              //�����жϱ���
    unsigned int ivalue2 = 0;              //�����жϱ���mic
    flag = 0;

    while (1)
    {

        //  ivalue = GetAD();               //û������˲�
        ivalue = Filter1();                 //����˲�
        ivalue2 = Filter2();                 //����˲�

        if (ivalue2 >= 2500)
        {

//            P1OUT |= BIT0;

            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
            icnt = 0;
            flag = 1;
            TA2CCR2 = 1000;
        }
//        printf("%d\t%d\t%d\n", ivalue,ivalue2,icnt);
        if (flag == 1)
        {
            if (ivalue > 520)
            {
                TA2CCR2+=(int)0.01*(ivalue-520)^2;  //ռ�ձ�80%
                P2DIR |= BIT5;    // P1.2 ����Ϊ���
                P2SEL |= BIT5;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
                __delay_cycles(0.25e4);

            }
            if (ivalue < 470)
            {
                TA2CCR2-=(int)0.01*(470-ivalue)^2;  //ռ�ձ�80%
                P2DIR |= BIT5;    // P1.2 ����Ϊ���
                P2SEL |= BIT5;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
                __delay_cycles(0.25e4);

            }
//            printf("%d\t%d\n",ivalue,TA2CCR2);

        }

        if (ivalue <= 2400)
        {
            P8OUT |= BIT1;
        }
        else
        {
            P8OUT &= ~BIT1;
        }
        if (ivalue <= 1800)
        {
            P3OUT |= BIT7;
        }
        else
        {
            P3OUT &= ~BIT7;
        }
        if (ivalue <= 1200)
        {
            P7OUT |= BIT4;
        }
        else
        {
            P7OUT &= ~BIT4;
        }
        if (ivalue <= 800)
        {
            P6OUT |= BIT3;
        }
        else
        {
            P6OUT &= ~BIT3;
        }
        if (ivalue <= 600)
        {
            P6OUT |= BIT4;
        }
        else
        {
            P6OUT &= ~BIT4;
        }
        if (ivalue <= 400)
        {
            P3OUT |= BIT5;
        }
        else
        {
            P3OUT &= ~BIT5;
        }

    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

    icnt++;
    if (icnt == 2 * 200)
    {      //10s�ص�
        TA2CCR2 = 0;  //�ر�
        P2DIR |= BIT5;    // P1.2 ����Ϊ���
        P2SEL |= BIT5;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
        icnt = 0;
        flag = 0;
    }
}
