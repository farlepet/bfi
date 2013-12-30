#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct
{
        char *option;
        char *setting;
} option;

option options[4];

#define OPT_INPUT_FILE 0
#define OPT_HELP       1
#define OPT_JUMPFUCK   2
#define OPT_EXTBRAINI  3

void get_options(int, char **);


#define VERSION "1.00"

#define USAGE	"bfi v" VERSION " USAGE:\n"                \
				"    bfi -i [input] [-j -x]\n"            \
				"      -j: Enable JumpFuck\n"             \
				"      -x: Enable Extended Brainfuck\n"

void usage(int);

#endif // OPTIONS_H