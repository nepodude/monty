#include "monty.h"

/* External variable declared in my_monty.c */
extern char *arg_push;

/**
 * push_op - Pushes an element to the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The current line number in the bytecode file.
 */
void push_op(stack_t **stack, unsigned int line_number)
{
	int value;
	stack_t *new_node;

	/* Validate the argument */
	if (arg_push == NULL || (isdigit(arg_push[0]) == 0 && arg_push[0] != '-' && arg_push[0] != '+'))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	value = atoi(arg_push);

	new_node = (stack_t *)malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall_op - Prints all the values on the stack, starting from the top.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The current line number in the bytecode file.
 */
void pall_op(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;  /* Suppress unused variable warning */

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * free_stack - Frees all nodes in the stack.
 * @stack: Pointer to the top of the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *temp;

	while (stack != NULL)
	{
		temp = stack;
		stack = stack->next;
		free(temp);
	}
}
