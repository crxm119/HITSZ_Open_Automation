#include "stdafx.h"
#include "string.h"

char s1[1000], s2[1000];
int n1[1000], n2[1000];//ȫ�ֱ���Ĭ��Ϊ����Ԫ�س�ʼֵΪ0
int sum[1010];//ͬ��
int main()
{
	  //ʹ��scanf_s ʱ��Ҫ��������һ���������������ַ������������ֹ��������������ڴ�ı��������ϵͳ����
	    scanf_s("%s", s1,1000);
	    scanf_s("%s", s2,1000);

	    printf("s1=%s,len=%d\n", s1, strlen(s1));
		printf("s2=%s,len=%d\n", s2, strlen(s2));
		memset(n1, 0, sizeof(n1));//���ֹ�0
		memset(n2, 0, sizeof(n2));
		for (int i = 0; i < strlen(s1); i++)//�ַ���123 ���������������Ϊ321��Ŀ����Ϊ�˷������
		{
			n1[i] = s1[strlen(s1) - 1 - i] - '0';
		}
		for (int i = 0; i < strlen(s2); i++)//�ڶ����������n2
		{
			n2[i] = s2[strlen(s2) - 1 - i] - '0';
		}
		for (int i = 0; i <  (strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2)) ; i++) //ѭ������Ϊ �������λ��
		{
			sum[i] = n1[i] + n2[i]; //һλһλ��  �ڵ������е�����£������д�ŵ�����λ��Ϊ����ʮ��ǧ����ʵ���е�д���෴
			if (sum[i] >= 10)      //Ȼ����ǽ�λ
			{
				sum[i + 1]++;
				sum[i] -= 10;
			}
		}
		//(strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2))
		//�ӷ����㣬�������е��������λ��Ϊnʱ����ô�ӷ��Ľ�������λ��Ϊn+1�� �� max ( strlen(s1),strlen(s2) ) =2ʱ���� iȡֵ= 2 1 0 
		//ʵ���ϱ��������λ����λ��n+1 ;
		for (int i = (strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2)); i >= 0; i--)
		{
			if (sum[i] != 0)                //ֱ��ĳλ��Ϊ0   �Ӻ���ǰ�Ҳ�Ϊ0������Ҳ�����ҵ���Ϊ0�����λ��
			{
				for (int j = i; j >= 0; j--)//��ӡ���
				{
					printf("%d", sum[j]);
				}
				break;
			}
		}
		printf("\n");
	
	return 0;
}
