#ifndef MY_STACK_HPP_INCLUDED
#define MY_STACK_HPP_INCLUDED

#include <stdlib.h>
using namespace std;

//ջ������ջ������һ���������޵����Ա��޶��ڽ��ڱ�β���в����ɾ�����������Ա�
//��һ��ջ������Ԫ���ֳ�Ϊ��ջ����ջ��ѹջ�����ǰ���Ԫ�طŵ�ջ��Ԫ�ص����棬ʹ֮��Ϊ�µ�ջ��Ԫ�أ�
//��һ��ջ����Ԫ���ֳ�Ϊ��ջ����ջ�����ǰ�ջ��Ԫ��ɾ������ʹ�����ڵ�Ԫ�س�Ϊ�µ�ջ��Ԫ�ء�

template<class T>
class MyStack
{
    public:
        //���캯��
        MyStack()
        {
            maxsize =1;
            data = new T[maxsize];//��̬�����洢�ռ�
            top = -1;//topΪ-1��ʶ��ջ
        }
        //��������
        virtual ~MyStack()
        {
            if(data != NULL)
            {
                delete[] data;//�ͷ��ڴ�
                data = NULL;
            }
        }
        //�ж��Ƿ�Ϊ��ջ����ջ����1���ǿշ���0
        bool isEmpty()
        {
            return top==-1;
        }
        //��ȡջ��Ԫ��
        T getTop()
        {
            return data[top];
        }
        //��ջ������ջ��Ԫ�أ�������Ԫ�س�Ϊ�µ�ջ��Ԫ��
        T pop()
        {
            return data[top--];
        }
        //��ջ�����µ�Ԫ�ط���ջ��Ԫ���Ϸ�
        void push(T x)
        {
            if(top+1 == maxsize)
                expand();

            data[++top]=x;
        }

    private:
        T *data;
        int maxsize;
        int top;
        //��ջ�ռ䲻�㣬������������
        void expand()
        {
 			T* temp = data;
            data = new T[maxsize*2];
            for(int i=0; i<=top; i++)
                data[i] = temp[i];
            delete[] temp;
			temp = NULL;
            maxsize = maxsize*2;
        }
	protected:

};


#endif // MY_STACK_HPP_INCLUDED
