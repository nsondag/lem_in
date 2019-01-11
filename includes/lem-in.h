/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:15:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/10 14:31:47 by nsondag          ###   ########.fr       */
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

typedef	struct	s_adj
{
	int		dist;
	int		dist2;
	int		len_tab;
	char	*name;
	int		*tab;
	char	is_passed;
}				t_adj;

typedef struct	s_a
{
	int		nb_ant;
	int		tab_size;
	t_adj	*adj;
	char	*buf;
	int		start_room;
	int		**path;
	int		*len_path;
	int		nb_path;
}				t_a;

typedef struct	s_var
{
	int		is_start;
	int		is_end;
	int		ret;
}				t_var;

typedef struct	s_path
{
	int		i;
	int		j;
}				t_path;

int		read_comment(char *line);
int		read_room(t_a *all);
void	exit_func(int exit_code, t_a *all);
void	free_all(t_a *all);
int		parse(t_a *ant);
int		smallest(t_a *ant);
int		smallest2(t_a *ant);
int		dead_ends(t_a *ant);

int		supp_room_from_other(int index_to_supp, t_adj *other);
int		free_one_room(t_a *all, int index);
int		search_for_mult_path(t_a *all, int start);
int		search_for_deadend(t_adj *adj, int tab_size);


#endif
