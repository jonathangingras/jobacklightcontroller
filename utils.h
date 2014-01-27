#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

const char* get_homefile();
int get_back_int(const char*);
void set_back_int(const char*, int);

#ifdef __cplusplus
}
#endif

#endif // UTILS_H
