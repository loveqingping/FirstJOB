/**
 *  Filename: nbk_iconv.c
 *   Created: 2014-10-30 18:56:21
 *      Desc: nbk iconv
 *    Author: xutao(Tony Xu), xu.tao@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include "nbk_iconv.h"
#include <memory.h>
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	char* p = outbuf;
	char **pin = &inbuf;
	char **pout = &outbuf;
	printf("outlen:%d\n",outlen);
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) 
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == (size_t)-1) 
	{
		iconv_close(cd);
		return -1;
	}
	printf("outbuf:%d\n",*p);
	printf("buf:%d\n",*(*pout - 1));   
	printf("buf:%c\n",*(*pout - 2));
	printf("buf:%c\n",*(*pout - 3));
	iconv_close(cd);
	return 0;
}

/* utf-8 -> gb2312 */
int u2g(char *inbuf, int inlen, char *outbuf, int outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

/* gb2132 -> utf-8 */
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

/* 是否是 gb2312 编码 */
int is_gb2312(const unsigned char *str, size_t size)
{
	int is_gb2312 = 1;
	unsigned char *start = (unsigned char *)str;
	unsigned char *end = (unsigned char *)str + size;

	while (start < end) {
		if (*start < 0x80)		//0x00~0x7F ASCII码
			start++;
		else if (*start < 0xA1)	//0x80~0xA0 空码
		{
			is_gb2312 = 0;
			break;
		} else if (*start < 0xAA)	//0xA1~0xA9 字符部分
		{
			if (start >= end - 1)
				break;
//低字节范围 0xA1~0xFE
			if (start[1] < 0xA1 || start[1] > 0xFE) {
				is_gb2312 = 0;
				break;
			}
			start += 2;
		} else if (*start < 0xB0)	//0xAA~0xAF 空码
		{
			is_gb2312 = 0;
			break;
		} else if (*start < 0xF8)	//0xB0~0xF7 是对GB2312汉字表的扩充
		{
			if (start >= end - 1)
				break;
            /* 低字节范围 0xA1~0xFE(剔除0x7F) */
			if (start[1] < 0xA1 || start[1] > 0xFE) {
				is_gb2312 = 0;
				break;
			}
			start += 2;
		} else					//0xFF 空码
		{
			is_gb2312 = 0;
			break;
		}
	}

	return is_gb2312;
}
