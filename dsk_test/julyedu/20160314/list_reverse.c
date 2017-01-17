/**
 *  Filename: list_reverse.c
 *   Created: 2016-03-14 10:24:28
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
/*
 *
 *链表逆置
 * head->1->2->3->4->5
 *
 */
typedef struct __node
{
    int val;
    struct __node* next;
}node_t;
int list_add(node_t* phead, int val)
{
    if(phead == NULL)
    {
        fprintf(stderr, "pointer is NULL!\n");
        exit(-1);
    }
    node_t* p = malloc(sizeof(node_t));
    p->val = val;
    p->next = phead->next;
    phead->next = p;
    return 0;
}
int print_list(node_t* phead)
{
    node_t* p = phead->next;
    while( p!= NULL)
    {
        printf("%d", p->val);
        printf("->");
        p = p->next;
    }
    printf("NULL");
    printf("\n");
    return 0;
}
int list_reverse(node_t* phead, int from, int to)
{
    int i = 0;
    node_t* phead_r = phead;   //链表from处的前一个节点
    for(i = 0; i < from - 1; ++i)
    {
        phead_r = phead_r->next;
    }
#if 1
    if(phead_r == NULL)
    {
        goto ERROR;
    }
#endif
    node_t* pre = phead_r->next;
    node_t* cur = pre->next; 
    node_t* pnext = NULL;
    for(i = from + 1; i <= to; ++i)
    {
#if 1
        if(cur == NULL)
        {
            goto ERROR;
        }
#endif
        pnext = cur->next;
        cur->next = phead_r->next;
        phead_r->next = cur;
        pre->next = pnext;
        cur = pre->next;
    }
    return 0;
ERROR:
    return -1;
}
int main(int argc, char* argv[])
{
    node_t* head = NULL;
    int i = 0;
    head = malloc(sizeof(node_t));
    head->val = -1;
    head->next = NULL;
    for(i = 0; i < 7; ++i)
    {
        list_add(head, i);
    }
    print_list(head);
    list_reverse(head, 1, 7);
    print_list(head);
    return 0;
}
