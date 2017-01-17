/**
 *  Filename: hyperrb.h
 *   Created: 2016-04-19 09:18:15
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#ifndef HYPER_RB_H
#define HYPER_RB_H
#include <stdint.h>
typedef struct __hyper_rb_counter
{
    uint64_t freeq_get_fail;
    uint64_t freeq_get_success;
    uint64_t freeq_put_fail;
    uint64_t freeq_put_success;
    uint64_t busyq_get_fail;
    uint64_t busyq_get_success;
    uint64_t busyq_put_fail;
    uint64_t busyq_put_success;
}hyper_rb_counter_t;      //用来对环形队列的运行情况进行统计
typedef struct __hyper_rb
{
    uint32_t num;
    uint32_t struct_size;
    void* freeq;
    void* busyq;
    void* pool;   //真正存储数据
    void* bottom;   //池子底部, 用于检测放入指针的有效性
    hyper_rb_counter_t counter;
}hyper_rb_t;
#endif
