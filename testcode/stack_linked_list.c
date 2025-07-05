#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// To execute C, please define "int main()"
typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct Queue { 
  Node *head;
  Node *tail;
  size_t size;
} Queue;

int init_queue(Queue *queue, size_t size) {
  if(!queue)
    return -1;
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = size;
  return 0;
}

Node *create_node(void *data, size_t size) {
  if(!data || !size)
    return NULL;

  Node *new_node = malloc(sizeof(Node));
  if(!new_node)
    return NULL;
  new_node->data = malloc(size);
  if(!new_node->data) {
    free(new_node);
    return NULL;
  }
  memcpy(new_node->data, data, size);
  new_node->next = NULL;
  return new_node;
}

int enqueue(Queue *queue, void *data) {
  if(!queue || !data)
    return -1;
  Node *new_node = create_node(data, queue->size);
  if(queue->head == NULL) {
    queue->head = new_node;
    queue->tail = new_node;
  } else {
    queue->tail->next = new_node;
    queue->tail = queue->tail->next;
  }
  return 0;
}

int dequeue(Queue *queue, void *data_out) {
  if(!queue || !queue->head || !queue->head->data)
    return -1;
  memcpy(data_out, queue->head->data, queue->size);
  Node *temp=queue->head;
  queue->head = queue->head->next;
  if(queue->head == NULL) {
    queue->tail = NULL;
  }
  free(temp->data);
  free(temp);
}

int main() {

  return 0;
}
