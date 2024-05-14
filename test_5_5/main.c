#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    int a, b, c;
    
    while (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (a + b > c && a + c > b && c + b > a)
        {
            if (a == b && a == c && c == b)
            {
                printf("Equilateral trangle");
            }
            else if ((a == b &&  b!= c) || (a == c &&  c != b) || ((b == c &&  c!= a)) ){
                printf("lsosceles triangie!");
            }
            else {
                printf("Ordinary trangle!");
            }
        }
        else
            printf("Not a triangle!");
    }

    return 0;
}
