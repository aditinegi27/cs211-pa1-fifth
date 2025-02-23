CC=gcc
CFLAG = -fsanitize=address,undefined -Og -g -Wall -Werror -std=c11

fifth: fifth.c 
	$(CC) -o fifth fifth.c $(CFLAG)
clean: fifth 
	rm -f fifth
