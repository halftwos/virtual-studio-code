
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct {
    int data[MAXSIZE];
    int top;
} SqStack;

void InitStack(SqStack* S) {
    S->top = -1;
}

int StackEmpty(SqStack S) {
    if (S.top == -1) {
        return 1;
    }
    return 0;
}

int StackFull(SqStack S) {
    if (S.top == MAXSIZE - 1) {
        return 1;
    }
    return 0;
}

int Push(SqStack* S, int x) {
    if (StackFull(*S)) {
        return 0;
    }
    S->top++;
    S->data[S->top] = x;
    return 1;
}

int Pop(SqStack* S, int* x) {
    if (StackEmpty(*S)) {
        return 0;
    }
    *x = S->data[S->top];
    S->top--;
    return 1;
}

int main() {
    SqStack s;
    InitStack(&s);

    // 入栈
    for (int i = 0; i < 10; i++) {
        Push(&s, i);
        printf("入栈元素：%d\n", i);
    }

    // 出栈
    int x;
    while (!StackEmpty(s)) {
        Pop(&s, &x);
        printf("出栈元素：%d\n", x);
    }

    return 0;
}
