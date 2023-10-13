#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double stack[100];
int stack_used;

int empty_stack(){
  if(stack_used == 0)return 1;
  return 0;
}

void init_stack(){
  stack_used = 0;
}

void push(double x){
  stack[stack_used++] = x;
}

double pop(){
  return stack[--stack_used];
}

double top(){
  return stack[stack_used-1];
}

void print_stack(){
  for(int i = 0; i < stack_used; i++){
    printf("%f,", stack[i]);
  }
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
  }

  printf("答え %f\n",top());
  return 0;
}