#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct
{
        char *option;
        char *setting;
} option;

option options[2];

#define OPT_INPUT_FILE 0
#define OPT_JUMPFUCK   1

void get_options(int, char **);


#define VERSION "0.01"

#define USAGE	"bfi v" VERSION "USAGE:" \
				"    bfi -i [input]\n"

void usage(int);

#endif // OPTIONS_H