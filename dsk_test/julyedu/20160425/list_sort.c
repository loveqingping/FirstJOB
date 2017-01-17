/**
 *  Filename: list_sort.c
 *   Created: 2016-04-25 08:58:26
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <malloc.h>
typedef struct __node
{
    int data;
    struct __node* next;
}node_t;
/* 寻找合适的插入位置，pre节点的数据比data小，cur节点比data大，那么pre和cur之
 * 间就是最好的插入位置
 */
node_t* search_insert_position(node_t* phead, int data)
{
    if(phead == NULL || phead->next == NULL || phead->next->next == NULL)    /*    只有一个有数据的节点，根本不用排序 */
    {
        goto ERROR;
    }
    node_t* p_cur = phead->next;
    node_t* p_pre = phead;
    while(p_cur != NULL)
    {
        if(p_cur->data >= data)
        {
           break; 
        }
        p_pre = p_cur;
        p_cur = p_cur->next;
    }
    return p_pre;
ERROR:
    return NULL;
}
node_t* list_init()
{
    node_t* p = malloc(sizeof(node_t));
    p->data = -1;
    p->next = NULL;
    return p;
}
int list_add(node_t* phead, int data)
{
    if(phead == NULL)
    {
        goto ERROR;
    }
    node_t* p = (node_t*)malloc(sizeof(node_t));
    if(p == NULL)
    {
        goto ERROR;
    }
    p->next = phead->next;
    phead->next = p;
    p->data = data;
ERROR:
    return -1;
}
int list_remove(node_t* phead, node_t* p)
{
    if(phead == NULL || p == NULL)
    {
        goto ERROR;
    }
    node_t* p_pre = phead;
    while(p_pre->next != p && p_pre != NULL)
    {
        p_pre = p_pre->next;
    }
    if(p_pre == NULL)
    {
        goto ERROR;
    }
    if(p_pre->next == p)
    {
        p_pre->next = p->next;
        p->next = NULL;
        free(p);
    }
    return 0;
ERROR:
    return -1;
}
/* head节点不存放数据   */
int list_insert_sort(node_t* phead)
{
    if(phead == NULL || phead->next == NULL || phead->next->next == NULL)
    {
        goto RETURN;
    }
    node_t* p_pre = phead->next;
    node_t* p_cur = p_pre->next;
    node_t* ptemp = NULL;
    node_t* pnext;
    int swap = 0;
    while(p_cur != NULL)
    {
        if(p_cur->data < p_pre->data)   /*   出现逆序 */
        {
            ptemp = search_insert_position(phead, p_cur->data);
            pnext = p_cur->next;
            p_cur->next = ptemp->next;
            ptemp->next = p_cur;
            p_pre->next = pnext;
            swap = 1;
        }
        if(swap == 0)
        {
            p_pre = p_cur;
            p_cur = p_pre->next;


        }
        else if(swap == 1)
        {
            p_cur = p_pre->next;
            swap = 0;
        }
    }
    return 0;
RETURN:
    return -1;
}
void list_foreach(node_t* phead)
{
    if(phead == NULL || phead->next == NULL)
    {
        goto ERROR;
    }
    node_t* p = phead->next;
    while(p != NULL)
    {
        printf("%d", p->data);
        printf("->");
        p = p->next;
    }
    printf("\n");
ERROR:
    return;
}
int main(int argc, char* argv[])
{
    node_t* phead = NULL;
    phead = list_init();
    list_add(phead, 4);
    list_add(phead, 3);
    list_add(phead, 1);
    list_add(phead, 2);
    list_add(phead, 10);
    list_add(phead, 11);
    list_add(phead, 0);
    list_foreach(phead);
    list_insert_sort(phead);
    list_foreach(phead);
    return 0;
}

