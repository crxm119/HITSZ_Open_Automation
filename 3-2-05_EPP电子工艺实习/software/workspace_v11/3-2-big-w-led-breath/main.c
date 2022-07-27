/*
 * ���ʺ�����
 */
#include <msp430.h>

int main(void)
{
// stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT5; //p8.1 output/L1
    P1OUT |= BIT5;
    P2DIR |= BIT4; //p8.1 output/L1
    P2OUT &= ~BIT4;
//    P2DIR|=BIT5; //p8.1 output/L1
//    P2OUT|=BIT5;

//ClockInit();
// ѡ��ʱ��ACLK, ��� TAR��������
    TA2CTL = TASSEL_2 + TACLR + MC0;
    unsigned int period = 1e2;
    TA2CCR0 = period;   // PWM����
    TA2CCTL2 = OUTMOD_7;   // ���ģʽ7
    while (1)
    {

        unsigned int i;
        for (i = 1; i <= period; i++)
        {

            TA2CCR2 = i;  //ռ�ձ�80%
            P2DIR |= BIT5;    // P1.2 ����Ϊ���
            P2SEL |= BIT5;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
            __delay_cycles(0.25e4);
        }

        for (i = period; i >= 1; i--)
        {

            TA2CCR2 = i;  //ռ�ձ�80%
            P2DIR |= BIT5;    // P1.2 ����Ϊ���
            P2SEL |= BIT5;   // P1.2�˿�Ϊ���裬��ʱ��TA0.1
            __delay_cycles(0.25e4);
        }

    }
}
