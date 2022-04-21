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

typedef struct _nodelist
{
    node ** list;
    int size;
}nodelist;


node * create_node(int data)
{
    node * newnode = (node *)malloc(sizeof(node));
    
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->empty = false;

    return newnode;
}

nodelist * create_nodelist()
{
    nodelist * list = (nodelist *)malloc(sizeof(nodelist));

    list->list = (node **)malloc(sizeof(node *));
    list->size = 0;

    return list;
}

void insert_in_nodelist(nodelist * list, node * n)
{
    if(list->size == 0)
    {
        list->list[0] = n;
        list->size ++;
    }
    else
    {
        list->list = (node **)realloc(list->list, (list->size + 1) * sizeof(node *));
        list->list[list->size] = n;
        list->size++;
    }
}


void get_inorder_seq(nodelist * inorder_sequence, node * n)
{
    if(n != NULL)
    {
        if(!n->empty)
        {
            get_inorder_seq(inorder_sequence, n->left);
            insert_in_nodelist(inorder_sequence, n);
            get_inorder_seq(inorder_sequence, n->right);
        }
    }
}

node * get_predecessor(nodelist * inorder_sequence, node * n)
{
    for (int i = 0; i < inorder_sequence->size; i++)
    {
        if(inorder_sequence->list[i] == n)
        {
            if(i == 0)
                return NULL;
            else
                return inorder_sequence->list[i - 1];
        }
    }
    
    return NULL;
}

node * get_successor(nodelist * inorder_sequence, node * n)
{
    for (int i = 0; i < inorder_sequence->size; i++)
    {
        if(inorder_sequence->list[i] == n)
        {
            if(i == inorder_sequence->size - 1)
                return NULL;
            else
                return inorder_sequence->list[i + 1];
        }
    }
    
    return NULL;
}

void recur_insert_node(node * n, node * newnode)
{
    if(n->data > newnode->data)
    {
        if(n->left == NULL || n->left->empty)
        {
            n->left = newnode;
            n->left->empty = false;
        }
        else
        {
            recur_insert_node(n->left, newnode);
        }
    }
    else if(n->data < newnode->data || n->right->empty)
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

bool delete_node(node * n, int data)
{
    if(n == NULL)
        return false;

    if (n->data == data)
    {
        if(n->left == NULL && n->right == NULL)
        {
            free(n);
            n->empty = true;
            return true;
        }
        else if(n->left != NULL && n->right == NULL)
        {
            node * temp = n;
            n = n->left;
            free(temp);

            temp->empty = true;
            return true;
        }
        else if(n->left == NULL && n->right != NULL)
        {
            node * temp = n;
            n = n->right;
            free(temp);

            temp->empty = true;
            return true;
        }
        else
        {
            nodelist * inorder_seq = create_nodelist();
            get_inorder_seq(inorder_seq, n);

            node * ps = get_predecessor(inorder_seq, n);
            if(ps == NULL)
                ps = get_successor(inorder_seq, n);
            
            int temp_data = n->data;
            n->data = ps->data;

            free(inorder_seq->list);
            free(inorder_seq);

            if(temp_data > n->data)
                return delete_node(n->left, ps->data);
            else
                return delete_node(n->right, ps->data);

        }
    }
    else if(n->data < data)
        return delete_node(n->right, data);
    else if(n->data > data)
        return delete_node(n->left, data);
    
}

void display_tree(node * n)
{
    recur_display_tree(n, 0, 'H');
}

int main(int argc, char const *argv[])
{
    node * root = NULL;

    // root = create_node(4);
    // insert_node(root, 3);
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

            bool isfound = delete_node(root, num);

            if(isfound)
                printf("The node successfully deleted!\n");
            else
                printf("Node not found!\n");

        }
        else
            break;
    
    }
    
    return 0;
}
