#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

// To execute C, please define "int main()"
typedef struct Queue_t {
  char *p_data;
  uint32_t head;
  uint32_t tail;
  uint32_t count; // Current data count
  uint32_t max_buffer_size;
} Queue_t;

void init_queue(Queue_t *queue, size_t size) {
  if(!queue || !size)
    return;
  queue->p_data = malloc(size);
  if(!queue->p_data)
    return;
  queue->head = 0;
  queue->tail = 0;
  queue->count = 0;
  queue->max_buffer_size = size;
}
// Return number of byte enqueued, or -1 if error
int enqueue(Queue_t *queue, char *input_data, size_t data_size) {
  if(!queue || !input_data || !data_size || !queue->p_data)
    return -1;
  int free_size = queue->max_buffer_size - queue->count;
  if(free_size == 0)
    return 0;
  int to_write = data_size>free_size?free_size:data_size;

  if(queue->head+to_write>queue->max_buffer_size) { // 2 chunk
    int first_chunk = queue->max_buffer_size-queue->head;
    memcpy(&queue->p_data[queue->head], input_data, first_chunk);
    memcpy(queue->p_data, &input_data[first_chunk], to_write-first_chunk);
  } else {
    memcpy(&queue->p_data[queue->head], input_data, to_write);
  }
  queue->head = (queue->head+to_write)%queue->max_buffer_size;
  queue->count += to_write;
  return to_write;
}

// Assuming memory already allocated for output_data
int dequeue(Queue_t *queue, char *output_data, size_t buffer_size) {
  if(!queue || !output_data || !buffer_size || !queue->p_data)
    return -1;
  if(!queue->count)
    return 0;
  int to_read = buffer_size>queue->count?queue->count:buffer_size;
  if(queue->tail+to_read>queue->max_buffer_size) {  // 2 chunk
    int first_chunk = queue->max_buffer_size-queue->tail;
    memcpy(output_data, &queue->p_data[queue->tail], first_chunk);
    memcpy(&output_data[first_chunk], queue->p_data,  to_read - first_chunk);
  } else {
    memcpy(output_data, &queue->p_data[queue->tail], to_read);
  }
  queue->tail += to_read;
  queue->tail %= queue->max_buffer_size;
  queue->count -= to_read;
  return to_read;
}

int main() {
  Queue_t queue;
  init_queue(&queue, MAX_BUFFER_SIZE);


}
