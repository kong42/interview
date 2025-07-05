#include <stdio.h>
#include <stdlib.h>

// To execute C, please define "int main()"
typedef struct Node_t {
  int val;
  struct Node_t *next;
} Node_t;

Node_t* create_node(int val) {
  Node_t *temp = malloc(sizeof(Node_t));
  if(temp) {
    temp->val = val;
    temp->next = NULL;
  }
  return temp;
}

void free_node(Node_t *root) {
  Node_t *cur=root;
  while(cur) {
    Node_t *temp = cur;
    cur=cur->next;
    free(temp);
  }
}

void display_node(Node_t *root) {
  Node_t *cur=root;
  while(cur) {
    if(cur->next)
      printf("%d->", cur->val);
    else
      printf("%d\n", cur->val);
    cur = cur->next;
  }
}

void create_list(Node_t **root, int *p_val, size_t size) {
  *root = create_node(p_val[0]);
  Node_t *cur=*root;
  for(int i=1; i<size; ++i) {
    cur->next = create_node(p_val[i]);
    cur = cur->next;
  }
}

//----------------------------------------
Node_t *merge_sorted(Node_t *p_listA, Node_t *p_listB) {
  if(!p_listA)
    return p_listB;
  if(!p_listB)
    return p_listA;

  Node_t *curA = p_listA, *curB = p_listB, *root, *cur;
  if(curA->val < curB->val) {
    root = curA;
    curA = curA->next;
  } else {
    root = curB;
    curB = curB->next;    
  }
  cur = root;
  while(curA && curB) {
    if(curA->val < curB->val) {
      cur->next = curA;
      curA = curA->next;
    } else {
      cur->next = curB;
      curB = curB->next;      
    }
    cur = cur->next;
  }
  if(curA)
    cur->next = curA;
  if(curB)
    cur->next = curB;

  return root;
}


int main() {
  int A[] = {1, 4, 9};
  int B[] = {2, 3, 10, 12};
  Node_t *listA, *listB, *merged;
  create_list(&listA, A, sizeof(A)/sizeof(int));
  create_list(&listB, B, sizeof(B)/sizeof(int));
  //display_node(listA);
  //display_node(listB);
  merged = merge_sorted(listA, listB);
  display_node(merged);

  free_node(merged);
  //free_node(listA);
  //free_node(listB);
}
