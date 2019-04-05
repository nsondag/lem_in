/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:14:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/19 23:14:22 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		restore_initial_len(t_a *ant)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ant->nb_room)
	{
		j = -1;
		while (++j < ant->room[i].nb_tubes)
			ant->room[i].tubes[j].len = ant->room[i].tubes[j].tmp_len;
		ant->room[i].is_passed = -1;
	}
	return (VALID);
}

int		change_len(t_room *room, int start, int dest, int new_path_len)
{
	int		i;

	i = -1;
	while (++i < room[start].nb_tubes)
	{
		if (room[start].tubes[i].dest == dest)
		{
			room[start].tubes[i].len = new_path_len;
			return (1);
		}
	}
	return (0);
}

int		change_all_len(t_a *ant, t_room *room, t_path **path, int nb_path)
{
	int		i;

	ant->nb_path = nb_path;
	restore_initial_len(ant);
	while (--nb_path > -1)
	{
		i = -1;
		while (++i < path[nb_path]->len_path - 1)
		{
			if (i)
				room[path[nb_path]->chain[i]].is_passed = nb_path;
			change_len(room, path[nb_path]->chain[i],
					path[nb_path]->chain[i + 1], 2000000);
			change_len(room, path[nb_path]->chain[i + 1],
					path[nb_path]->chain[i], 0);
		}
	}
	return (0);
}
