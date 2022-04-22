#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SPACE 5

typedef struct _node
{
    int data;
    struct _node * left;
    struct _node * right;
    bool empty;

}node;

node * create_node(int data)
{
    node * newnode = (node *)malloc(sizeof(node));
    
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->empty = false;

    return newnode;
}

node * get_predecessor(node * left_node, node ** prede_parent)
{
    if(left_node->right == NULL)
        return left_node;
    else
    {
        *prede_parent = left_node;
        return get_predecessor(left_node->right, prede_parent);
    }
}

void recur_insert_node(node * n, node * newnode)
{
    if(n->data > newnode->data)
    {
        if(n->left == NULL)
        {
            n->left = newnode;
            n->left->empty = false;
        }
        else
        {
            recur_insert_node(n->left, newnode);
        }
    }
    else if(n->data < newnode->data)
    {
        if(n->right == NULL)
        {
            n->right = newnode;
            n->right->empty = false;
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

void recur_display_tree(node * n, int curr_space, char nodetype)
{

    if(n != NULL && !n->empty)
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

        printf("-- %d%c\n", n->data, nodetype);
        
        recur_display_tree(n->left, curr_space + SPACE, 'L');

        recur_display_tree(n->right, curr_space + SPACE, 'R');
    }

    
}

node * delete_node(node * n, int data)
{
    if(n == NULL)
        return NULL;

    if (n->data == data)
    {
        if(n->left == NULL)
        {
            node * temp = n->right;
            free(n);
            n = NULL;

            return temp;
        }
        else if(n->right == NULL)
        {
            node * temp = n->left;
            free(n);
            n = NULL;

            return temp;
        }
        else
        {
            node * prede_parent = n;
            node * prede = get_predecessor(n->left, &prede_parent);
        
            n->data = prede->data;
            
            free(prede);
            if (prede_parent == n)
                prede_parent->left = NULL;
            else
                prede_parent->right = NULL;

            return n;
        }
    }
    else if(n->data < data)
    {
        n->right = delete_node(n->right, data);
        return n->right;
    }
    else if(n->data > data)
    {
        n->left = delete_node(n->left, data);
        return n->left;
    }
    
}

void display_tree(node * n)
{
    recur_display_tree(n, 0, 'H');
}

int main(int argc, char const *argv[])
{
    node * root = NULL;

    // root = create_node(4);
    // insert_node(root, 2);
    // insert_node(root, 5);
  
    // delete_node(root, 4);
   
    // display_tree(root);

    // insert_node(root, 4);

    // display_tree(root);

    while (1)
    {
        printf("1. Display Tree\n");
        printf("2. Insert Node\n");
        printf("3. Delete Node\n");
        printf("4. Exit\n");
        printf(">> ");

        int choice;
        scanf(" %d", &choice);

        if(choice == 1)
        {
            if(root == NULL || root->empty)
                printf("The tree is empty!\n");
            else
                display_tree(root);
        }
        else if(choice == 2)
        {
            printf("Enter a number to insert\n>> ");
            int num;
            scanf(" %d", &num);

            if(root == NULL)
                root = create_node(num);
            else
                insert_node(root, num);
        }
        else if(choice == 3)
        {
            if(root == NULL)
            {
                printf("The tree is empty!\n");
                continue;
            }

            printf("Enter a number to delete\n>> ");
            int num;
            scanf(" %d", &num);

            node * temp = delete_node(root, num);
            if(temp == NULL)
                printf("That node doesn't exist!\n");
            else
            {
                printf("Node deleted successfully!\n");
                root = temp;
            }

        }
        else
            break;
    
    }
    
    return 0;
}
