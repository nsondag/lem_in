/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:15:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 20:02:15 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

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
	int		index;
	char	*name;
	int		*tab;
}				t_adj;

typedef struct	s_a
{
	int		nb_ant;
	int		tab_size;
	t_adj	*adj;
	char	*buf;
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

#endif
