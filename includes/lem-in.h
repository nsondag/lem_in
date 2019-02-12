/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:15:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/02/12 16:29:20 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define REALLOC_SIZE 100
# define NONE_LEFT 6
# define ENDPROG 5
# define ENDFUNCTION 4
# define START 3
# define END 2
# define COMMENT 1
# define VALID 0
# define INVALID -1
# define MERROR -2

typedef	struct	s_tube
{
	int		len;
	int		dest;
}				t_tube;

typedef	struct	s_room
{
	int		dist;
	int		previous;
	int		nb_tubes;
	char	*name;
	t_tube	*tubes;
	int		is_passed;
}				t_room;

typedef	struct	s_path
{
	int		*chain;
	int		len_path;
	int		nb_ant_in_path;
}				t_path;

typedef struct	s_a
{
	int		nb_ant;
	int		nb_room;
	t_room	*room;
	int		start_room;
	char	*buf;
	int		nb_path;
	t_path	*path;
}				t_a;

typedef struct	s_var
{
	int		is_start;
	int		is_end;
	int		ret;
}				t_var;

int		read_comment(char *line);
int		read_room(t_a *all);
void	exit_func(int exit_code, t_a *all);
void	free_all(t_a *all);
int		parse(t_a *ant);
int		smallest(t_a *ant);
int		smallest2(t_a *ant);
int		dead_ends(t_a *ant);

int		supp_room_from_other(int index_to_supp, t_room *other);
int		free_one_room(t_a *all, int index);
int		search_for_mult_path(t_a *all, int start);
int		search_for_deadend(t_room *adj, int tab_size);
int		path(t_a *ant);
int		sending_ants(t_a *ants, int max_path);
int		racc_path2(t_a *ant, int **path);

#endif
