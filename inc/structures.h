#ifndef STRUCTURES_H
#	define STRUCTURES_H

typedef struct	s_tile
{
	int			x;
	int			y;
	char		content;
} 				t_tile;

typedef struct	s_board
{
	t_tile**	tiles;
	int			size;
}				t_board;

#endif