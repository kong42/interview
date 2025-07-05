#include <stdio.h>
#include <stdlib.h>

typedef struct BST_t {
  int val;
  struct BST_t *left;
  struct BST_t *right;
} BST_t;

BST_t *create_node(int val) {
  BST_t *temp = malloc(sizeof(BST_t));
  if(temp) {
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
  }
  return temp;
}

BST_t* insert_node(BST_t *root, int val) {
  if(!root) {
    return create_node(val);
  }
  if(root->val > val)
    root->left = insert_node(root->left, val);
  else
    root->right = insert_node(root->right, val);
  return root;
}

void print_tree(BST_t *root) {
  if(!root)
    return;
  print_tree(root->left);
  printf("%d ", root->val);
  print_tree(root->right);
}

int main() {
  int A[] = {5, 3, 7, 2, 4, 6, 8};
  BST_t *root=NULL;
  for(int i=0; i<sizeof(A)/sizeof(int); ++i) 
    root = insert_node(root, A[i]);

  print_tree(root);
}
