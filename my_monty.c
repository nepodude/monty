#include "monty.h"

/* Global variable to store the argument for push */
char *arg_push = NULL;

/**
 * my_monty - Runs Monty bytecode file commands in order.
 * @argv: Arguments from the command line.
 * @args: Number of command line arguments.
 */
void my_monty(char **argv, int args)
{
	FILE *file;
	char line[1024];
	stack_t *stack = NULL;
	unsigned int line_number = 0;
	char *opcode;
	instruction_t instructions[] = {
		{"push", push_op},
		{"pall", pall_op},
		{NULL, NULL}
	};
	int i;

	if (args != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;

		/* Remove newline character */
		line[strcspn(line, "\n")] = '\0';

		/* Skip empty lines */
		if (line[0] == '\0')
			continue;

		/* Tokenize the line to get opcode and argument */
		opcode = strtok(line, " \t\n");
		if (opcode == NULL || opcode[0] == '#') /* Skip comments and empty tokens */
			continue;

		/* If opcode is push, get the next argument */
		if (strcmp(opcode, "push") == 0)
		{
			arg_push = strtok(NULL, " \t\n");
		}
		else
		{
			arg_push = NULL;
		}

		/* Iterate through the instructions to find a match */
		for (i = 0; instructions[i].opcode != NULL; i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].f(&stack, line_number);
				break;
			}
		}

		/* If no instruction matched */
		if (instructions[i].opcode == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free_stack(stack);
			fclose(file);
			exit(EXIT_FAILURE);
		}
	}

	free_stack(stack);
	fclose(file);
}
