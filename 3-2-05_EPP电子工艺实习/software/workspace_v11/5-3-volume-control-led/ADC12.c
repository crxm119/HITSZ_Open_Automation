/*
 * ad.c
 *
 *  Created on: 2018-2-10
 *      Author: Liu
 */
#include "ADC12.h"

//ADC ��ʼ��
//void ADInit(char channel)
//{
//    ADC12CTL0 |= ADC12MSC;                                      //�Զ�ѭ������ת��
//    ADC12CTL0 |= ADC12ON;                                       //����ADC12ģ��
//    ADC12CTL1 |= ADC12CONSEQ1 ;                                 //ѡ��ͨ��ѭ������ת��
//    ADC12CTL1 |= ADC12SHP;                                      //��������ģʽ
//    switch (channel)
//    {
//            case 0:ADC12MCTL0 |= ADC12INCH_0;    break;         //ѡ��ͨ��0��P6.0
//            case 1:ADC12MCTL0 |= ADC12INCH_1;   break;          //ѡ��ͨ��1��P6.1
//            case 2:ADC12MCTL0 |= ADC12INCH_2;   break;          //ѡ��ͨ��2��P6.2
//            case 3:ADC12MCTL0 |= ADC12INCH_3;   break;          //ѡ��ͨ��3��P6.3
//            case 4:ADC12MCTL0 |= ADC12INCH_4;   break;          //ѡ��ͨ��4��P6.4
//            case 5:ADC12MCTL0 |= ADC12INCH_5;   break;          //ѡ��ͨ��5��P6.5  ���Ӳ����λ��
//            case 6:ADC12MCTL0 |= ADC12INCH_6;   break;          //ѡ��ͨ��6��P6.6
//            case 12:ADC12MCTL0 |= ADC12INCH_12; break;          //ѡ��ͨ��12��P7.0
//            default: ;break;
//    }
//
//    ADC12CTL0 |= ADC12ENC;
//}
void InitAD()
{
ADC12CTL0 |= ADC12MSC;            //�Զ�ѭ������ת��
ADC12CTL0 |= ADC12ON;               //����ADC12ģ��
ADC12CTL1 |= ADC12CONSEQ_3 ;//ѡ������ͨ�����ѭ������ת��
ADC12CTL1 |= ADC12SHP;             //��������ģʽ
ADC12CTL1  |= ADC12CSTARTADD_0;
ADC12MCTL0 |=ADC12INCH_1;    //ͨ��ѡ��
ADC12MCTL1 |=ADC12INCH_2+ADC12EOS;
ADC12CTL0 |= ADC12ENC;
}

#define N_POINT 13
unsigned int  GetAD2()
{
    unsigned int temp = 0;          //���ñ���
    ADC12CTL0 |= ADC12SC;           //��ʼ����ת��
    temp= ADC12MEM1;                //�ѽ����������
    return temp;
}

unsigned int Filter2( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int temp=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetAD2();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   temp = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = temp;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //���Ϊ2��n�η��ȷ֣��������>>n�ļ��ټ�����  a=a*8;  ����Ϊ a=a<<3;
    //b=b/8; ����Ϊb=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}

unsigned int  GetAD1()
{
    unsigned int temp = 0;          //���ñ���
    ADC12CTL0 |= ADC12SC;           //��ʼ����ת��
    temp= ADC12MEM0;                //�ѽ����������
    return temp;
}

unsigned int Filter1( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int temp=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetAD1();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   temp = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = temp;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //���Ϊ2��n�η��ȷ֣��������>>n�ļ��ټ�����  a=a*8;  ����Ϊ a=a<<3;
    //b=b/8; ����Ϊb=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}

