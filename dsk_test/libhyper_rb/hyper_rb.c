/**
 *  Filename: hyperrb.c
 *   Created: 2016-04-19 09:00:25
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/****************************************************************************************************/

/** @file
 *  ±¾ÎÄ¼þÖÐ°üº¬ÁË»·ÐÎ¶ÓÁÐ¿âµÄËùÓÐÍâ²¿½Ó¿Úºê¡£
 *
 *  »·ÐÎ¶ÓÁÐ¿âµÄËùÓÐÍâ²¿½Ó¿Ú¶¼ÊÇÒÔºêµÄÐÎÊ½³öÏÖµÄ¡£Êµ¼ÊÉÏÕû¸ö»·ÐÎ¶ÓÁÐ¿â½öÓÉ±¾Í·ÎÄ¼þ¹¹³É¡£
 *  <p>Ò»¸ö»·ÐÎ¶ÓÁÐÂß¼­ÉÏÊÇÓÉÒ»¸öÊý×é¡¢Ò»¸ö¶ÁÖ¸ÕëºÍÒ»¸öÐ´Ö¸Õë¹¹³ÉµÄ¡£
 *  <p>¶ÁÖ¸ÕëÖ¸Ê¾µÄÊÇÏÂÒ»´Î½«±»¶ÁÈ¡µÄÔªËØµÄÏÂ±ê£¬Ð´Ö¸ÕëÖ¸Ê¾µÄÊÇÏÂÒ»´Î±»Ð´Èë¶ÓÁÐµÄÔªËØµÄÏÂ±ê¡£
 *  <p>µ±¶ÁÖ¸ÕëµÈÓÚÐ´Ö¸ÕëÊ±£¬±íÊ¾¶ÓÁÐÎª¿Õ¡£µ±Ð´Ö¸Õë½«Ö¸ÏòµÄÏÂÒ»¸öÎªÎ»ÖÃÎª¶ÁÖ¸ÕëÖ¸Ê¾Î»ÖÃÊ±£¬±íÊ¾¶ÓÁÐÎªÂú¡£
 *  <p>Ã¿´ÎÏò¶ÓÁÐÖÐÐ´ÈëÒ»¸öÔªËØÊ±£¬Ö±½Ó½«Ð´ÈëµÄÔªËØ±»·ÅÖÃµ½Ð´Ö¸ÕëËùÔÚÎ»ÖÃ£¬È»ºóÐ´Ö¸Õë½«ÏòÇ°ÒÆ¶¯Ò»¸öÎ»ÖÃ¡£
 *  <p>Ã¿´Î´Ó¶ÓÁÐ¶ÁÈ¡Ò»¸öÔªËØÊ±£¬½«Ö±½ÓÈ¡¶ÁÖ¸ÕëËùÖ¸Î»ÖÃµÄÔªËØ£¬È»ºó¶ÁÖ¸Õë½«ÏòÇ°ÒÆ¶¯Ò»¸öÎ»ÖÃ¡£
 *  
 *  <p>ÔÚ±¾´ÎÊµÏÖ»·ÐÎ¶ÓÁÐµÄÊ±ºò£¬³ýÁË»·ÐÎ¶ÓÁÐµÄ»ù±¾¹¦ÄÜÖ®Íâ£¬»¹¿¼ÂÇµ½ÁËÏÂÁÐ2¸ö³£¼ûµÄÐèÇó£º
 *  <ol>
 *	<li>·ÅÖÃÔÚ»·ÐÎ¶ÓÁÐÖÐµÄÔªËØÓ¦¸Ã¿ÉÒÔÊÇÈÎºÎÀàÐÍ¡£¶ÔÓÚ»·ÐÎ¶ÓÁÐÀ´Ëµ£¬Êý¾ÝÀàÐÍÖ®¼äµÄÇø±ð½ö±íÏÖÎªËùÕ¼¿Õ¼äµÄ´óÐ¡²»Í¬¡£ÈçÒ»¸öÓÉÕûÊý¹¹³ÉµÄ»·ÐÎ¶ÓÁÐºÍÒ»¸öÓÉ¶ÌÕûÊý¹¹³ÉµÄ»·ÐÎ¶ÓÁÐ´ÓÂß¼­ÉÏËµ¿ÉÖ´ÐÐµÄ²Ù×÷ÊÇÏàÍ¬£¬Ö»ÊÇÔÚÊµÏÖÊ±ÐèÒª¿¼ÂÇµ½Êý¾ÝÀàÐÍµÄ²»Í¬£»</li>
 *  <li>ÎªÁË½«»·ÐÎ¶ÓÁÐÓëÆäËûÓ¦ÓÃ·½±ãµÄ¼¯³ÉÆðÀ´£¬²»×ÜÊÇÐèÒªÓÉ»·ÐÎ¶ÓÁÐ×Ô¼ºÀ´·ÖÅäÄÚ´æ¡£</li>
 *  </ol>
 * 
 *  <p>ÔÚ±¾´ÎÊµÏÖÖÐ£¬»·ÐÎ¶ÓÁÐÔÚÄÚ´æÖÐµÄ½á¹¹ÈçÏÂÍ¼ËùÊ¾£º
 *  <pre>
 *©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
 *©¦       rsize      ©¦
 *©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©È
 *©¦       bsize      ©¦
 *©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©È
 *©¦        wp        ©¦
 *©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©È
 *©¦        rp        ©¦
 *©À©¤©¤©¤©¤©¤©¤©¤©¤©¤©È
 *©¦  »·ÐÎ¶ÓÁÐµÄÔªËØ  ©¦
 *©¦    ..........    ©¦
 *©¦                  ©¦
 *©¦                  ©¦
 *©¦                  ©¦
 *©¦                  ©¦
 *©¦                  ©¦
 *©¦                  ©¦
 *©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
 * </pre>
 */
