#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define null 0

typedef struct avl_node{
    int balance;
    int data;
    struct avl_node * right;
    struct avl_node * left;
}node;

int calc_tree(node * root){
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = calc_tree(root->left);
        int right_height = calc_tree(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

int balance(node * head){
    return 0;
}
node * create(int data){
    node * new_node = (node *)malloc(sizeof(struct avl_node));
    new_node -> data = data;
    new_node -> balance = 0;
    new_node -> right = null;
    new_node -> left = null;
}
node * insert(node * head, int data){

    if(head == null)
        return create(data);

    if(data > head -> data)
        head -> right = insert(head -> right, data);
    else
        head -> left = insert(head -> left, data);

    return head;
}

node * print_pre_order(node * head){
    if(head == null)
        return head;
    print_pre_order(head -> left);
    printf("%d\n", head -> data);
    print_pre_order(head -> right);
}
int main(){
    node * start = null;
    int k;
    scanf("%d", &k);
    while(k != -1){
        start = insert(start, k);
        printf("%d\n", calc_tree(start));
        scanf("%d", &k);
    }
    print_pre_order(start);
    return 0;
}
