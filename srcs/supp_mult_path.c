/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_mult_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:20:36 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/09 17:20:38 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		supp_room_from_other(int index_to_supp, t_room *other)
{
	int		i;

	i = 0;
	while (other->tubes[i].dest != index_to_supp)
		i++;
	other->nb_tubes--;
	other->tubes[i] = other->tubes[other->nb_tubes];
	return (0);
}

int		free_one_room(t_a *all, int index)
{
	free(all->room[index].tubes);
	free(all->room[index].name);
	bzero(&(all->room[index]), sizeof(t_room) * index);
	return (0);
}

int		supp_2comp_room(t_room *room, int index)
{
	int		to_return;

	if (room[room[index].tubes[0].dest].nb_tubes == 2)
		to_return = room[index].tubes[0].dest;
	else
		to_return = room[index].tubes[1].dest;
	supp_room_from_other(index, &(room[room[index].tubes[0].dest]));
	supp_room_from_other(index, &(room[room[index].tubes[1].dest]));
	room[index].nb_tubes = 0;
	return (to_return);
}

int		supp_1comp_room(t_room *room, int index)
{
	supp_room_from_other(index, &(room[room[index].tubes[0].dest]));
	room[index].nb_tubes = 0;
	return (room[index].tubes[0].dest);
}

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

int		search_for_mult_path(t_a *all, int start)
{
	int		i;
	int		size_of_path;
	int		first_side;
	int		second_side;
	int		room_first_side;
	int		j;
	int		k;
	int		tmp_path_size;
	int		l;

	i = start;
	while (i < all->nb_room && all->room[i].nb_tubes != 2)
		i++;
	if (i == all->nb_room)
		return (NONE_LEFT);
	size_of_path = 1;
	room_first_side = 0;
	second_side = search_for_side(all->room, i, &room_first_side, &size_of_path);
	room_first_side = 1;
	first_side = search_for_side(all->room, i, &room_first_side, &size_of_path);
	if (first_side + second_side == 1)
		return (search_for_mult_path(all, i + 1));
	if (first_side == second_side)
	{
		supp_chained(all->room, room_first_side);
		return (search_for_mult_path(all, i + 1));
	}
	j = 0;
	while (j < all->room[first_side].nb_tubes)
	{
		k = all->room[first_side].tubes[j].dest;
		if (k == second_side)
		{
			supp_chained(all->room, room_first_side);
			return (search_for_mult_path(all, 2));
		}
		else if (k != room_first_side && all->room[k].nb_tubes == 2)
		{
			tmp_path_size = 1;
			l = all->room[k].tubes[0].dest == j;
			if (search_for_side(all->room, k, &l, &tmp_path_size) == second_side)
			{
				supp_chained(all->room, size_of_path < tmp_path_size ? k : room_first_side);
				return (search_for_mult_path(all, 2));
			}
		}
		j++;
	}
	return (search_for_mult_path(all, i + 1));
}
