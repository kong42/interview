#include <stdio.h>
#include <stdint.h>

#define MAX_STACK_SIZE 1000  // Maximum number of elements in the stack

typedef struct Stack_t {
  uint8_t *data;     // Pointer to the stack buffer
  uint32_t top;      // Index of the top element (number of elements)
} Stack_t;

uint8_t buffer[MAX_STACK_SIZE];  // Static buffer for storing stack data

// Initialize the stack
void init_stack(Stack_t *stack) {
  if (stack) {
    stack->top = 0;
    stack->data = buffer;
  }
}

// Push an element onto the stack
// Returns 0 on success, -1 if the stack is full
int push(Stack_t *stack, uint8_t value) {
  if (!stack || stack->top >= MAX_STACK_SIZE)
    return -1; // Stack overflow

  stack->data[stack->top++] = value;
  return 0;
}

// Pop an element from the stack
// Returns the value if successful, or -1 if the stack is empty
int pop(Stack_t *stack) {
  if (!stack || stack->top == 0)
    return -1; // Stack underflow

  return stack->data[--stack->top];
}

// Simple test in main
int main() {
  Stack_t my_stack;
  init_stack(&my_stack);

  // Push values onto the stack
  for (uint8_t i = 1; i <= 5; ++i) {
    if (push(&my_stack, i) == 0)
      printf("Pushed: %d\n", i);
    else
      printf("Failed to push: %d\n", i);
  }

  // Pop all values
  int val;
  while ((val = pop(&my_stack)) != -1) {
    printf("Popped: %d\n", val);
  }

  return 0;
}



