#include <string.h>

// From libgcc
void *memset(void *dst, int c, size_t n)
{
    unsigned char *ptr = dst;

    while (n-- > 0)
        *ptr++ = c;
    return dst;
}

// From libgcc
void *memcpy(void *dst, const void *src, size_t n)
{
    char *d = dst;
    const char *s = src;

    while (n--)
        *d++ = *s++;
    return dst;
}

// From glibc
size_t strlen(const char *s)
{
    const char *char_ptr;
    const unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;

    for (char_ptr = s; ((unsigned long int) char_ptr
                          & (sizeof(longword) - 1)) != 0;
         ++char_ptr)
        if (*char_ptr == '\0')
            return char_ptr - s;
    
    longword_ptr = (unsigned long int *) char_ptr;

    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof(longword) > 4)
    {
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }
    // I don't think we want to be aborting
    // if (sizeof(longword) > 8)
    //     abort();

    for(;;)
    {
        longword = *longword_ptr++;

        if (((longword - lomagic) & ~longword & himagic) != 0)
        {
            const char *cp = (const char *) (longword_ptr - 1);

            if (cp[0] == 0)
                return cp - s;
            if (cp[1] == 0)
                return cp - s + 1;
            if (cp[2] == 0)
                return cp - s + 2;
            if (cp[3] == 0)
                return cp - s + 3;
            if (sizeof(longword) > 4)
            {
                if (cp[4] == 0)
                    return cp - s + 4;
                if (cp[5] == 0)
                    return cp - s + 5;
                if (cp[6] == 0)
                    return cp - s + 6;
                if (cp[7] == 0)
                    return cp - s + 7;

            }
        }
    }
}

// From glibc
char *strcpy(char *dst, const char *src)
{
    return memcpy(dst, src, strlen(src) + 1);
}

// From glibc
int strcmp(const char *p1, const char *p2)
{
    const unsigned char *s1 = (const unsigned char *) p1;
    const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

// From glibc
char *strchr(const char *s, int c_in)
{
    const unsigned char *char_ptr;
    const unsigned long int *longword_ptr;
    unsigned long int longword, magic_bits, charmask;
    unsigned char c;

    c = (unsigned char) c;

    for (char_ptr = (const unsigned char *) s;
         ((unsigned long int) char_ptr & (sizeof(longword) - 1)) != 0;
         ++char_ptr)
        if (*char_ptr == c)
            return (void *) char_ptr;
        else if (*char_ptr == '\0')
            return NULL;
    
    longword_ptr = (unsigned long int *) char_ptr;

    magic_bits = -1;
    magic_bits = magic_bits / 0xff * 0xfe << 1 >> 1 | 1;

    charmask = c | (c << 8);
    charmask |= charmask << 16;
    if (sizeof(longword) > 4)
        charmask |= (charmask << 16) << 16;
    // if (sizeof(longword) > 8)
    //     abort()

    for (;;)
    {
        longword = *longword_ptr++;

        if ((((longword + magic_bits)
            ^ ~longword)
            & ~magic_bits) != 0
            || ((((longword ^ charmask) + magic_bits) ^ ~(longword ^ charmask))
                & ~magic_bits) != 0)
        {
            const unsigned char *cp = (const unsigned char *) (longword_ptr - 1);

            if (*cp == c)
                return (char *) cp;
            else if (*cp == '\0')
                return NULL;
            if (*++cp == c)
                return (char *) cp;
            else if (*cp == '\0')
                return NULL;
            if (*++cp == c)
                return (char *) cp;
            else if (*cp == '\0')
                return NULL;
            if (*++cp == c)
                return (char *) cp;
            else if (*cp == '\0')
                return NULL;
            if (sizeof(longword) > 4)
            {
                if (*++cp == c)
                    return (char *) cp;
                else if (*cp == '\0')
                    return NULL;
                if (*++cp == c)
                    return (char *) cp;
                else if (*cp == '\0')
                    return NULL;
                if (*++cp == c)
                    return (char *) cp;
                else if (*cp == '\0')
                    return NULL;
                if (*++cp == c)
                    return (char *) cp;
                else if (*cp == '\0')
                    return NULL;
            }
        }
    }

    return NULL;
}

// char *strdup(const char *s)
// {

// }