#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Number:190410102\nsubject No.3-program No.1\n\n");
    int total,n5,n2,n1,i,ret;
    printf("�����뽫Ҫ�һ�������ҽ��(������100Ԫ��:");
    ret=scanf("%d",&total);
    while(ret!=1||total<=0||total>100)
    {
        while(getchar()!='\n');
        printf("�����뽫Ҫ�һ�������ҽ��(������100Ԫ��:");
        ret=scanf("%d",&total);
    }
    n5=total/5;
    n2=(total%5)/2;
    n1=total%5-2*n2;
    printf("������ϣ���Ԫ%02d�ţ���Ԫ%02d�ţ�һԪ%02d��,��%02d��\n\n",n5,n2,n1,n5+n2+n1);
    i=1;
    while(n5>=0)
    {
        n1=total-5*n5;
        n2=0;
        printf("��%03d��Ϊ����Ԫ%02d�ţ���Ԫ%02d�ţ�һԪ%02d��,��%02d��\n",i,n5,n2,n1,n5+n2+n1);
        while(n1>=2)
        {
            i++;
            n1-=2;
            n2+=1;
            printf("��%03d��Ϊ����Ԫ%02d�ţ���Ԫ%02d�ţ�һԪ%02d��,��%02d��\n",i,n5,n2,n1,n5+n2+n1);
        }
        n5--;
        i++;
    }
    printf("��%03d��",i-1);
    return 0;
}
