#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "splist.h"
#define MAX_CAPACITY 100
void displayMenu() {
    printf("------顺序表基本操作-----\n");
    printf("-------1.位置查找-------\n");
    printf("-------2.按值查找-------\n");
    printf("-------3.插入------------\n");
    printf("-------4.删除------------\n");
    printf("-------5.输出------------\n");
    printf("-------6.合并有序表-------\n");
    printf("-------0.退出--------------\n");
}

int main() {
    SqListPtr list = createSqList(MAX_CAPACITY);
    int choice, pos, value;
    while (1) {
        displayMenu();
        printf("请输入你的选择（0-6）：");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            destroySqList(list);
            return 0;
        case 1:
            printf("请输入要查找的值：");
            scanf("%d", &value);
            pos = locateElem(list, value);
            if (pos >= 0) {
                printf("值 %d 在位置 %d\n", value, pos);
            }
            else {
                printf("值 %d 不存在\n", value);
            }
            break;
        case 2:
            printf("请输入要查找的位置：");
            scanf("%d", &pos);
            pos = locatePos(list, pos);
            if (pos >= 0) {
                printf("位置 %d 的值为 %d\n", pos, list->elem[pos]);
            }
            else {
                printf("无效位置\n");
            }
            break;
        case 3:
            printf("请输入要插入的位置和值（以空格分隔）：");
            scanf("%d %d", &pos, &value);
            insertElem(list, pos, value);
            break;
        case 4:
            printf("请输入要删除的位置：");
            scanf("%d", &pos);
            deleteElem(list, pos);
            break;
        case 5:
            printList(list);
            break;
        case 6:
            printf("请输入第一个有序表的长度和元素（以空格分隔）：");
            scanf("%d", &list->length);
            for (int i = 0; i < list->length; i++) {
                scanf("%d", &list->elem[i]);
            }
            SqListPtr list2 = createSqList(MAX_CAPACITY);
            printf("请输入第二个有序表的长度和元素（以空格分隔）：");
            scanf("%d", &list2->length);
            for (int i = 0; i < list2->length; i++) {
                scanf("%d", &list2->elem[i]);
            }
            mergeLists(list, list2);
            destroySqList(list2);
            break;
        default:
            printf("无效选择\n");
            break;
        }
    }
}
