#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
void menu() //���ò˵�
{
	printf("*********************\n");
	printf("*** 1. play 0.exit***\n");
	printf("*********************\n");
}
void game()//������Ϸ
{
	char ret = 0;
	char board[ROW][COL] = {0};
	//��ʼ������
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//����
	while (1)
	{
		playerMove(board, ROW, COL);
		ret = Iswin(board, ROW, COL);
		if (ret != 'C') {
			break;
		}
		DisplayBoard(board, ROW, COL);
		ComputerMove(board, ROW, COL);
		ret = Iswin(board, ROW, COL);
		if (ret != 'C') {
			break;
		}
		DisplayBoard(board, ROW, COL);
	}
	if (ret == '*') {
		printf("���Ӯ\n");
	}
	else if (ret == '#') {
		printf("����Ӯ\n");
	}
	else {
		printf("ƽ��\n");
	}
}
int main() {
	srand((unsigned int)time(NULL));
	int put = 0;
	do {
		menu();
		printf("ѡ�񣺣�>");
		scanf("%d", &put);
		switch (put) {
		case 1:
		{
			game();
				break;
		}
			
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����\n");
			break;

		}
	} while (put !=0);
	return 0;
}