#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

int stack[STACK_SIZE];
int top = -1; // Initialize the stack pointer to -1 (empty stack)

void push(int value) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "L%d: can't push, stack overflow\n", line_number);
        exit(EXIT_FAILURE);
    }
    top++;
    stack[top] = value;
}

void pall() {
    int i;
    for (i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;

        char *opcode = strtok(line, " \n");
        if (opcode == NULL) {
            continue; // Empty line, skip it
        }

        if (strcmp(opcode, "push") == 0) {
            char *arg = strtok(NULL, " \n");
            if (arg == NULL) {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                return EXIT_FAILURE;
            }

            int value = atoi(arg);
            push(value);
        } else if (strcmp(opcode, "pall") == 0) {
            pall();
        } else {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
