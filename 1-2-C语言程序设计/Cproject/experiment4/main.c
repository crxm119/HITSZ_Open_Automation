#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************
**�ж�һ�����Ƿ�Ϊ���������ֽ�������

����1��(1):�ж��Ƿ�Ϊ�����У�Forѭ���в�������ʱֻ��Ҫ��sqrt(num)��
�������������²鿴ʵ����˵���ĵ��е����ݡ�
(2): �޸ĳɳ�������Ϊ0��count+1 ����ôֻ��Ҫ�ж�count==1�����ж��Ƿ�Ϊ������
***************/

int main()
{
    printf("Number:190410102\nsubject No.4-program No.1\n\n");

    int number,num,i,j,k,count;
    char ans;

    //ѭ���ж�
    for(k=1;; k++)
    {


        //����һ����
        printf("������һ����Ҫ�ж��Ƿ�Ϊ��������������");
        scanf("%d",&number);
        count=0;
        num=number;//nun�����м�ֵ

        //��Ϊ1,2ʱ
        if(number==1)
        {
            printf("It's neither a prime nor decomposable.\n");
        }
        /**revise**/
       /*if(number==2)
       {
           printf("2=1*2\n");
        }*/

        //������2
        if(number>=2)
        {
            /**revise:sqrt**/
            for(i=1; i<=sqrt(number); i++)//�õ���������
            {
                if(number%i==0)
                    count++;
                else
                {
                    ;
                }
            }

            if(count==1)//�ж�Ϊ����
            {
                printf("It's a prime number.\n");
            }

            else//�ж�Ϊ������
            {
                printf("%d=1",number);
                for(i=2; i<=number-1; i++)
                {
                    for(j=i;;)//��ͬһ�����Ӷ��طֽ�
                    {
                        if(num%j==0)
                        {
                            printf("*%d",j);
                            num=num/j;
                        }
                        else
                            break;
                    }
                }
                printf("\n");
            }
        }

        //ѯ���Ƿ�����ж�
        printf("Do you want to continue?\nYes please type 'y'or 'Y', no please type 'n' or 'N'.  ");
        while(getchar()!='\n');
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y');
        else
            break;
    }
    return 0;
}
