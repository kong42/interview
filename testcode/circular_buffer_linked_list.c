#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// To execute C, please define "int main()"

typedef struct Node_t {
  void *data;
  struct Node_t *next;
} Node_t;

typedef struct Queue_t {
  size_t data_size;
  Node_t *head;
  Node_t *tail;
  pthread_mutex_t m;
  pthread_cond_t c_is_empty;
} Queue_t;

Node_t *create_node(void *p_data, size_t data_size) {
  Node_t *new_node = malloc(sizeof(Node_t));
  if(!new_node)
    return NULL;
  new_node->data = malloc(data_size);
  if(!new_node->data) {
    free(new_node);
    return NULL;
  }
  memcpy(new_node->data, p_data, data_size);
  new_node->next = NULL;
  return new_node;
}

// Return 0 for success, -1 otherwise
int queue_init(Queue_t *queue, size_t data_size) {
  if(!queue || !data_size)
    return -1;
  queue->head = NULL;
  queue->tail = NULL;
  pthread_mutex_init(&queue->m, NULL);
  pthread_cond_init(&queue->c_is_empty, NULL);
  queue->data_size = data_size;
  return 0;
}

// Return 0 for success, -1 otherwise
int enqueue(Queue_t *queue, void *p_data) {
  if(!queue || !p_data)
    return -1;
  Node_t *new_node = create_node(p_data, queue->data_size);
  if(!new_node)
    return -1;

  pthread_mutex_lock(&queue->m);
  if(!queue->head) {
    queue->head = new_node;
    queue->tail = new_node;
  } else {
    queue->tail->next = new_node;
    queue->tail = queue->tail->next;
  }
  pthread_cond_signal(&queue->c_is_empty);
  pthread_mutex_unlock(&queue->m);  
  return 0;
}

int dequeue(struct Queue_t *queue, void *p_buffer) {
  if(!queue || !p_buffer)
    return -1;
  pthread_mutex_lock(&queue->m);
  while(queue->head == NULL) {  // wait for data is ready
    pthread_cond_wait(&queue->c_is_empty, &queue->m);
  }
  memcpy(p_buffer, queue->head->data, queue->data_size);
  free(queue->head->data);
  Node_t *cur = queue->head;
  queue->head = queue->head->next;
  free(cur);
  if(queue->head == NULL)
    queue->tail = NULL;
  pthread_mutex_unlock(&queue->m);
  return 0;
}

int main() {




  return 0;
}
