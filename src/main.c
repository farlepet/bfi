#include <options.h>
#include <stdlib.h>
#include <stdio.h>
#include <bf.h>

FILE  *input;
size_t inputlen;
char  *file;


int main(int argc, char **argv)
{
	printf("BFI v" VERSION "\n------------------\n");

	get_options(argc, argv);

	if((size_t)options[OPT_HELP].setting == 1) usage(0);

	if((size_t)options[OPT_INPUT_FILE].setting == 1)
	{
		printf("No input file specified.\n");
		usage(1);
	}

	if(!(input = fopen(options[OPT_INPUT_FILE].setting, "r")))
	{
		printf("Couldn't open specified input file.\n");
		usage(1);
	}

	fseek(input, 0, SEEK_END);
	size_t inputlen = ftell(input);
	fseek(input, 0, SEEK_SET);

	file = (char *)malloc(inputlen);
	fread(file, inputlen, 1, input);

	bf_interp(file, inputlen);

	free(file);

	return 0;
}