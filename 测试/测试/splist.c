#include <stdio.h>
#include <stdlib.h>

#include "splist.h"

SqListPtr createSqList(int capacity) {
    SqListPtr list = (SqListPtr)malloc(sizeof(SqList));
    if (list == NULL) {
        printf("Failed to allocate memory for the list.\n");
        exit(1);
    }
    list->elem = (ElemType*)malloc(sizeof(ElemType) * capacity);
    if (list->elem == NULL) {
        printf("Failed to allocate memory for the list elements.\n");
        exit(1);
    }
    list->length = 0;
    list->capacity = capacity;
    return list;
}

void destroySqList(SqListPtr list) {
    free(list->elem);
    free(list);
}

int locateElem(SqListPtr list, ElemType value) {
    for (int i = 0; i < list->length; i++) {
        if (list->elem[i] == value) {
            return i;
        }
    }
    return -1;
}

int locatePos(SqListPtr list, int pos) {
    if (pos >= 0 && pos < list->length) {
        return pos;
    }
    else {
        return -1;
    }
}

void insertElem(SqListPtr list, int pos, ElemType value) {
    if (list->length == list->capacity) {
        printf("The list is full.\n");
        return;
    }
    if (pos < 0 || pos > list->length) {
        printf("Invalid position.\n");
        return;
    }
    for (int i = list->length; i > pos; i--) {
        list->elem[i] = list->elem[i - 1];
    }
    list->elem[pos] = value;
    list->length++;
}

void deleteElem(SqListPtr list, int pos) {
    if (list->length == 0) {
        printf("The list is empty.\n");
        return;
    }
    if (pos < 0 || pos >= list->length) {
        printf("Invalid position.\n");
        return;
    }
    for (int i = pos; i < list->length - 1; i++) {
        list->elem[i] = list->elem[i + 1];
    }
    list->length--;
}

void printList(SqListPtr list) {
    if (list->length == 0) {
        printf("The list is empty.\n");
        return;
    }
    printf("The list contents are:\n");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->elem[i]);
    }
    printf("\n");
}

void mergeLists(SqListPtr list1, SqListPtr list2) {
    int i = 0, j = 0;
    while (i < list1->length && j < list2->length) {
        if (list1->elem[i] <= list2->elem[j]) {
            i++;
        }
        else {
            insertElem(list1, i, list2->elem[j]);
            i++;
            j++;
        }
    }
    while (j < list2->length) {
        insertElem(list1, i, list2->elem[j]);
        i++;
        j++;
    }
}
