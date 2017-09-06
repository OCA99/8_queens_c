#include "headers.h"
#include "structures.h"
#include "shared.h"

int				solution_number;

t_board*		define_board(int x, int y, int s)
{
	t_board*	ret;
	int			i;
	int			j;

	ret = malloc(sizeof(t_board));
	ret->tiles = malloc(sizeof(t_tile*) * s);
	ret->size = s;
	i = 0;
	while (i < s)
	{
		ret->tiles[i] = malloc(sizeof(t_tile) * s);
		j = 0;
		while (j < s)
		{
			ret->tiles[i][j].x = j;
			ret->tiles[i][j].y = i;
			ret->tiles[i][j].content = ' ';
			j++;
		}
		i++;
	}
	ret->tiles[y][x].content = 'Q';

	return (ret);
}

void			update_board(t_board* board)
{
	int			i;
	int			j;
	int			k;
	int			o;
	int			s;

	s = board->size;
	i = 0;
	while (i < s)
	{
		j = 0;
		while (j < s)
		{
			if (board->tiles[i][j].content == 'X')
				board->tiles[i][j].content = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while (i < s)
	{
		j = 0;
		while (j < s)
		{
			if (board->tiles[i][j].content == 'Q')
			{
				k = 0;
				while (k < s)
				{
					o = 0;
					while (o < s)
					{
						if (i == k && j != o)
						{
							board->tiles[k][o].content = 'X';
						}
						else if (j == o && i != k)
						{
							board->tiles[k][o].content = 'X';
						}
						else if (abs(i - k) == abs(j - o) && i - k != 0)
						{
							board->tiles[k][o].content = 'X';
						}
						o++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

void			print_board(t_board* board)
{
	int			s;
	int			i;
	int			j;
	int			k;

	s = board->size;
	i = 0;
	while (i < s * 2 + 1 + (s * 2) + 2)
	{
		printf("-");
		i++;
	}
	printf("\nSolution number %d\n", solution_number);
	i = 0;
	while (i < s * 2 + 1 + (s * 2) + 2)
	{
		printf("-");
		i++;
	}
	printf("\n  ");
	i = 0;
	while (i < s * 2 + 1 + (s * 2))
	{
		printf("-");
		i++;
	}
	printf("\n");
	i = 0;
	while (i < s)
	{
		printf("%d | ", i + 1);
		j = 0;
		while (j < s)
		{
			if (board->tiles[i][j].content == 'Q')
				printf("Q");
			else
				printf(" ");
			if (j != s - 1)
				printf(" | ");			
			j++;
		}
		printf(" |\n  ");
		j = 0;
		while (j < s * 2 + 1 + (s * 2))
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("  ");
	i = 0;
	k = 0;
	while (i < s * 2 + 1 + (s * 2))
	{
		if ((i - 2) % 4 == 0)
		{
			printf("%c", k + 65);
			k++;
		}
		else
		{
			printf(" ");
		}
		i++;
	}
	printf("\n\n");
}

int				place_queen(t_board* board, int d, int i)
{
	int			s;
	int			j;

	s = board->size;
	if (d == s)
	{
		solution_number++;
		print_board(board);
		return (1);
	}
	while (i < s)
	{
		j = 0;
		while (j < s)
		{
			if (board->tiles[i][j].content == ' ')
			{
				board->tiles[i][j].content = 'Q';
				update_board(board);
				place_queen(board, d + 1, i + 1);
				board->tiles[i][j].content = ' ';
				update_board(board);
			}
			j++;
		}
		i++;
	}

	return (0);
}

int 			main(int argc, char **argv)
{
	t_board*	board;
	clock_t		start;
	clock_t		end;
	double		cpu_time;

	start = clock();
	solution_number = 0;
	if (atoi(argv[3]) < 4)
	{
		printf("This case has no solution.\n");
		return (0);
	}
	if (atoi(argv[1]) - 1 < 0 || atoi(argv[1]) - 1 > atoi(argv[3]) - 1)
	{
		printf("Invalid input.\n");
		return (0);
	}
	if (atoi(argv[2]) - 1 < 0 || atoi(argv[2]) - 1 > atoi(argv[3]) - 1)
	{
		printf("Invalid input.\n");
		return (0);
	}
	board = define_board(atoi(argv[1]) - 1, atoi(argv[2]) - 1, atoi(argv[3]));
	update_board(board);
	place_queen(board, 1, 0);
	if (solution_number == 0)
	{
		printf("This case has no solution.\n");
		return (0);
	}
	printf("Total # of solutions: %d\n", solution_number);
	end = clock();
	cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time elapsed: %lf\n", cpu_time);

	return (0);
}