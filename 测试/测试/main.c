#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "splist.h"
#define MAX_CAPACITY 100
void displayMenu() {
    printf("------˳����������-----\n");
    printf("-------1.λ�ò���-------\n");
    printf("-------2.��ֵ����-------\n");
    printf("-------3.����------------\n");
    printf("-------4.ɾ��------------\n");
    printf("-------5.���------------\n");
    printf("-------6.�ϲ������-------\n");
    printf("-------0.�˳�--------------\n");
}

int main() {
    SqListPtr list = createSqList(MAX_CAPACITY);
    int choice, pos, value;
    while (1) {
        displayMenu();
        printf("���������ѡ��0-6����");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            destroySqList(list);
            return 0;
        case 1:
            printf("������Ҫ���ҵ�ֵ��");
            scanf("%d", &value);
            pos = locateElem(list, value);
            if (pos >= 0) {
                printf("ֵ %d ��λ�� %d\n", value, pos);
            }
            else {
                printf("ֵ %d ������\n", value);
            }
            break;
        case 2:
            printf("������Ҫ���ҵ�λ�ã�");
            scanf("%d", &pos);
            pos = locatePos(list, pos);
            if (pos >= 0) {
                printf("λ�� %d ��ֵΪ %d\n", pos, list->elem[pos]);
            }
            else {
                printf("��Чλ��\n");
            }
            break;
        case 3:
            printf("������Ҫ�����λ�ú�ֵ���Կո�ָ�����");
            scanf("%d %d", &pos, &value);
            insertElem(list, pos, value);
            break;
        case 4:
            printf("������Ҫɾ����λ�ã�");
            scanf("%d", &pos);
            deleteElem(list, pos);
            break;
        case 5:
            printList(list);
            break;
        case 6:
            printf("�������һ�������ĳ��Ⱥ�Ԫ�أ��Կո�ָ�����");
            scanf("%d", &list->length);
            for (int i = 0; i < list->length; i++) {
                scanf("%d", &list->elem[i]);
            }
            SqListPtr list2 = createSqList(MAX_CAPACITY);
            printf("������ڶ��������ĳ��Ⱥ�Ԫ�أ��Կո�ָ�����");
            scanf("%d", &list2->length);
            for (int i = 0; i < list2->length; i++) {
                scanf("%d", &list2->elem[i]);
            }
            mergeLists(list, list2);
            destroySqList(list2);
            break;
        default:
            printf("��Чѡ��\n");
            break;
        }
    }
}