enum
{
    HYPER_RB_HANDLE_IS_NULL = -5, 
    HYPER_RB_MEMORY_ALLOC_FAILED,
    HYPER_RB_NO_AVAILABLE_ELEMENT,
    HYPER_RB_IS_FULL,
    HYPER_RB_ILLEGAL_ELEMENT,
    HYPER_RB_OK
};
#include <malloc.h>
#include "hyper_rb.h"

/** ´ú±í»·ÐÎ¶ÓÁÐµÄ½á¹¹¡£
 *  ÓÃ»§Ê¹ÓÃ»·ÐÎ¶ÓÁÐ¿âÊ±²¢²»ÐèÒªÖ±½ÓÊ¹ÓÃ¸Ã½á¹¹¡£
 */
typedef struct __ring_buffer
{
	int rsize;	/**< ±£´æ»·ÐÎ¶ÓÁÐÖÐÔªËØµÄ¸öÊý¡£ÔÚÒ»¸ö»·ÐÎ¶ÓÁÐÖÐÄÜ¹»±£´æÔªËØµÄ×î´óÊýÁ¿ÊÇrsize-1¡£*/
	int bsize;	/**< ±£´æ»·ÐÎ¶ÓÁÐÖÐÃ¿¸öÔªËØËùÕ¼¿Õ¼äµÄ´óÐ¡¡£*/
	volatile int wp;	/**< wpÊÇÐ´Ö¸Õë¡£ */
	volatile int rp;	/**< rpÊÇ¶ÁÖ¸Õë¡£ */
}RING_BUFFER;

/** PRING_BUFFER±»¶¨ÒåÎªRING_BUFFER*	*/
typedef RING_BUFFER* PRING_BUFFER;

/** @def rb_memory_required(rs, bs)
 *  ¼ÆËãÒ»¸ö°üº¬\a rs ¸ö\a bs ´óÐ¡µÄÔªËØµÄ»·ÐÎ¶ÓÁÐËùÐèÒªÕ¼ÓÃµÄÄÚ´æ´óÐ¡¡£
 *  ¸ÃºêµÄÖµ¾ÍÊÇËùÐèÄÚ´æ´óÐ¡¡£
 */
#define rb_memory_required(rs, bs) (sizeof(RING_BUFFER) + (bs) * ((rs)+1))

