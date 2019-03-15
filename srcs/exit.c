/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:31:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 20:51:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_a *all)
{
	int		count;

	if (all)
	{
		count = -1;
		if (all->room)
			while (++count < all->nb_room)
			{
				free(all->room[count].name);
				free(all->room[count].tubes);
			}
		free(all->room);
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
