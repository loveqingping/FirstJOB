/*
*   matcher 
        ---story

*/

#ifndef __MATCHER__H__
#define __MATCHER__H__

#define MAX_PATTERN_LEN  128
enum alg
{
    ori_ac=0,
    da_ac
};
void *matcher_create(int alg);
int  matcher_add_pattern(void* matcher, char *pattern,int32_t pattern_len, void *info);
int  matcher_compile(void *matcher);
void *matcher_find_first(void *matcher, char **text, int32_t *text_len,int32_t *state, void **session);
void *matcher_find_next( void *matcher, char **text, int32_t *text_len,int32_t *state, void **session);
void *matcher_find_all( void *matcher, char *text, int32_t text_len,int32_t max_num, void** result, int32_t *ret_num);
int  matcher_destroy(void *matcher);


int  matcher_add_pattern_r(void* matcher, char *pattern,int32_t pattern_len, void *info);
void *matcher_find_first_r(void *matcher, char **text, int32_t *text_len,int32_t *state, void **session);
void *matcher_find_next_r( void *matcher, char **text, int32_t *text_len,int32_t *state, void **session);

//tools
size_t matcher_total_mem(void *matcher);
#endif