/** @def rb_initialize(rs, bs, pbuf)
 *  ÔÚ\a pbuf ËùÖ¸ÏòµÄÄÚ´æÖÐ£¬³õÊ¼»¯Ò»¸ö°üÀ¨\a rs ¸ö\a bs ´óÐ¡µÄÔªËØµÄ»·ÐÎ¶ÓÁÐ¡£ËùÓÐ»·ÐÎ¶ÓÁÐÔÚÊ¹ÓÃÖ®Ç°¶¼±ØÐëÊ×ÏÈÓÉ\a rb_initialize ½øÐÐ³õÊ¼»¯¡£
 *  ¸ÃºêµÄÖµÎª0Ê±±íÊ¾³õÊ¼»¯²»³É¹¦£¬·ñÔò±íÊ¾³õÊ¼»¯³É¹¦¡£³É¹¦³õÊ¼»¯Ö®ºó£¬rpºÍwp¶¼Îª0£¬±íÊ¾¶ÓÁÐÎª¿Õ¡£
 */
#define rb_initialize(rs, bs, pbuf)	\
	((pbuf)==0 ? 0 : (((PRING_BUFFER)(pbuf))->bsize = (bs), ((PRING_BUFFER)(pbuf))->rsize = (rs)+1, ((PRING_BUFFER)(pbuf))->rp = ((PRING_BUFFER)(pbuf))->wp = 0, (pbuf)))

/** @def rb_create(rs, bs, pbuf)
 *  ¸ù¾Ý\a rs ºÍ \a bs Éú³ÉÒ»¸ö»·ÐÎ¶ÓÁÐ£¬\a pbuf Ö¸ÏòÉú³ÉÖ®ºóµÄ»·ÐÎ¶ÓÁÐ¡£
 *  ¸ÃºêµÄÖµÎª0Ê±±íÊ¾Éú³É²»³É¹¦£¬·ñÔò±íÊ¾Éú³É³É¹¦¡£
 */ 
#define rb_create(rs, bs, pbuf) (pbuf=malloc(rb_memory_required(rs, bs)), rb_initialize(rs, bs, pbuf))

/** @def rb_incPtr(prb, ptr)
 *  ½«\a prb µÄÖµÏò¼Ó1£¬Èç¹û¼Ó1Ö®ºó\a prb µÄÖµ²»Ð¡ÓÚ\a rsize Ôò\a prb ÖÃÎª0¡£\a ptr Ö¸ÏòÒ»¸ö³É¹¦³õÊ¼»¯µÄ»·ÐÎ¶ÓÁÐ¡£
 *  ¸ÃºêµÄÖµÎªÔö1Ö®ºóprbµÄÖµ¡£
 */
#define rb_incPtr(prb, ptr) ((ptr)=(((ptr)+1)%(((PRING_BUFFER)(prb))->rsize)))

/** @def rb_canRead(prb)
 *  ÅÐ¶ÏÊÇ·ñ¿É´Ó\a prb ËùÖ¸ÏòµÄ»·ÐÎ¶ÓÁÐÖÐ¶Á³öÔªËØ¡£
 *  ¸ÃºêµÄÖµÎª0Ê±£¬±íÊ¾²»¿É¶Á¡£·ñÔò±íÊ¾¿É¶Á¡£
 */
#define rb_canRead(prb) (((PRING_BUFFER)(prb))->wp != ((PRING_BUFFER)(prb))->rp)

/** @def rb_canWrite(prb)
 *  ÅÐ¶ÏÊÇ·ñ¿ÉÒÔÏò\a prb ËùÖ¸ÏòµÄ»·ÐÎ¶ÓÁÐÖÐÐ´ÈëÔªËØ¡£
 *  ¸ÃºêµÄÖµÎª0Ê±£¬±íÊ¾²»¿ÉÐ´¡£·ñÔò±íÊ¾¿ÉÒÔÐ´¡£
 */
#define rb_canWrite(prb) (((((PRING_BUFFER)(prb))->wp + 1) % (((PRING_BUFFER)(prb))->rsize)) != ((PRING_BUFFER)(prb))->rp)

/** @def rb_dataBuffer(prb, T)
 *  ·µ»Ø»·ÐÎ¶ÓÁÐÖÐ¶ÓÁÐÔªËØÊý×éµÄÊ×µØÖ·¡£\a prb Ö¸Ïò»·ÐÎ¶ÓÁÐ£¬\a T ÎªÔªËØµÄÀàÐÍ¡£
 */
