#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char * get_homefile()
{
    int len = strlen(getenv("HOME")) + 17;
    char* home = (char*)calloc(len, sizeof(char));
    strcat(home, getenv("HOME"));
    strcat(home, "/.savedbacklight");
    return home;
}

int get_back_int(const char * file)
{
    FILE * p = fopen(file , "r");
    char s_maxb[6];
    fgets(s_maxb, 6, p);
    fclose(p);
    return atoi(s_maxb);
}

void set_back_int(const char * _file, int _backlight)
{
    FILE * p = fopen(_file, "w+");
    fprintf(p, "%i", _backlight);
    fclose(p);
}
