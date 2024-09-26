#include "monty.h"

/**
 * main - Entry point for the Monty interpreter.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
 */
int main(int argc, char **argv)
{
	my_monty(argv, argc);
	return (EXIT_SUCCESS);
}
