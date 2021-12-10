#include <stdlib.h>
#include <stdio.h>

#define null NULL
typedef struct tree_node{
    int data;
    int balance;
    struct tree_node * right;
    struct tree_node * left;
}node;
struct tree_node * parent = null;


//int find_height(node *);
//void find_parent(node *, node *);
//void disp_tree(node *, node *);
//void disp_inorder(node*);
//node * create_node(int, int);
//node * insert(node *, int, int);
//void prt_lvl(node *, node *, int);



int find_height(node * root){
    if(root == null)
        return 0;
    int left_height = find_height(root->left);
    int right_height = find_height(root->right);
    return (right_height > left_height)? right_height + 1 : left_height + 1;
}

int find_balance(node * head){
    return find_height(head->left) - find_height(head -> right);
}


node * create_node(int data){
    node * temp = (node*)malloc(sizeof(struct tree_node));
    temp -> data = data;
    temp -> balance = 0;
    temp -> left = null;
    temp -> right = null;
    return temp;
}

node * rotate_right(node * critical_node){
    node *left_child = critical_node -> left;
    node *left_right_child = left_child -> right;

    left_child->right = critical_node;
    critical_node->left = left_right_child;

    critical_node -> balance = find_balance(critical_node);
    left_child -> balance = find_balance(left_child);

    return left_child;
}

node * rotate_left(node * critical_node){
    node * right_child = critical_node -> right;
    node *right_left_child = right_child -> left;

    // Perform rotation
    right_child->left = critical_node;
    critical_node->right = right_left_child;

    //  Update heights
    critical_node -> balance = find_balance(critical_node);
    right_child -> balance = find_balance(right_child);

    // Return new root
    return right_child;
}

node * insert(node * root, int data){
    if(root == null){
        return create_node(data);
    }
    if (data > root->data)
        root->right = insert(root->right, data);
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }


    int balance = find_balance(root);
    root -> balance = balance;

    if (balance > 1 && data < root->left->data)
        return rotate_right(root);

    else if (balance < -1 && data > root->right->data)
        return rotate_left(root);

    if (balance > 1 && data > root->left->data)
    {
        root->left =  rotate_left(root->left);
        return rotate_right(root);
    }

    else if (balance < -1 && data < root->right->data)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}
void find_parent(node * child, node * root){
    if(child == root){
        parent = null;
        return;
    }
    if(root != null){
        if(root -> left == child || root -> right == child) {
            //printf("parent is: %d", root -> balance);
            parent = root;
            return;
        }else{
            find_parent(child, root->left);
            find_parent(child, root->right);
        }
    }
}

void disp_inorder(node * root){
    if(root != null){
        disp_inorder(root -> left);
        printf("%d %d\n", root -> data, root -> balance);
        disp_inorder(root -> right);
    }
}



void prt_lvl(node * root, node * org, int h){
    if(root == null)
        return;
    if(h == 1) {
        printf("%d ", root->data);
        find_parent(root, org);
        if (parent != null) {
            //printf("censored powder\n"); // for debugging
            if (parent == root) {
                find_parent(root, org);
            }
            if (parent -> data > root -> data)
                printf("(%d L) ", parent -> data);
            else if (parent -> data < root -> data) {
                printf("(%d R) ", parent -> data);
            }
        }
        printf("(%d B) ", root -> balance);
    }else if(h > 1){
        prt_lvl(root -> left, org, h - 1);
        prt_lvl(root -> right, org, h - 1);
    }
}



void disp_tree(node * org, node * root){
    int height = find_height(root);
    for (int i = 1; i <= height; ++i) {
        prt_lvl(root, org, i);
        if(i != height)
            printf("\n");
    }
}
node * print_pre_order(node * head){
    if(head == null)
        return head;
    print_pre_order(head -> left);
    printf("%d\n", head -> data);
    print_pre_order(head -> right);
}

int main(){
    int data;
    scanf("%d", &data);
    node * my_root = null;
    while(data != -1){
        my_root = insert(my_root, data);
        scanf("%d", &data);
    }
    print_pre_order(my_root);
    printf("\n");
    disp_tree(my_root, my_root);
    return 0;
}
