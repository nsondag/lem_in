/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_mult_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:20:36 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 21:10:47 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		supp_chained(t_room *room, int index)
{
	if (room[index].nb_tubes == 2)
		index = supp_2comp_room(room, index);
	while (index > 1 && room[index].nb_tubes == 1)
		index = supp_1comp_room(room, index);
	return (0);
}

int		search_for_side(t_room *room, int index, int *direction, int *size)
{
	int		refer;

	refer = room[index].tubes[*direction].dest;
	if (refer < 2 || room[refer].nb_tubes != 2)
	{
		*direction = index;
		return (refer);
	}
	(*size)++;
	*direction = room[refer].tubes[0].dest == index;
	return (search_for_side(room, refer, direction, size));
}

int		search_for_deadend(t_room *room, int nb_room)
{
	int		i;

	i = 2;
	while (i < nb_room)
	{
		if (room[i].nb_tubes == 1)
			supp_chained(room, i);
		i++;
	}
	return (0);
}

int		search_for_mult_path2(t_a *all, int g[9])
{
	g[5] = 0;
	while (g[5] < all->room[g[2]].nb_tubes)
	{
		g[5] = all->room[g[2]].tubes[g[5]].dest;
		if (g[5] == g[3])
		{
			supp_chained(all->room, g[4]);
			return (search_for_mult_path(all, 2));
		}
		else if (g[5] != g[4] && all->room[g[5]].nb_tubes == 2)
		{
			g[7] = 1;
			g[8] = all->room[g[5]].tubes[0].dest == g[5];
			if (search_for_side(all->room, g[5], &(g[8]), &g[7]) == g[3])
			{
				supp_chained(all->room, g[1] < g[7] ? g[5] : g[4]);
				return (search_for_mult_path(all, 2));
			}
		}
		g[5]++;
	}
	return (search_for_mult_path(all, g[0] + 1));
}

/*
** i = g[0]
** size_of_path = g[1]
** first_side = g[2]
** second_side = g[3]
** room_first_side = g[4]
** j = g[5]
** k = g[6]
** tmp_path_size = g[7]
** l = g[8]
*/

int		search_for_mult_path(t_a *all, int start)
{
	int		g[9];

	g[0] = start;
	while (g[0] < all->nb_room && all->room[g[0]].nb_tubes != 2)
		g[0]++;
	if (g[0] == all->nb_room)
		return (NONE_LEFT);
	g[1] = 1;
	g[4] = 0;
	g[3] = search_for_side(all->room, g[0], &g[4], &g[1]);
	g[4] = 1;
	g[2] = search_for_side(all->room, g[0], &g[4], &g[1]);
	if (g[2] + g[3] == 1)
		return (search_for_mult_path(all, g[0] + 1));
	if (g[2] == g[3])
	{
		supp_chained(all->room, g[4]);
		return (search_for_mult_path(all, g[0] + 1));
	}
	return (search_for_mult_path2(all, g));
}