#define rb_dataBuffer(prb, T) ((T*)(((unsigned char*)(prb))+sizeof(RING_BUFFER)))

/** @def rb_writePeek(prb, T)
 *  È¡»Ø½«Ð´µÄÔªËØ¡£\a prb Ö¸Ïò»·ÐÎ¶ÓÁÐ£¬\a T ÎªÔªËØµÄÀàÐÍ¡£
 */ 
#define rb_writePeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->wp])

/** @def rb_readPeek(prb, T)
 *  È¡»Ø½«¶ÁµÄÔªËØ¡£\a prb Ö¸Ïò»·ÐÎ¶ÓÁÐ£¬\a T ÎªÔªËØµÄÀàÐÍ¡£
 */ 
#define rb_readPeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->rp])

/** @def rb_writeIn(prb)
 *  ÏòÇ°ÒÆ¶¯Ð´Ö¸Õë£¬Íê³ÉÐ´²Ù×÷¡£\a prb Ö¸Ïò»·ÐÎ¶ÓÁÐ¡£
 */ 
#define rb_writeIn(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->wp)

/** @def rb_readOut(prb)
 *  ÏòÇ°ÒÆ¶¯¶ÁÖ¸Õë£¬Íê³É¶Á²Ù×÷¡£\a prb Ö¸Ïò»·ÐÎ¶ÓÁÐ¡£
 */
#define rb_readOut(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->rp) 

/** @def rb_writeInValue(prb, T, V)
 *  Ïò\a prb ËùÖ¸ÏòµÄ»·ÐÎ¶ÓÁÐÖÐÐ´ÈëÒ»¸öÀàÐÍÎª\a T £¬ÖµÎª\a V µÄÔªËØ¡£
 */ 
#define rb_writeInValue(prb, T, V) (rb_canWrite(prb) ? ((rb_writePeek(prb, T))=(V), rb_writeIn(prb), 1): 0)

/** @def rb_readOutValue(prb, T, V)
 *  ´Ó\a prb ËùÖ¸ÏòµÄ»·ÐÎ¶ÓÁÐÖÐ¶ÁÈ¡Ò»¸öÀàÐÍÎª\a T £¬ÖµÎª\a V µÄÔªËØ¡£
 */
#define rb_readOutValue(prb, T, V) (rb_canRead(prb)  ? ((V)=(rb_readPeek(prb,T)), rb_readOut(prb), 1): 0)


#define rb_GetTotal(prb)        (((PRING_BUFFER)(prb))->rsize-1) 
#define rb_occupied_slots(prb) ((((PRING_BUFFER)(prb))->wp - ((PRING_BUFFER)(prb))->rp+((PRING_BUFFER)(prb))->rsize) % (((PRING_BUFFER)(prb))->rsize))
#define rb_empty_slots(prb) (((PRING_BUFFER)(prb))->rsize - rb_occupied_slots(prb) - 1)

#define rb_Getwp(prb)   (((PRING_BUFFER)(prb))->wp%(((PRING_BUFFER)(prb))->rsize))
#define rb_Getrp(prb)   (((PRING_BUFFER)(prb))->rp%(((PRING_BUFFER)(prb))->rsize))




int hyper_rb_init_rb(hyper_rb_t* prb, uint32_t element_num, uint32_t struct_size)
{
    int i = 0;
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    prb->num = element_num;
    rb_create(prb->num, sizeof(void*), prb->freeq);
    rb_create(prb->num, sizeof(void*), prb->busyq);
    prb->pool = calloc(prb->num, struct_size);
    prb->bottom = (char*)(prb->pool) + (prb->num - 1) * struct_size;  //bottom指向最后一个元素的首地址
    if(prb->pool == NULL)
    {
        return HYPER_RB_MEMORY_ALLOC_FAILED;
    }
    for(i = 0; i < (int)prb->num; i++)
    {
        rb_writeInValue(prb->freeq, void*, (char*)(prb->pool) + i * struct_size);
    }
    return HYPER_RB_OK;
}
/*
 *对于环形队列的细节情况，其实只需要关注从freeq_get的情况以及busyq_put的情况， 如果freeq_get失败，说明freeq可用元素不够，busyq堆积的元素过多，很可能就是入库线程从busyq中获取元素的速度太慢，引起的
 *
 *
 */
