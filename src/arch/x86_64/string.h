#ifndef STRING_H
#define STRING_H

#define NULL ((char *)0)

typedef unsigned long size_t;
typedef long ssize_t;

extern void *memset(void *dst, int c, size_t n);
extern void *memcpy(void *dst, const void *src, size_t n);
extern size_t strlen(const char *s);
extern char *strcpy(char *dst, const char *src);
extern int strcmp(const char *p1, const char *p2);
extern char *strchr(const char *s, int c_in);
// extern char *strdup(const char *s); --- Under construction

#endif