/*
 * ad.h
 *
 *  Created on: 2018-2-10
 *      Author: peter Liu
 */

#ifndef ADC12_H_
#define ADC12_H_
#include <msp430.h>



extern void  ADInit(char channel);  //��ʼ��ADC ��channel����AD�ɼ�ͨ��  ͨ��0��P6.0��ͨ��1��P6.1��ͨ��2��P6.2��ͨ��3��P6.3��ͨ��4��P6.4��ͨ��5��P6.5��ͨ��12��P7.0
extern unsigned int  GetAD();//����AD�ɼ����ݣ�
extern unsigned int Filter( );  //AD�ɼ���������˲�����λֵƽ���˲���


#endif /* ADC12_H_ */
