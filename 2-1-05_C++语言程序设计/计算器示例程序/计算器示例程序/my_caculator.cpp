#include <iostream>
#include <stdio.h>
#include <string>
#include "my_caculator.h"
using namespace std;
//���캯��������̨��ʾ�û�����������ʽ�����ʽ�����ַ�0-9,+,-,*,/,(,),[,],{,},��ΪӢ���ַ�
Caculator::Caculator()
{
    cout << "please input the expression"<<endl;
    string temp_string;
    getline(cin, temp_string);
    expression_ = temp_string;
    cout << "the expression is "<< expression_<<endl;
}
//���ι��캯��������������ʽ�ַ���
//input: string
Caculator::Caculator(string str)
{
    expression_ = str;
    cout << "the expression is "<< expression_<<endl;
}

Caculator::~Caculator()
{
    //dtor
}
//ʵ��������ʽ����ֵ���������ʶ�𣬺�����ƥ����ж�
int Caculator::output_num_opt_and_check_balance()
{
    //������ջ�����ڴ������
    MyStack<char> brackets_stack;
    //����string���ʽ
    for(int i=0; i<expression_.length()-1; i++)
    {
        //���Ϊ0-9.�ַ����������������У�ֱ��������0-9.�ַ�
        if(isNum(expression_[i]))
        {
            char member[16]={0};//��������ַ�������
            int m = 0;
            while(isNum(expression_[i]))
            {
                member[m++] = expression_[i++];
            }
            //���õ��������ַ�����ת��Ϊdouble��ֵ
            double num = str_to_num(member);
            //double num = std::stod(member);
            cout <<"������:"<<num<<endl;
        }

        if(isOpt(expression_[i]))
        {
            cout <<"������:"<<expression_[i]<<endl;
            //�����������,�������brackets_stack��
            if(expression_[i]=='(' || expression_[i]=='['||expression_[i]=='{')
            {
                brackets_stack.push(expression_[i]);
            }

            if(expression_[i]==')' || expression_[i]==']'||expression_[i]=='}')
            {
                //����������ţ���ջΪ�գ���ƥ�����
                if(brackets_stack.isEmpty())
                {
                     cout<<"����ƥ�����"<<endl;
                     exit(0);
                }

                else
                {
                    //����������ţ���ջ��Ԫ�����������ƥ�䣬�򵯳�ջ��Ԫ��
                    char temp = brackets_stack.getTop();
                    if(isPair(temp,expression_[i]))
                    {
                        brackets_stack.pop();
                        continue;
                    }
                    //����������ţ���ջ��Ԫ����������Ų�ƥ�䣬��ƥ�����
                    else
                    {
                        cout <<"����ƥ�����"<<endl;
                        exit(0);
                    }

                }
            }
        }
        //�����⵽�����ַǲ������ַ�������ʾ�Ƿ����ʽ
        if(!isOpt(expression_[i]) && !isNum(expression_[i]) && expression_[i] != 0)
        {
            cout <<"illegale expression:"<<expression_[i]<<endl;
            exit(0);
        }
    }
    //�����ַ���ȡ��������ջ��Ϊ�գ���ʾ��δƥ��������ţ�ƥ�����
    if(!brackets_stack.isEmpty())
    {
         cout<<"����ƥ�����"<<endl;
         exit(0);
    }

}
//���㲢����������ʽ��ֵ
double Caculator::get_caculation_result()
{
    MyStack<char> opt_stack;//����������ջ
    MyStack<double> num_stack;//����������ջ

    double num1,num2;
    char opt;

    for(int i=0; i<expression_.length(); i++)
    {
        //����������ǲ���������ѹ�������ջ
        if(isNum(expression_[i]))
        {
            char member[16]={0};
            int m = 0;
            do
            {
                member[m++] = expression_[i++];
            }
            while(isNum(expression_[i]));

            double num = str_to_num(member);
            //double num = std::stod(member);
            num_stack.push(num);
        }
        //����������ǲ�����
        if(isOpt(expression_[i]))
        {
            //��������Ĳ������������ţ������ε���������ջԪ�أ�ֱ��������ƥ���������
            if(expression_[i] == ')' || expression_[i] == ']' || expression_[i] == '}' )
            {
                while(!isPair(opt_stack.getTop(), expression_[i]))
                {
                    opt=opt_stack.pop();
                    //ÿ����һ������������Ӳ�����ջ������������������������󣬽��ѹ�������ջ
                    num1=num_stack.pop();
                    num2=num_stack.pop();
                    double temp_result = compute(num2,num1,opt);
                    num_stack.push(temp_result);
                }
                //������ƥ���������
                opt_stack.pop();
            }
            else
            {
                //���������ջΪ�գ����߲�����ջ���ķ������ȼ�С���򽫶����Ĳ�����ѹ�������ջ
                if (opt_stack.isEmpty() || PriorityTable(expression_[i])>PriorityTable(opt_stack.getTop()))
                {
                    opt_stack.push(expression_[i]);
                }
                else
                {
                    //�������ε���ջ����������ֱ��ջ�����������ȼ�С�ڶ����Ĳ���������ջΪ�գ�����ջ��Ԫ��Ϊ������
                    while(!opt_stack.isEmpty() && (PriorityTable(expression_[i])<=PriorityTable(opt_stack.getTop())) && opt_stack.getTop()!='(' && opt_stack.getTop()!='['&& opt_stack.getTop()!='{')
                    {
                        opt=opt_stack.pop();
                        num1 = num_stack.pop();
                        num2 = num_stack.pop();
                        double temp_result = compute(num2,num1,opt);
                        num_stack.push(temp_result);
                    }
                    //�������Ĳ�������ջ
                    opt_stack.push(expression_[i]);
                }
            }

        }
    }
    //��ȡ���������������ջ�л���Ԫ�أ������ε�����ֱ��������ջΪ��
    while(!opt_stack.isEmpty())
    {
        opt = opt_stack.pop();
        num1 = num_stack.pop();
        num2 = num_stack.pop();
        double temp_result = compute(num2,num1,opt);
        num_stack.push(temp_result);
    }
    return num_stack.pop();
}



bool isNum(char c)
{
	return (c>='0' && c<='9' || c=='.');
}

bool isOpt(char c)
{
	return (c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='[' || c==']'||c=='{' || c=='}') ;
}

bool isPair(char lc, char rc)
{
	return(lc=='('&&rc==')' || lc=='['&&rc==']' || lc=='{'&&rc=='}' );
}

double str_to_num(char *s)
{
	double num=0;
	bool decimal=0;
	double exp=0.1;

	while(*s)
	{
		if (*s=='.')
		{
			decimal=1;
			s++;
			continue;
		}

		if (!decimal)
		{
			num=num*10+(*s-'0');
		}
		else
		{
			num=num+(*s-'0')*exp;
			exp=exp*0.1;
		}
		s++;
	}
	return num;
}
int PriorityTable(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '(':
    case '[':
    case '{':
		return 3;

	case ')':
    case ']':
    case '}':
		return -1;
	}
}

double compute(double a1, double a2, char opt)
{
	switch (opt)
	{
	case '+':
		return a1+a2;
	case '-':
		return a1-a2;
	case '*':
		return a1*a2;
	case '/':
		return a1/a2;
	}

}
