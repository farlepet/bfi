#include <options.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

option options[4] = 
{
	{"-i", (char *)1}, // Input file
	{"-h", (char *)0}, // Print help
	{"-j", (char *)0}, // Enable JumpFuck
	{"-x", (char *)0}, // Extended Brainfuck Type I
};
#define N_OPTS (int)(sizeof(options) / sizeof(options[0]))

void get_options(int argc, char **argv)
{
	int i, j;
	for(i = 1; i < argc; i++) //i = 1: to skip the executable's name
	{
		for(j = 0; j < N_OPTS; j++)
		{
			if(!strcmp(options[j].option, argv[i]))
			{
				if(options[j].setting != 0)
					options[j].setting = argv[++i]; // Some free optimization: add I so it doesn't put the setting through the loop!
				else
					options[j].setting = (char *)1; //do not set as the next argument, this is JUST a flag
				break;
			}
			if(j == (N_OPTS - 1))
			{
				printf("Unknown option: %s\n", argv[i]);
				usage(0);
			}
		}
	}
}


void usage(int retval)
{
	printf(USAGE);
	exit(retval);
}