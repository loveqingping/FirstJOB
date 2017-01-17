#ifndef __XML_CFG_H___
#define __XML_CFG_H___

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

typedef enum _xml_config_type_type_ {
    xmlcfg_file,
    xmlcfg_buff
}xmlcfg_type_t;

typedef struct _xml_config_type_ {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    char filename[512];
    char *xmlbuf;
    int  xmlbuf_len;
    xmlcfg_type_t  type;
}xmlcfg_t;

typedef struct _xm_config_list_type_ {
    xmlXPathObjectPtr xpathObj;
    xmlNodeSetPtr nodes;
}xmlcfg_list_t ;


// export funcion list

int xmlcfg_init_file(xmlcfg_t *xmlcfg, const char *filename);
int xmlcfg_init_buf(xmlcfg_t *xmlcfg, char *xmlbuf, int buflen);
int xmlcfg_close(xmlcfg_t *xmlcfg);

int xmlcfg_get_long(xmlcfg_t *xmlcfg, char *expr, long *value);
int xmlcfg_get_str(xmlcfg_t *xmlcfg, char *expr, char *buf, int buflen);
int xmlcfg_get_ip(xmlcfg_t *xmlcfg, char *expr, char *ipstr, int len, int *ipv);
int xmlcfg_get_hex_long(xmlcfg_t *xmlcfg, char *expr, long *value);

int xmlcfg_get_list(xmlcfg_t *xmlcfg, char *expr, xmlcfg_list_t *list);
int xmlcfg_list_length(xmlcfg_list_t *list);
int xmlcfg_list_get_long(xmlcfg_list_t *list, int idx, char *name, long *v);
int xmlcfg_list_get_str(xmlcfg_list_t *list, int idx, char *name, char *buf, int buflen);
int xmlcfg_list_get_hex_long(xmlcfg_list_t *list, int idx, char *name, long *v);
int xmlcfg_list_get_ip(xmlcfg_list_t *list, int idx, char *name, char *ipstr, int len, int *ipv);

int xmlcfg_list_free(xmlcfg_list_t *list);


#endif
