#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/**************************
**���룬���򣬲���ϵͳ
**************************/

int main()
{
    printf("Number:190410102\nsubject No.5-program No.1\n\n");

    /**choice�����û�ѡ��ret�����ж�������������,
    ans_search���ڽ������������count���ڼ�¼�Ƿ���������,
    ListΪԱ���ţ�SalaryΪԱ�����ʣ�ave���ڽ���ƽ��ֵ**/
    int choice,ret,i,ans_search,num_employee,count=0;
    int list[30];
    double salary[30];
    double ave;

    /**����Ա������������ȷ�Լ��**/
    printf("Please input employee number(1<=n<=30):");
    ret=scanf("%d",&num_employee);
    while(ret!=1||num_employee<1||num_employee>30)
    {
        printf("Please input employee number(1<=n<=30):");
        while(getchar()!='\n');
        ret=scanf("%d",&num_employee);
    }

    /**ϵͳѭ��ʹ��**/
    for(;;)
    {
        PrintfChoice();
        scanf("%d",&choice);

        if(choice==1)/**�������ݲ�����**/
        {
            InputDate(num_employee,list,salary);
            count=1;
            Order(num_employee,list,salary);
        }

        if(choice==2)/**���㹤��ƽ��ֵ**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                ave=Average(num_employee,salary);
                printf("%lf\n",ave);
            }
        }

        if(choice==3)/**���������**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("NO.%d  %d  %lf\n",i+1,list[i],salary[i]);
                }
            }
        }

        if(choice==4)/**��Ա���Ų���Ա��**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                ans_search=Search(num_employee,list);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**Ա���Ų�������ʾ**/
                }
                else
                {
                    printf("%d  %lf\n",list[ans_search],salary[ans_search]);
                }
            }

        }

        if(choice==5)/**�����¼**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%d  %lf\n",list[i],salary[i]);
                }

            }

        }

        if(choice==6)/**�˳�ϵͳ**/
        {
            break;
        }

    }

    return 0;
}
