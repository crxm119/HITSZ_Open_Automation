//��ͷ.h
#pragma once
class Matrix_4x4
{
private:
	double matrix[4][4];
public:
	//Ĭ�Ϲ��캯������ʼ������Ϊ��λ��
	Matrix_4x4();
	//���������캯������һ��4x4�Ķ�ά�����ʼ��
	Matrix_4x4(double a[4][4]);
	//�������캯��
	Matrix_4x4(const Matrix_4x4& a);
	//���� = �����������Ϊ�������

	//���� = �����������Ϊһ��4x4�Ķ�ά����
	// ������������� + - * 
	// ���� ^ �����Ϊ�����i���ݣ����iΪ��������δ�����

	// ���� [ ] �������ʵ��˫�±귽ʽ���ʾ���Ԫ�أ��ù����Ѿ�ʵ�֣������Լ�д��
	const double* operator[] (const int i) const { return matrix[i]; }
	double* operator[] (const int i) { return matrix[i]; }

	// ��������<< ����� >>
	friend ostream& operator <<(ostream& output, Matrix_4x4& a);
	

	Matrix_4x4 inverse();   //�������棬���ı䵱ǰ����ֵ�����������
	Matrix_4x4 transpose(); //����ת�ã����ı䵱ǰ����ֵ������ת�þ���

	void disp();
};