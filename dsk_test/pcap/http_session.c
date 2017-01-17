#include "http_session.h"
#include <malloc.h>
http_session_t*  http_session_malloc()
{
	http_session_t* p = calloc(1,sizeof(http_session_t));
	return p;
}