int  hyper_rb_busyq_get(hyper_rb_t* prb, void** pst)
{
    void* p;
    if(prb == NULL || pst == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;    //handle为空
    }
    if(rb_canRead(prb->busyq))
    {
        p = rb_readPeek(prb->busyq, void*);
        rb_readOut(prb->busyq);
        *pst = p;
        return HYPER_RB_OK;
    }
    else
    {
        *pst = NULL;      //队列中取不到，就设置为空
        return HYPER_RB_NO_AVAILABLE_ELEMENT;
    }
}

int hyper_rb_busyq_put(hyper_rb_t* prb, void* pst)
{
    if(prb == NULL || pst  == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    if(pst < prb->pool || pst > prb->bottom)
    {
        return HYPER_RB_ILLEGAL_ELEMENT;
    }
    if(rb_canWrite(prb->busyq))
    {
        rb_writeInValue(prb->busyq, void*,  pst);
        return HYPER_RB_OK;
    }
    else
    {
        prb->counter.busyq_put_fail++;
        return HYPER_RB_IS_FULL;  //入队失败
    }
}
int  hyper_rb_freeq_get(hyper_rb_t* prb, void** pst)
{
    void* p;
    if(prb == NULL || pst == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    if(rb_canRead(prb->freeq))
    {
        p = rb_readPeek(prb->freeq, void*);
        rb_readOut(prb->freeq);
        *pst = p;
        return HYPER_RB_OK;
    }
    else
    {
        *pst = NULL;
        prb->counter.freeq_get_fail++;
        return HYPER_RB_NO_AVAILABLE_ELEMENT;
    }
}
int hyper_rb_freeq_put(hyper_rb_t* prb, void* pst)
{
    if(prb == NULL || pst  == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    if(pst < prb->pool || pst > prb->bottom)
    {
        return HYPER_RB_ILLEGAL_ELEMENT;
    }
    if(rb_canWrite(prb->freeq))
    {
        rb_writeInValue(prb->freeq, void*,  pst);
        return HYPER_RB_OK;
    }
    else
    {
        return HYPER_RB_IS_FULL;
    }
}
/*
 *  计算当前空闲队列中有多少个元素
 *  
 *  
 *
 */
int hyper_rb_freeq_occupy_slots(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int num;
    num = rb_occupied_slots(prb->freeq);
    return num;
}
/*
 *  计算当前busy队列中空闲空间个数
 *   
 */
int hyper_rb_freeq_empty_slots(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int num;
    num = rb_empty_slots(prb->freeq);
    return num;

}
/*
 *  计算当前busy队列中有多少个元素
 */
int hyper_rb_busyq_occupy_slots(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int num;
    num = rb_occupied_slots(prb->busyq);
    return num;
}
/*
 *  计算当前busy队列中空闲空间个数
 */
int hyper_rb_busyq_empty_slots(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int num;
    num = rb_empty_slots(prb->busyq);
    return num;
}


/*
 *  获取当前空闲队列的wp指针
 *  
 */
int hyper_rb_freeq_wp(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int wp;
    wp = rb_Getwp(prb->freeq);
    return wp;
}
/*
 *  
 *   
 *   获取当前空闲队列的rp指针
 */
int hyper_rb_freeq_rp(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int rp;
    rp = rb_Getrp(prb->freeq);
    return rp;
}
/*
 *  
 *   获取当前busy队列的wp指针
 */
int hyper_rb_busyq_wp(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int wp;
    wp = rb_Getwp(prb->busyq);
    return wp;
}
/*
 *
 *
 * 获取当前busy队列的rp指针
 * 
 */
int hyper_rb_busyq_rp(hyper_rb_t* prb)
{
    if(prb == NULL)
    {
        return HYPER_RB_HANDLE_IS_NULL;
    }
    int rp;
    rp = rb_Getrp(prb->busyq);
    return rp;
}

