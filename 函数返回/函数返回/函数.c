#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
void pound(int ch);//函数声明 形参
int main(void)
{
	int times = 5;
	char ch = '!';
	float f = 6.0;
	pound(times+10);//函数调用
	pound(ch);//实参
	pound(f);


	return 0;
}
void pound(int ch)//函数定义
{
	while (ch-- > 0)
	{
		printf("#");
	}
	printf("\n");
	return pound;

}