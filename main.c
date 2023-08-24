#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 1024

/* Define the stack structure */
typedef struct Stack {
    int data[STACK_SIZE];
    int top;
} Stack;

/* Initialize a new stack */
void initStack(Stack *stack) {
    stack->top = -1;
}

/* Push an element onto the stack */
void push(Stack *stack, int value) {
    if (stack->top < STACK_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

/* Pop an element from the stack */
int pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

/* Main interpreter function */
void interpret(FILE *file) {
    char line[256]; // Adjust the buffer size as needed
    Stack stack;
    initStack(&stack);

    int line_number = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        // Tokenize the line into opcode and argument
        char *opcode = strtok(line, " \n");
        char *argument = strtok(NULL, " \n");

        if (opcode == NULL)
            continue; // Blank line

        // Implement Monty instructions
        if (strcmp(opcode, "push") == 0) {
            if (argument == NULL) {
                fprintf(stderr, "Error: Missing argument for push on line %d\n", line_number);
                exit(EXIT_FAILURE);
            }
            int value = atoi(argument);
            push(&stack, value);
        } else if (strcmp(opcode, "pop") == 0) {
            pop(&stack);
        } else if (strcmp(opcode, "pall") == 0) {
            // Print the entire stack
            for (int i = 0; i <= stack.top; i++) {
                printf("%d\n", stack.data[i]);
            }
        } else {
            fprintf(stderr, "Error: Unknown instruction %s on line %d\n", opcode, line_number);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    interpret(file);
    fclose(file);
    return EXIT_SUCCESS;
}

