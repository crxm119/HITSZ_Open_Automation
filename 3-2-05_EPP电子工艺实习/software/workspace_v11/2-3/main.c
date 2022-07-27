/*
 * 5s��ʱ��
 */

#include <msp430.h>
#include "key.h"
StrKeyFlag KeyFlag;
void delay(uint16 t)
{
    uint16 i,j,k;

    for(j=t;j>0;j--)
        for(i=250;i>0;i--)
            k=0;
}


unsigned int i=0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    IO_Init();

    //ʱ��ΪSMCLK,�Ƚ�ģʽ����ʼʱ���������
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;
    TA0CCTL0 = CCIE;                //�Ƚ����ж�ʹ��
    TA0CCR0  = 50000;               //�Ƚ�ֵ��Ϊ50000���൱��50ms��ʱ����
    while(1)
    {
        ScanKey();                          //ɨ�谴������
          if(KeyFlag.S1==1)
          {
              KeyFlag.S1=0;
              P8OUT |= BIT1;          //�γ�����Ч��
              P3OUT |= BIT6;      //�γ�����Ч��
              i=0;
                __disable_interrupt();
          }
          else{
              __enable_interrupt();
          }
//          if(KeyFlag.S2==1)
//        {
//            KeyFlag.S2=0;
//
//
//        }
    }
}
/************************��ʱ���жϺ���********************************/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    i++;
    if(i==100)
   {
        P8OUT &= ~BIT1;          //�ر�����Ч��
        P3OUT &= ~BIT6;      //�رշ�����
        i=0;
   }
}
/************************IO�ڳ�ʼ��********************************/
void IO_Init(void)
{
    P8DIR |= BIT1;              // ����P8.1��Ϊ���ģʽ  ����LED��
    P8OUT |= BIT1;  // ѡ��P8.1Ϊ�����ʽ

    P3DIR |= BIT6;              // ����P3.6��Ϊ���ģʽ  ���Ʒ�����
    P3OUT |= BIT6;  // ѡ��P3.6Ϊ�����ʽ

    P2DIR |= BIT2;
    P2OUT &=~ BIT2;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;
}

void ScanKey(void)
{
    if((P1IN&BIT2)!=BIT2)//ͨ��IO��ֵ�ó�����������Ϣ
   {
        delay(50);  //��ʱȥ��
        if((P1IN&BIT2)!=BIT2)   //ͨ��IO��ֵ�ó�����������Ϣ
        {
    KeyFlag.S1=1;
        }
   }
   if((P1IN&BIT3)!=BIT3)//ͨ��IO��ֵ�ó�����������Ϣ
   {
        delay(50);   //��ʱȥ��
        if((P1IN&BIT3)!=BIT3) //ͨ��IO��ֵ�ó�����������Ϣ
        {
                KeyFlag.S2=1;
        }
   }
   if((P2IN&BIT3)!=BIT3) //ͨ��IO��ֵ�ó�����������Ϣ
  {
        delay(50);   //��ʱȥ��
        if((P2IN&BIT3)!=BIT3)           //ͨ��IO��ֵ�ó�����������Ϣ
        {
                KeyFlag.S3=1;
        }
  }
  if((P2IN&BIT6)!=BIT6) //ͨ��IO��ֵ�ó�����������Ϣ
  {
         delay(50);//��ʱȥ��
         if((P2IN&BIT6)!=BIT6)          //ͨ��IO��ֵ�ó�����������Ϣ
         {
               KeyFlag.S4=1;
         }
   }
}

