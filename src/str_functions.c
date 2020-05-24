//
// Created by benedikt on 3/1/20.
//

#include "../include/defender.h"
#include "../include/my.h"

char *concat_strings(char *str1, char *str2)
{
    char *result = malloc(sizeof(char) * (my_strlen(str1) + \
my_strlen(str2)) + 1);
    int d = 0;

    if (str2 == NULL || str1 == NULL)
        return (str1);
    for (; str1[d] != '\0'; d++)
        result[d] = str1[d];
    for (int i = 0; str2[i] != '\0'; i++) {
        result[d] = str2[i];
        d++;
    }
    result[d] = '\0';
    return (result);
}

void my_strcpy(char *dest, char const *str)
{
    int i = 0;
    int begin = 0;
    int end;

    while (str[i] != '\0') {
        i += 1;
    }
    end = i;
    while (begin < end) {
        dest[begin] = str[begin];
        begin += 1;
    }
    dest[begin] = '\0';
}