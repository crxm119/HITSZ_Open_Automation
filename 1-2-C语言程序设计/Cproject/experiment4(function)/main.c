#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/***************
**�ж�һ�����Ƿ�Ϊ���������ֽ�������
***************/

int main()
{
    int ans,number,ret;
    char reply;
    do
    {


        printf("������һ����Ҫ�ж��Ƿ�Ϊ��������������");
        ret=scanf("%d",&number);

        while(number<1||number%1!=0||ret!=1)
        {
            printf("������һ����Ҫ�ж��Ƿ�Ϊ��������������");
            while(getchar()!='\n');
            ret=scanf("%d",&number);

        }
        ans=Whether_primer(number);
        switch (ans)
        {


        case 0:

            printf("It's a prime number.\n");
            break;

        case 2:

            printf("It's neither a prime nor decomposable.\n");
            break;

        case 1:

            Get_factor(number);
            break;

        }
        printf("Do you want to continue?(y/n,Y/N)    ");
        while(getchar()!='\n');
        scanf("%c",&reply);

    }while(reply=='Y'||reply=='y');

    return 0;
}
