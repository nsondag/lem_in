/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_mult_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 17:20:36 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 21:10:46 by nsondag          ###   ########.fr       */
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
