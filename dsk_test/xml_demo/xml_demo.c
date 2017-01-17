#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xmlcfg.h"
#include <memory.h>
int main(int argc,char *argv[])
{
    xmlcfg_t tc;
    xmlcfg_list_t xmllist;
	int ret = 0;
    long v;
    char buf[1024] = {0};
    if(xmlcfg_init_file(&tc,"kun_conf.xml") != 0)
    {
        printf("kun.conf fail\n");
        exit(0);
    }
    xmlcfg_get_long(&tc,"/china/id",&v);
    printf("%d\n",(int)v);
	ret =  xmlcfg_get_str(&tc,"/china/province",buf,1024);
	if(ret <= 0)
	{
		fprintf(stderr,"load conf failed!\n");
	}
	printf("%s\n",buf);
	printf("%d\n",strlen(buf));
    return 0;
}
