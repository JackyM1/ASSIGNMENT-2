#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100
// Structure to represent stack
struct Stack {
    int top;
    char items[MAX_STACK_SIZE];
};
// Function to initialize stack
void initialize(struct Stack *s) {
    s->top = -1;
}
// Function to push element onto stack
void push(struct Stack *s, char c) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = c;
}
// Function to pop element from stack
char pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// Function to convert infix expression to postfix (RPN) expression
void infix_to_rpn(char *infix, char *rpn) {
    struct Stack operator_stack;
    initialize(&operator_stack);

    int i, j = 0;
    for (i = 0; infix[i]; i++) {
        if (isdigit(infix[i])) {
            rpn[j++] = infix[i];
        } else if (is_operator(infix[i])) {
            while (operator_stack.top != -1 &&
                   precedence(operator_stack.items[operator_stack.top]) >= precedence(infix[i])) {
                rpn[j++] = pop(&operator_stack);
            }
            push(&operator_stack, infix[i]);
        } else if (infix[i] == '(') {
            push(&operator_stack, infix[i]);
        } else if (infix[i] == ')') {
            while (operator_stack.top != -1 && operator_stack.items[operator_stack.top] != '(') {
                rpn[j++] = pop(&operator_stack);
            }
            if (operator_stack.top == -1) {
                printf("Mismatched parentheses\n");
                exit(EXIT_FAILURE);
            }
            pop(&operator_stack);
        }
    }

    while (operator_stack.top != -1) {
        if (operator_stack.items[operator_stack.top] == '(') {
            printf("Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        rpn[j++] = pop(&operator_stack);
    }
    rpn[j] = '\0';
}

int main() {
    char infix[100], rpn[100];
    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0'; // Removing newline character

    infix_to_rpn(infix, rpn);
    printf("Equivalent RPN expression: %s\n", rpn);

    return 0;
}
