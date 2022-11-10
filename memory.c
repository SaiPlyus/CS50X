#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    char *p = &s[0];

    printf("%s\n", s);
    printf("%s\n", p);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
    printf("%p\n", p);
}
