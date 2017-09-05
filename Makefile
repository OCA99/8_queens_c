default: create

create:
	gcc -Wall -Werror -Wextra -Iinc src/*.c

clean:
	rm *.out

re: clean create
