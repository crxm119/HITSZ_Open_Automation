//function.cpp
#pragma once

#include<iostream>
#include<string>
#include "��ͷ.h"
#define VNAME(value) (#value)

using namespace std;

//Ĭ�Ϲ��캯������ʼ������Ϊ��λ��
Matrix_4x4::Matrix_4x4()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = 0;
	for (int i = 0; i < 4; i++)matrix[i][i] = 1;
};
//���������캯������һ��4x4�Ķ�ά�����ʼ��
Matrix_4x4::Matrix_4x4(double a[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = a[i][j];
};
//�������캯��
Matrix_4x4::Matrix_4x4(const Matrix_4x4& a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = a.matrix[i][j];
}
//���� = �����������Ϊ�������

//���� = �����������Ϊһ��4x4�Ķ�ά����
// ������������� + - * 
// ���� ^ �����Ϊ�����i���ݣ����iΪ��������δ�����

// ��������>> ����� <<
ostream& operator <<(ostream& output, Matrix_4x4& a)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			output << "\t" << a.matrix[i][j];
		output << endl;
	}

	a.disp();
	//output << "F : " << D.feet << " I : " << D.inches;
	return output;
}



Matrix_4x4 Matrix_4x4::inverse()//�������棬���ı䵱ǰ����ֵ�����������
{
	return Matrix_4x4();
}
Matrix_4x4 Matrix_4x4::transpose() //����ת�ã����ı䵱ǰ����ֵ������ת�þ���
{
	return Matrix_4x4();
}


void Matrix_4x4::disp()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << "\t" << matrix[i][j];
		cout << endl;
	}
}

