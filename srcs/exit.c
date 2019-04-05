/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:31:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/17 21:23:27 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_a *all)
{
	int		c[2];

	if (all && (c[0] = -1))
	{
		while (all->room && ++c[0] < all->nb_room)
		{
			free(all->room[c[0]].name);
			free(all->room[c[0]].tubes);
		}
		if ((c[0] = -1) &&
			(all->data = rea(all, all->data, NULL)))
			ft_free_tab((void***)&all->data);
		free(all->room);
		while (all->path && ++c[0] < all->nb_path && (c[1] = -1))
		{
			while (++c[1] <= c[0])
			{
				free(all->path[c[0]][c[1]]->chain);
				free(all->path[c[0]][c[1]]);
			}
			free(all->path[c[0]]);
		}
		free(all->path);
		free(all->nb_move);
	}
}

void	exit_func(int exit_code, t_a *all)
{
	if (exit_code == INVALID)
		write(1, "ERROR\n", 6);
	else if (exit_code == MERROR)
		write(1, "malloc error\n", 13);
	free_all(all);
	exit(exit_code >= 0 ? 0 : exit_code);
}
