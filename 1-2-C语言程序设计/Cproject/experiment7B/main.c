#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/**************************
**Ա��������Ա���š�����
�������룬���򣬲���ϵͳV3.0
**************************/
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21
int main()
{
    printf("Number:190410102\nsubject No.7B-program No.1\n\n");

    /**choice�����û�ѡ��ret�����ж�������������,
    ans_search���ڽ������������count���ڼ�¼�Ƿ���������,
    employ���ڼ�¼������Ա���š�н��**/
    int choice,ret,i,ans_search,num_employee,count=0;


    /**����Ա������������ȷ�Լ��**/
    printf("Please input employee number(1<=n<=30):");
    ret=scanf("%d",&num_employee);
    while(ret!=1||num_employee<1||num_employee>MAX_EMPLOYEE)
    {
        printf("Please input employee number(1<=n<=30):");
        while(getchar()!='\n');
        ret=scanf("%d",&num_employee);
    }

    /**ϵͳѭ��ʹ��**/
    for(;;)
    {

        PrintfChoice();

        /**�����û�ѡ�񲢽���׼ȷ�Լ��**/
        ret=scanf("%d",&choice);
        while(ret!=1||choice<0||choice>6)
        {
            printf("Please input choice(0,1,2,3,4,5,6):");
            while(getchar()!='\n');
            ret=scanf("%d",&choice);
        }

        if(choice==1)/**��������**/
        {
            InputDate(num_employee,employee);
            count=1;
        }

        if(choice==2)/**���н�ʽ���**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                Orderbysalary(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("NO.%d name:%-20s ID:%d       salary:%f\n",i+1,employee[i].name,employee[i].ID,employee[i].salary);
                }
            }
        }
        if(choice==3)/**����������**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                Orderbyname(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("NO.%d name:%-20s ID:%d       salary:%f\n",i+1,employee[i].name,employee[i].ID,employee[i].salary);
                }
            }
        }

        if(choice==4)/**����������Ա��**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                ans_search=Searchbyname(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**������������ʾ**/
                }
                else
                {
                    printf("name:%-20s ID:%d       salary:%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].salary);
                }
            }
        }

        if(choice==5)/**��Ա���Ų���Ա��**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**Ա���Ų�������ʾ**/
                }
                else
                {
                    printf("name:%-20s ID:%d       salary:%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].salary);
                }
            }

        }

        if(choice==6)/**�����¼**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("name:%-20s ID:%d       salary:%f\n",employee[i].name,employee[i].ID,employee[i].salary);
                }

            }

        }

        if(choice==0)/**�˳�ϵͳ**/
        {
            break;
        }

    }

    return 0;
}
