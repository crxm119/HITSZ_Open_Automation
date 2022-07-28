#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define MAX_EMPLOYEE 30



void PrintfChoice()/**��ӡ��ʾ**/
{
    printf("===========================\n");
    printf("1.Input record\n2.Sort in descending order by salary\n3.search by name\n4.Search by ID\n5.List record\n0.Exit\n");
    printf("===========================\n");
    printf("Please input your choice:");
}
void InputDate(int num,struct Employ emp[])/**��������**/
{
    int i,ret;
    printf("Please input employee name ID and salary(01,5000):\n");
    for(i=0; i<=num-1; i++)
    {
        while(getchar()!='\n');
        ret=scanf("%c,%d,%d",&employee[i].name,&employee[i].ID,&employee[i].salary);
        while(ret!=3||employee[i].salary<5000-1e-5||employee[i].salary>20000+1e-5)
        {
            printf("Please input salary between 5000 and 20000:\n");
            while(getchar()!='\n');
            ret=scanf("%c,%d,%d",&employee[i].name,&employee[i].ID,&employee[i].salary);
        }
    }
}
void Order(int num,struct Employ emp[])/**����**/
{
    int listmax,idtemp,i,j;
    int salarytemp;
    char nametemp;
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].salary>emp[listmax].salary)
            {
                listmax=j;
            }

        }
        if(listmax!=i)
        {
            idtemp=emp[i].ID;
            emp[i].ID=emp[listmax].ID;
            emp[listmax].ID=idtemp;
            salarytemp=emp[i].salary;
            emp[i].salary=emp[listmax].salary;
            emp[listmax].salary=salarytemp;
            nametemp=emp[i].name;
            emp[i].name=emp[listmax].name;
            emp[listmax].name=nametemp;
        }

    }
}
int Searchbyname(int num,struct Employ emp[])/**��Ա�����ֲ���**/
{
    int i;
    char que;
    printf("SEARCH:Please input employee's name.\n");
    while(getchar()!='\n');
    que=getchar();
    for(i=0; i<=num-1; i++)
    {
        if(que==emp[i].name)
        {
            return i;
        }
    }
    return -1;
}

int SearchbyID(int num,struct Employ emp[])/**��Ա������������**/
{
    int que,i;
    printf("SEARCH:Please input employee ID.\n");
    while(getchar()!='\n');
    scanf("%d",&que);
    for(i=0; i<=num-1; i++)
    {
        if(que==emp[i].ID)
        {
            return i;
        }
    }
    return -1;

}

