/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:50:37 by hvromman          #+#    #+#             */
/*   Updated: 2019/02/12 01:50:38 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		modify_tubes_first(t_a *ant)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ant->nb_room)
	{
		j = -1;
		while (++j < ant->room[i].nb_tubes)
		{
			ant->room[i].tubes[j].tmp_len = ant->room[i].tubes[j].len +
			ant->room[i].dist - ant->room[ant->room[i].tubes[j].dest].dist;
		}
	}
	return (VALID);
}

int		path(t_room *room, t_path *current, int i)
{
	int		j;

	if (!current->chain)
	{
		if (!(current->chain = malloc(i + 1)))
			return (MERROR);
		current->chain[0] = 0;
		i = 0;
	}
	if (current->chain[i] == 1)
		return (1);
	j = -1;
	while (++j < room[current->chain[i]].nb_tubes)
	{
		if (room[current->chain[i]].tubes[j].tree)
		{
			current->chain[i + 1] = room[current->chain[i]].tubes[j].dest;
			if (path(room, current, i + 1))
				return (1);
		}
	}
	return (0);
}

t_path	*duplicate(t_path *dup)
{
	t_path	*new;

	if (!(new = malloc(sizeof(t_path))))
		return (NULL);
	if (!(new->chain = malloc(sizeof(int) * dup->len_path)))
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->chain, dup->chain, dup->len_path);
	new->len_path = dup->len_path;
	new->nb_ant_in_path = 0;
	return (new);
}

t_path	**start_searching(t_a *ant, t_path **previous, int i)
{
	t_path	**tab;
	int		j;
	int		ret;

	if (!(tab = malloc(sizeof(t_path*) * (i + 2))))
		return (NULL);
	if (previous)
	{
		j = -1;
		while (++j < i)
			tab[j] = duplicate(previous[j]);
	}
	tab[i + 1] = NULL;
	if (!(tab[i] = ft_memalloc(sizeof(t_path))))
	{
		free(tab);
		return (NULL);
	}
	if ((ret = path(ant->room, tab[i], ant->room[1].dist)) == 0)
	{
		free(tab[i]->chain);
		free(tab[i]);
		free(tab);
		return (NULL);
	}
	tab[i]->len_path = ant->room[1].dist;
	ft_memcpy(tab[i]->chain, tab[i]->chain + 1, tab[i]->len_path * sizeof(int));
	return (tab);
}
