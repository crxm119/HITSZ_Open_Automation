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
    printf("Number:190410102\nsubject No.8-program No.1\n\n");

    /**choice�����û�ѡ��ret�����ж�������������,
    ans_search���ڽ������������count���ڼ�¼�Ƿ���������,
    employ���ڼ�¼������Ա���š�н��**/
    int choice,ret,i,ans_search,num_employee=0,addnum;
    EMPLOY employee[MAX_EMPLOYEE];
    STATIS sta;
    for(i=1; i<=MAX_EMPLOYEE-1; i++)
    {
        employee[i].ID=0;
    }
    num_employee=Getemployee_num();
    printf("There has/have been %d employee data in file.\n",num_employee);
    Copyoutfile(num_employee,employee);

    /**ϵͳѭ��ʹ��**/
    for(;;)
    {
        PrintfChoice();
        /**�����û�ѡ�񲢽���׼ȷ�Լ��**/
        ret=scanf("%d",&choice);
        while(ret!=1||choice<0||choice>11)
        {
            printf("Please input choice(0<=n<=11):");
            while(getchar()!='\n');
            ret=scanf("%d",&choice);
        }
        if(choice==1)/**�������ݲ�¼���ļ�**/
        {
            /**����Ա������������ȷ�Լ��**/
            printf("Please input how many employee's do you want to add in(1<=n<=%d):",30-num_employee);
            ret=scanf("%d",&addnum);
            while(ret!=1||addnum<0||addnum>30-num_employee)
            {
                printf("Please input number(0<=n<=%d):",30-num_employee);
                while(getchar()!='\n');
                ret=scanf("%d",&addnum);
            }
            num_employee+=addnum;
            Inputdate(addnum,employee);
            Addinfile(addnum,employee);
            Copyoutfile(num_employee,employee);
        }
        if(choice==2)/**����Ա����ɾ������**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("DELETE:Please input employee ID.\n");
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND! FAIL TO DELETE.\n");
                }
                else
                {
                    ret=Deletedate(ans_search,num_employee,employee);
                    if(ret==0)
                    {
                        num_employee--;
                        Copyinfile(num_employee,employee);
                        printf("DELETED SUCCESSFULLY!\n");
                    }
                    else
                    {
                        printf("FAIL TO DELETE.\n");
                    }
                }
            }
        }
        if(choice==3)/**����������Ա��**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Please input employee's name:");
                ans_search=Searchbyname(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**������������ʾ**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==4)/**��Ա���Ų���Ա��**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Please input employee ID:");
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**Ա���Ų�������ʾ**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==5)/**����ְ���ڲ���Ա��**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Please input employee hire date:");
                ans_search=Searchbyhiredate(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**Ա���Ų�������ʾ**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==6)/**�޸�ָ��Ա����Ա����н������**/
        {

            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                Modify(num_employee,employee);
                Copyinfile(num_employee,employee);
            }
        }
        if(choice==7)/**ͳ��Ա�����ݣ�������ÿ��н���ܺͣ�ƽ������)**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("number of employee:%d;  SUM:%.2f;  AVEERAGE:%.2f\n",num_employee,Sum(num_employee,employee),Sum(num_employee,employee)/num_employee);
                Inputstatis(sta);
                printf("Statics is stored in file.\n");
            }
        }
        if(choice==8)/**��Ա��������**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Sort record in descending by ID.\n");
                OrderbyID(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==9)/**����������**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Sort record in descending by name.\n");
                Orderbyname(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==10)/**����ְʱ������**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                printf("Sort record in descending by hire date.\n");
                Orderbyhiredate(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==11)/**�������Ա����¼**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**δ��������¼����ʾ**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
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
