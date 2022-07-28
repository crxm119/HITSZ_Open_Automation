#ifndef MY_EXPRESSION_H
#define MY_EXPRESSION_H

#include <string>
#include "my_stack.hpp"
using namespace std;

class Caculator
{
    public:
        Caculator();//���캯��������̨��ʾ�û�����������ʽ�����ʽ�����ַ�0-9,+,-,*,/,(,),[,],{,},��ΪӢ���ַ�
        Caculator(string str);//���ι��캯��������������ʽ�ַ���
        void output_num_opt_and_check_balance();//ʵ��������ʽ����ֵ���������ʶ�𣬺�����ƥ����ж�
        double get_caculation_result();//���㲢����������ʽ��ֵ
        virtual ~Caculator();

    protected:

    private:
        string expression_; //�洢������ʽ�ַ���
};

bool isNum(char c);//�ж�һ���ַ��Ƿ�Ϊ����0-9���Ƿ���1���񷵻�0
bool isOpt(char c);//�ж�һ���ַ��Ƿ�Ϊ���������Ƿ���1���񷵻�0
bool isPair(char lc, char rc);//�ж�lc,lr�Ƿ�ƥ�䣬�Ƿ���1���񷵻�0��ƥ���Ϊ()��[]��{}
double str_to_num(char *s);//���ַ���ת��Ϊdouble����ֵ
int PriorityTable(char c);//�������������ȼ���
double compute(double a1, double a2, char opt);//�����������㣬����������������һ�����������õ�������double

#endif // MY_EXPRESSION_H
