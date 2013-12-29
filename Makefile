MAINDIR    = $(CURDIR)
SRC        = $(MAINDIR)/src
INC        = $(MAINDIR)/inc

OUT        = $(MAINDIR)/bfi
INSTALL    = /usr/bin/$(OUT)

SRCS       = $(wildcard $(SRC)/*.c)
OBJS       = $(patsubst %.c,%.o,$(SRCS))

CC         = gcc

CFLAGS     = -I$(INC) -Wall -Wextra -Werror


link:   $(OBJS)
	@echo -e "\033[33m  \033[1mLinking sources\033[0m"
	@$(CC) -o $(OUT) $(OBJS)


%.o: %.c
	@echo -e "\033[32m  \033[1mCC\033[21m    \033[34m$<\033[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<


clean:
	@echo -e "\033[33m  \033[1mCleaning sources\033[0m"
	@rm -f $(OBJS)
	@rm -f $(OUT)

install:
	@echo -e "\033[33m  \033[1mInstalling executable\033[0m"
	@cp $(OUT) $(INSTALL)