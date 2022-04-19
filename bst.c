#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct _node
{
    int data;
    struct _node * left;
    struct _node * right;

}node;

node * create_node(int data)
{
    node * newnode = (node *)malloc(sizeof(node));
    
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

void recur_insert_node(node * n, node * newnode)
{
    if(n->data > newnode->data)
    {
        if(n->left == NULL)
        {
            n->left = newnode;
        }
        else
        {
            recur_insert_node(n->left, newnode);
        }
    }

    if(n->data < newnode->data)
    {
        if(n->right == NULL)
        {
            n->right = newnode;
        }
        else
        {
            recur_insert_node(n->right, newnode);
        }
    }
}

void insert_node(node * root, int data)
{
    node * newnode = create_node(data);

    recur_insert_node(root, newnode);

}

int main(int argc, char const *argv[])
{
    node * root = create_node(1);

    int nums[] = {3, 2, 5, 4, 8, 10, 7};

    for (int i = 0; i < sizeof(nums) / sizeof(int); i++)
    {
        insert_node(root, nums[i]);
    }
    
    printf("Success\n");

    return 0;
}
