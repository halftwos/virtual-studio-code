#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
void pound(int ch);//�������� �β�
int main(void)
{
	int times = 5;
	char ch = '!';
	float f = 6.0;
	pound(times+10);//��������
	pound(ch);//ʵ��
	pound(f);


	return 0;
}
void pound(int ch)//��������
{
	while (ch-- > 0)
	{
		printf("#");
	}
	printf("\n");
	return pound;

}