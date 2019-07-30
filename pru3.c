#include <stdio.h>

int main(int argc, const char * argv[]) {

    char *s = "12345";

    printf("%d\n", s);      // 1.Outputs "3999" is this the address of the first pointer?
    printf("%d\n", *s);     // 2.The decimal value of the first character
    printf("%c\n", s);      // 3.Outputs "\237" What is this value?
    printf("%c\n", *s);     // 4.Outputs "1"
    printf("%c\n", *(s+1)); // 5.Outputs "2"
    printf("%s\n", s);      // 6.Outputs "12345"
    printf("%s\n", *s);     // 7.I get an error, why?
    return 0;
}
