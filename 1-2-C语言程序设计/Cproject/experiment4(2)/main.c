#include <stdio.h>
#include <stdlib.h>

/*********************
**�ж����Ƿ�Ϊ��ȫ��
*********************/

int main()
{
    printf("Number:190410102\nsubject No.4-program No.2\n\n");



    int number,num,i,j;
    char ans;

    //ѭ���ж�
    for(j=1;;j++)
    {


        //����һ����
        printf("������һ����Ҫ�ж��Ƿ�Ϊ��ȫ������������");
        scanf("%d",&number);
        num=0;

        if(number==1)
        {
            printf("It's not a perfect number.\n");
        }

        if(number>=2)
        {
            for(i=1; i<=number-1; i++)//���㲻ͬ���ӵĺ�
            {
                if(number%i==0)
                {
                    num+=i;
                }

            }

            if(num==number)//�ж�Ϊ��ȫ��
            {
                printf("It's a perfect number.\n");
                printf("%d=1",number);
                for(i=2; i<=number-1; i++)
                {
                    if(number%i==0)
                    {
                        printf("+%d",i);
                    }

                }
                printf("\n");

            }

            else//�ж�Ϊ����ȫ��
            {
                printf("It's not a perfect number.\n");
            }
        }

        //�Ƿ�����ж�
        printf("Do you want to continue?\nYes please type 'y'or 'Y', no please type 'n' or 'N'.   ");
        while(getchar()!='\n');
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y')
            ;
        else
            break;


    }
    return 0;
}
