#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int debug = 1;//デバッグ用なら１

typedef struct list {
  double item;
  struct list *next;
} list;

list *stack;

void push(double x){
  list *p = malloc(sizeof(list));
  p->item = x;
  p->next = stack;
  stack = p;
}

double pop(){
  double x;
  list *next;
  if(stack == NULL){
    fprintf(stderr, "##### スタックが空になっています\n");
    return 0;
  }
  x = stack->item;
  next = stack->next;
  free(stack);
  stack = next;
  return x;
}

double top(){
  return stack->item;
}

void recursive_stack(list *stack){
  if(stack != NULL){
    printf("%f, ", stack->item);
    recursive_stack(stack->next);
  }
}

void print_stack(){
  printf("スタックの中身：");
  recursive_stack(stack);
  puts("");
}

void tokenize(char *tokens[], char *string, const char *separator, int *tokens_length){
  int count = 0;
  char *token = strtok(string, separator); 
  while (token != NULL) {
      tokens[count] = token;
      count++;
      token = strtok(NULL, separator); 
  }
  *tokens_length = count;
}

int main(int argc, char *argv[]){
  char *tokens[100];
  int count;
  tokenize(tokens, argv[1], " ", &count);

  for (int i = 0; i < count; i++) {
    double num1, num2, answer;
    if (strcmp(tokens[i], "+") == 0) {
      num1 = pop();
      num2 = pop();
      push(num1 + num2);
    } else if (strcmp(tokens[i], "-") == 0) {
      num1 = pop();
      num2 = pop();
      push(num2 - num1);
    } else if (strcmp(tokens[i], "*") == 0) {
      num1 = pop();
      num2 = pop();
      push(num1 * num2);
    } else if (strcmp(tokens[i], "/") == 0) {
      num1 = pop();
      num2 = pop();
      push(num2 / num1);
    } else if (strcmp(tokens[i], "sqrt") == 0) {
    num1 = pop();
    push(sqrt(num1));
    } else if (strcmp(tokens[i], "pow") == 0) {
    num1 = pop();
    num2 = pop();
    push(pow(num2, num1));
    } else {
      push(atof(tokens[i]));
    }
    if(debug)print_stack();
  }
  printf("答え %f\n",top());
  return 0;
}