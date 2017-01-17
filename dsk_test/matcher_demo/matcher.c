#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xmlcfg.h"
#include "matcher_utils.h"
#include <strings.h>
#include <memory.h>
#define  DSK_KEYWORD_FILE "dsk_keyword.xml"
typedef struct _dsk_keyword
{
	size_t word_id;
	uint8_t word[256];
	size_t pz_id;
}dsk_keyword_t;
typedef struct _dsk_keyword_arr
{
	dsk_keyword_t *arr;
	size_t			keyword_num;
}dsk_keyword_arr_t;
typedef struct _dsk_keyword_handle
{
	int32_t		used_index;
	int32_t		back_index;
	void*		dsk_matcher_user;
	void*       dsk_matcher_content;
	size_t		keyword_num;
	dsk_keyword_t user_keyword_arr[10];
	
}dsk_keyword_handle_t;
dsk_keyword_handle_t* dsk_keyword_handle= NULL;
void* create_dsk_keyword_handle()
{
	xmlcfg_t xmlcfg;
	long tmp;
	int32_t err;
	char buf[1024];
	uint32_t keyword_num;
	xmlcfg_list_t keyword_list;
	int i = 0;
	//dsk_keyword_handle_t* dsk_keyword_handle= NULL;
	dsk_keyword_handle = (dsk_keyword_handle_t *)calloc(1,sizeof(dsk_keyword_handle_t));
	if(dsk_keyword_handle == NULL)
	{
		fprintf(stderr,"in %s,calloc for dsk_keyword_handle error!\n",__func__);
		exit(-1);
	}
	memset(&xmlcfg,0,sizeof(xmlcfg_t));
	if(xmlcfg_init_file(&xmlcfg,DSK_KEYWORD_FILE) != 0)
	{
		fprintf(stderr,"in %s,xmlcfg_init_file DSK_KEYWORD_FILE error!\n",__func__);
		exit(-1);
	}
	err = xmlcfg_get_list(&xmlcfg,"/conf/keyword",&keyword_list);
	keyword_num = xmlcfg_list_length(&keyword_list);
	printf("keyword_num %d\n",keyword_num);
	if(err)
	{
		fprintf(stderr,"num config failed %d\n",err);
		xmlcfg_close(&xmlcfg);
		exit(-1);
	}
	for(i = 0 ; i < keyword_num ;++i)
	{
		bzero(buf,1024);
		if(xmlcfg_list_get_str(&keyword_list,i,"keyword",buf,sizeof(buf)) < 0)
		{
			fprintf(stderr,"Get address failed,config file\n");
			goto error;
		}
		memcpy(dsk_keyword_handle->user_keyword_arr[i].word,buf,strlen(buf));
				
	}
	keyword_num = xmlcfg_list_length(&keyword_list);
	dsk_keyword_handle->dsk_matcher_user = matcher_create(da_ac);
	dsk_keyword_handle->dsk_matcher_content = matcher_create(da_ac);
error:
	xmlcfg_close(&xmlcfg);
	return NULL;

}
int32_t add_dsk_keyword(void* handle_p)
{
	int32_t i;
	dsk_keyword_handle_t* dsk_keyword_handle_p = (dsk_keyword_handle_t *)handle_p;
	for(i = 0;i < 3;i++)
	{
		matcher_add_pattern(dsk_keyword_handle_p->dsk_matcher_user,(char*)dsk_keyword_handle_p->user_keyword_arr[i].word, strlen((const char*)dsk_keyword_handle_p->user_keyword_arr[i].word),(void*)&dsk_keyword_handle_p->user_keyword_arr[i].word);

	}
	matcher_compile(dsk_keyword_handle_p->dsk_matcher_user);
	return 0;

	
}
int32_t search_user_keyword(char* data,...)
{
	int i = 0;
	void* ret;
	int32_t state;
	void* session;
	char* p;
	int32_t text_len;
	int32_t ret_num = 0;
	void* result[32];

	dsk_keyword_handle_t* dsk_keyword_handle_p = dsk_keyword_handle;
	state = 1;
	session = NULL;
	text_len = (int32_t)strlen(data);
	p = data;
	//fprintf(stderr,"data is:%s state is:%d\n",data),state;
	ret = matcher_find_first(dsk_keyword_handle_p->dsk_matcher_user,&p,&text_len,&state,&session);
	if(ret)
	{
		i++;
		fprintf(stderr,"%d:cur is :%s\n",i,(char *)ret);
	}
	while(ret)
	{
		ret = matcher_find_next(dsk_keyword_handle->dsk_matcher_user,&p,&text_len,&state,&session);
		if(ret)
		{
			i++;
			fprintf(stderr,"%d:next is :%s\n",i,*((char **)ret));
		}
	}
	return 0;
}
int main(int argc,char* argv[])
{
	char data[1024] = "zhongguo";
	create_dsk_keyword_handle();
	add_dsk_keyword(dsk_keyword_handle);
	search_user_keyword(data);
	return 0;
}
