#include <stdio.h>
#include <stdlib.h>

struct digit {
  int value;
  struct digit * prev, * next;
};
struct digit* new_digit() {
  struct digit* new_digit = (struct digit *)malloc(sizeof(struct digit));
  new_digit->value = 0;
  new_digit->prev = NULL;
  new_digit->next = NULL;
  return new_digit;
}

struct list {
  struct digit *HEAD;
  struct digit *TAIL;
};
struct list* new_list() {
  struct list* new_list = (struct list *)malloc(sizeof(struct list));
  new_list->HEAD = NULL;
  new_list->TAIL = NULL;
  return new_list;
}

void print_rev(struct list *list1) {
  struct digit *current_digit = list1->HEAD;
  printf("Printing number\n");
  while (current_digit != NULL) {
    printf("%d", current_digit->value);
    current_digit = current_digit->next;
  }
  printf("\n");
}

void print(struct list *list1, char end) {
  struct digit *current_digit = list1->TAIL;
  while (current_digit != NULL) {
    printf("%d", current_digit->value);
    current_digit = current_digit->prev;
  }
  printf("%c", end);
}

void insert(struct list *num1, int digit) {
  // printf("num1->HEAD=%p\n",num1->HEAD);
  if (num1->HEAD == NULL) {
    if (digit == 0)
      return;
    num1->HEAD = new_digit();
    num1->HEAD->value = digit;
    num1->TAIL = num1->HEAD;
  } else {
    struct digit *digit_node = new_digit();
    digit_node->value = digit;
    digit_node->next = num1->HEAD;
    num1->HEAD->prev = digit_node;
    num1->HEAD = digit_node;
  }
}

void insert_back(struct list* num, int digit) {
  if (num->TAIL == NULL) {
    num->TAIL = new_digit();
    num->TAIL->value = digit;
    num->HEAD = num->TAIL;
  } else {
    struct digit* digit_node = new_digit();
    digit_node->value = digit;
    digit_node->prev = num->TAIL;
    num->TAIL->next = digit_node;
    num->TAIL = digit_node;
  }
}

struct list* add(struct list* list1, struct list* list2) {
  // The list stores LSD in HEAD. So, we add from head and move carry to next node.
  struct list* result = new_list();
  int carry = 0;
  struct digit* list1_digit = list1->HEAD;
  struct digit* list2_digit = list2->HEAD;
  int A, B;
  while (list1_digit != NULL || list2_digit != NULL) {
    if (list1_digit == NULL)
      A = 0;
    else {
      A = list1_digit->value;
      list1_digit = list1_digit->next;
    }
    if (list2_digit == NULL)
      B = 0;
    else {
      B = list2_digit->value;
      list2_digit = list2_digit->next;
    }
    insert_back(result, (A + B + carry) % 10);
    carry = (A + B + carry) / 10;
  }
  if (carry == 1)
    insert_back(result, 1);
  return result;
}

void free_memory(struct list *num) {
  if (num->HEAD == NULL) {
    if (num != NULL) {
      free(num); /**< Don't return without freeing the root node first */
      num = NULL;
    }
    return;
  }
  struct digit *current_digit = num->HEAD;
  struct digit *next_digit;
  while (current_digit != NULL) {
    next_digit = current_digit->next;
    free(current_digit);
    current_digit = next_digit;
  }

  if (num != NULL) {
    free(num); /**< Always try to free the root node */
    num = NULL;
  }
}

static inline void reset(struct list *sum, struct list *a, struct list *b) {
  free_memory(sum);
  free_memory(a);
  free_memory(b);
}

int main(void) {
  int state = 1;
  struct list *num1 = new_list(), *num2 = new_list();
  int digit;
  while ((digit = fgetc(stdin)) != EOF) {
    if (digit == '\n') {
      // Output the sum here.
      // Your code here.
      struct list *sum = add(num1, num2);
      print(sum, '\n');
      reset(sum, num1, num2);
      num1 = new_list(); /**< Remember to deallocate on exit */
      num2 = new_list();
      state = 1;
    } else if (digit == ' ') {
      state = 2;
      // Your code here.
    } else {
      if (digit >= '0' && digit <= '9') { // Negative numbers are ignored.
        if (state == 1) {
          // Insert in first number
          insert(num1, digit - '0');
        } else {
          insert(num2, digit - '0');
        }
        // Your code here.
      }
    }
  }

  if (num1 != NULL) {
    free(num1);
    num1 = NULL;
  }

  if (num2 != NULL) {
    free(num2);
    num2 = NULL;
  }

  return EXIT_SUCCESS;
}
