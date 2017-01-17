/**
 *  Filename: b_tree.c
 *   Created: 2016-02-17 16:15:16
 *      Desc: TODO (some description)
 *    Author: du.shangkun(qianmo du), du.shangkun@ampthon.com
 *   Company: Tianyuan Tetong
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct __treenode
{
    struct __treenode* left;
    struct __treenode* right;
    int      data;
    int      height;
}treenode;
#define MAX(left, right) \
    (left > right ? left:right)
int height(treenode* p)
{
    int hl;
    int hr;
    int h;
    if(p == NULL)
    {
        return -1;
    }
    else
    {
        hl = height(p->left);
        hr = height(p->right);
    }
    h = MAX(hl, hr) + 1;
    return h;
}
treenode* insert(int x, treenode* root)
{
    if(root == NULL)
    {
        root = malloc(sizeof(treenode));
        if(root == NULL)
        {
            printf("malloc failed!(%s:%d)\n", __func__, __LINE__);
            exit(-1);
        }
        else
        {
            root->height = 0;
            root->data = x;
            root->left = NULL;
            root->right = NULL;
            return root;
        }
    }
    else if(x > root->data)
    {
        root->right = insert(x, root->right);
    }
    else
    {
        root->left = insert(x, root->left);
    }
    return root;
}
treenode* find(int x, treenode* root)
{
    treenode* tmp;
    if(x == root->data)
    {
        return root;
    }
    else if(x < root->data)
    {
        tmp = find(x, root->left);
        return tmp;

    }
    else 
    {
        tmp = find(x, root->right);
        return tmp;
    }
}
int main(int argc, char* argv[])
{
    treenode* root = NULL;
    treenode* tmp = NULL;
    int h;
    root = insert(10, root);
    insert(2, root);
    insert(11, root);
    insert(12, root);
    insert(8, root);
    tmp = find(10, root);
    printf("val:%d\n", tmp->data);
    h = height(tmp);
    printf("height:%d\n", h);
    return 0;
}
