#include <options.h>
#include <stdio.h>
#include <bf.h>

char data[0x8000]; // I think 32 KiB is enough for most BF programs...

void bf_interp(char *file, size_t len)
{
	int ptr_pos;
	int tmp;
	size_t tmp_pos;

	size_t i = 0;
	while(i < len)
	{
		switch(file[i])
		{
			case '>':	ptr_pos++;
						i++;
						continue;

			case '<':	ptr_pos--;
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

			default:	i++;
						continue;
		}
	}
}