#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

double calculate(char *string);
char readSign(char *string, char **pString);
double calcOp(double left, double right, char sign);
int isEndOfLine(char *string);
int getSpaceCount(char *string);
void trim(char *string);

int main(void) {

    printf("Vvedite vyrazhenie:\n");
    char * string = (char *) malloc(sizeof(char) * 20000);
    char * tmp;
    do {
        tmp = gets(string);
        if (!tmp) break;
        trim(string);
        double result = calculate(string);
        printf("result = %f\n", result);
    } while (tmp);

    free(string);
    return 0;
}

double calculate(char *string) {
    char *end;
    double a, b;
    char sign;
    a = strtod(string, &end);

    while (1) {
        if(isEndOfLine(end)) {
            break;
        }
        string=end;
        sign = readSign(string, &end);
        string=end;
        b = strtof(string, &end);
        a = calcOp(a, b, sign);
    }
    return a;
}

int isEndOfLine(char *string) {
    return strlen(string)==0;
}

double calcOp(double left, double right, char sign) {
    if (sign == '+') {
        return left + right;
    } else if (sign == '-') {
        return left - right;
    } else if (sign == '*') {
        return left * right;
    } else {
        printf ("Oshibka vvoda \n");
        return 0;
    }
}

char readSign(char *string, char **pString) {
    int spaceCount = getSpaceCount(string);
    char sign = string[0 + spaceCount];
    *pString = &string[1 + spaceCount];
    return sign;
}

int getSpaceCount(char *string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == ' ') {
            continue;
        }
        return i;
    }
    return 0;
}

void trim(char *string) {
    while (*string) {
        if (*string == 10 || *string == 13)
            *string = 0;
        ++string;
    }
}
