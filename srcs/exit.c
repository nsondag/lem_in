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
	int		count;
	int		c2;

	if (all)
	{
		count = -1;
		if (all->room)
			while (++count < all->nb_room)
			{
				free(all->room[count].name);
				free(all->room[count].tubes);
			}
		all->data = rea(all, all->data, NULL);
		if (all->data)
			ft_free_tab((void***)&all->data);
		free(all->room);
		count = -1;
		if (all->path)
		{
			while (++count < all->nb_path && (c2 = -1))
			{
				while (++c2 <= count)
				{
					free(all->path[count][c2]->chain);
					free(all->path[count][c2]);
				}
				free(all->path[count]);
			}
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
