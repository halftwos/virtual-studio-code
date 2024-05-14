#pragma once
#ifndef SPLIST_H
#define SPLIST_H

typedef int ElemType;

typedef struct SqList {
    ElemType* elem;
    int length;
    int capacity;
} SqList, * Ptr;

typedef Ptr SqListPtr;

SqListPtr createSqList(int capacity);

void destroySqList(SqListPtr list);

int locateElem(SqListPtr list, ElemType value);

int locatePos(SqListPtr list, int pos);

void insertElem(SqListPtr list, int pos, ElemType value);

void deleteElem(SqListPtr list, int pos);

void printList(SqListPtr list);

void mergeLists(SqListPtr list1, SqListPtr list2);

#endif
