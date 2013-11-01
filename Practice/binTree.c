#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree {
    int data ;
    struct tree * left ;
    struct tree * right ;
};
typedef struct tree node ;

void insert (node ** root, node * ins);
void avlInsert(node ** root, node * ins, int weight);

node * alloc(int val );
node * avlAlloc(int val );
void printInOrder(node * root);
int evaluate(node * root);

int main(){
    node * bintree = alloc(-1);
    int i = 0 ;
    while ( i != -1 ){
        printf("Enter: ");
        scanf("%d",&i);
        insert(&bintree,alloc(i));
        printInOrder(bintree);
        printf("\n");
        if (i==-2){
            printf("%d\n",sumTree(bintree));
        }
    }
}
node * alloc(int val ){
    node * rtn = (node *) malloc(sizeof(node));
    rtn->data = val ;
    return rtn;
}
void printInOrder(node * root){
    if ( root != NULL ){
        printInOrder(root->left);
        printf("%d ",root->data);
        printInOrder(root->right);
    }
}
int sumTree(node * root ){
    if ( root != NULL ){
        return root->data+sumTree(root->left)+sumTree(root->right);
    }
    else{
        return 0 ;
    }
}
node * avlAlloc(int val ){
    node * rtn = (node *) malloc(sizeof(node));
    rtn->data = val ;
    return rtn;
}
void insert (node ** root, node * ins){
    // if root is null
    if ( *root == NULL ){
        *root = ins ;
        return ;
    }
    if ( (*root)->data > ins->data) insert(&((*root)->left), ins);
    else insert(&((*root)->right), ins);

}

