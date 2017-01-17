#ifndef CODE_CONVERT_H
#define CODE_CONVERT_H
#include <stdio.h>
#include <iconv.h>
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen);
int u2g(char *inbuf, int inlen, char *outbuf, int outlen);
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
int is_gb2312(const unsigned char *str, size_t size);

#endif
