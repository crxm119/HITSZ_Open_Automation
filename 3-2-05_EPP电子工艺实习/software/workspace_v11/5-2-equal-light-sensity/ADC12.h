/*
 * ad.h
 *
 *  Created on: 2018-2-10
 *      Author: peter Liu
 */

#ifndef ADC12_H_
#define ADC12_H_
#include <msp430.h>



void InitAD();
extern unsigned int  GetAD1();//����AD�ɼ����ݣ�
extern unsigned int Filter1( );  //AD�ɼ���������˲�����λֵƽ���˲���
extern unsigned int  GetAD2();//����AD�ɼ����ݣ�
extern unsigned int Filter2( );  //AD�ɼ���������˲�����λֵƽ���˲���

#endif /* ADC12_H_ */
