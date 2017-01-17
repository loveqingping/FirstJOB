#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H
#include <stdint.h>
#define HTTP_URL_FINISH 0
#define HTTP_CONTENT_LENGTH_FINISH 1
typedef struct _http_session
{
	char url[256];
	int pos;
	uint32_t content_length;
}http_session_t;
http_session_t*  http_session_malloc();
#endif
