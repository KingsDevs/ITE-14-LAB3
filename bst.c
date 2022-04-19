#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SPACE 5

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

void recur_display_tree(node * n, int curr_space, bool isleft)
{
    if(n != NULL)
    {
    
        for (int i = 0; i < curr_space; i++)
        {
            printf(" ");
        }

        printf("|\n");        
        
        for (int i = 0; i < curr_space; i++)
        {
            printf(" ");
        }

        printf("-- %d\n", n->data);

        if(n->left != NULL && n->right != NULL)
            printf("|");
        
        
        recur_display_tree(n->left, curr_space + SPACE, true);
    }

    
}

void display_tree(node * n)
{
    recur_display_tree(n, 0, true);
}

int main(int argc, char const *argv[])
{
    node * root = create_node(3);

    int nums[] = {1, 5, 4, 8, 10, 7, 2};

    for (int i = 0; i < sizeof(nums) / sizeof(int); i++)
    {
        insert_node(root, nums[i]);
    }

    display_tree(root);
    
    // printf("\nSuccess\n");

    return 0;
}
