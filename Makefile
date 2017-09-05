default: create

create:
	gcc -Wall -Iinc src/*.c

clean:
	rm *.out

re: clean create
