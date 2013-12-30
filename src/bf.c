#include <options.h>
#include <stdlib.h>
#include <stdio.h>
#include <bf.h>

#define MAX_DATA 0x8000
#define MAX_JUMP 0x1000

unsigned char *data;
size_t        *jump; // Used for JumpFuck
unsigned char  stor; // Storage, used for Extended Brainfuck

void bf_interp(char *file, size_t len)
{
	size_t ptr_pos;
	int tmp;
	size_t tmp_pos;
	int jumped;

	int jf   = ((size_t)options[OPT_JUMPFUCK].setting)   == 1;
	int ebf  = ((size_t)options[OPT_EXTBRAINI].setting)  == 1;

	data = (unsigned char *)malloc(MAX_DATA * sizeof(unsigned char));
	if(jf) jump = (size_t *)malloc(MAX_JUMP * sizeof(size_t));

	size_t i = 0;
	while(i < len)
	{
		if(jumped) jumped--;
		switch(file[i])
		{
			case '>':	if(ptr_pos >= (MAX_DATA - 1)) ptr_pos = 0;
						else                          ptr_pos++;
						i++;
						continue;

			case '<':	if(ptr_pos == 0) ptr_pos = MAX_DATA - 1;
						else             ptr_pos--;
						i++;
						continue;

			case '+':	data[ptr_pos]++;
						i++;
						continue;

			case '-':	data[ptr_pos]--;
						i++;
						continue;

			case '.':	putchar(data[ptr_pos]);
						i++;
						continue;

			case ',':	data[ptr_pos] = getchar();
						i++;
						continue;

			case '[':   if(!data[ptr_pos])
						{
							tmp = 0; // "level"
							tmp_pos = i;
							while(file[tmp_pos] != ']' || tmp > 1)
							{
								if(tmp_pos >= len)
								{
									printf("No ending ']' after '[' at character %zu\n", i);
									return;
								}
								if(file[tmp_pos] == '[') tmp++;
								if(file[tmp_pos] == ']') tmp--;
								tmp_pos++;
							}
							i = tmp_pos + 1; // Get past ']'
						}
						else i++;
						continue;

			case ']':	tmp = 0; // "level"
						tmp_pos = i;
						while(file[tmp_pos] != '[' || tmp > 1)
						{
							if(tmp_pos <= 0)
							{
								printf("No matching '[' for ']' at character %zu\n", i);
								return;
							}
							if(file[tmp_pos] == ']') tmp++;
							if(file[tmp_pos] == '[') tmp--;
							tmp_pos--;
						}
						i = tmp_pos;
						continue;

		// JumpFuck only (And extended brainfuck Type I for &):
			case '&':	if(!jf)
						{
							if(ebf) data[ptr_pos] &= stor;
							i++;
							continue; 
						}
						if(jumped) data[ptr_pos] = data[(ptr_pos + 1) % MAX_DATA];
						else       data[ptr_pos] = 0;
						jump[data[ptr_pos]] = i;
						i++;
						continue;

			case '%':	if(!jf) { i++; continue; }
						jumped = 2;
						i = jump[data[ptr_pos]];
						continue;

		// Extended Brainfuck Type I only:
			case '@':	if(!ebf) { i++; continue; }
						return; // End of program

			case '$':	if(!ebf) { i++; continue; }
						stor = data[ptr_pos];
						i++;
						continue;

			case '!':	if(!ebf) { i++; continue; }
						data[ptr_pos] = stor;
						i++;
						continue;

			case '}':	if(!ebf) { i++; continue; }
						data[ptr_pos] >>= 1;
						i++;
						continue;

			case '{':	if(!ebf) { i++; continue; }
						data[ptr_pos] <<= 1;
						i++;
						continue;

			case '~':	if(!ebf) { i++; continue; }
						data[ptr_pos] = ~data[ptr_pos];
						i++;
						continue;

			case '^':	if(!ebf) { i++; continue; }
						data[ptr_pos] ^= stor;
						i++;
						continue;

			case '|':	if(!ebf) { i++; continue; }
						data[ptr_pos] |= stor;
						i++;
						continue;


			default:	i++;
						continue;
		}
	}
}