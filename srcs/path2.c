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
#include  <stdio.h>

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

int		path(t_room *room, t_path *curr, int i)
{
	int		j;

	if (!(curr->chain))
	{
		ft_printf("len_path %d\n", i+1);
		if (!(curr->chain = malloc(sizeof(int) * (i + 1))))
			return (MERROR);
		curr->len_path = i + 1;
		curr->chain[0] = 0;
		i = 0;
	}
	if (curr->chain[i] == 1)
		return (curr->len_path = i + 1);
	if (i >= curr->len_path)
		return (0);
	j = -1;
	while (++j < room[curr->chain[i]].nb_tubes)
	{
		if (room[curr->chain[i]].tubes[j].tree)
		{
			curr->chain[i + 1] = room[curr->chain[i]].tubes[j].dest;
			if (path(room, curr, i + 1))
				return (1);
		}
	}
	return (0);
}

t_path	*duplicate(t_path *dup, t_room *room)
{
	t_path	*new_path;
	int		i;

	if (!(new_path = malloc(sizeof(t_path))))
		return (NULL);
	if (!(new_path->chain = malloc(sizeof(int) * dup->len_path)))
	{
		free(new_path);
		return (NULL);
	}
	i = -1;
	while (++i < dup->len_path)
		room[dup->chain[i]].is_passed = -1;
	ft_memcpy(new_path->chain, dup->chain, sizeof(int) * dup->len_path);
	new_path->len_path = dup->len_path;
	new_path->nb_ant_in_path = 0;
	return (new_path);
}

t_path	**start_searching(t_a *ant, t_path **previous, int i)
{
	t_path	**tab;
	int		j;
	int		ret;

	if (!(tab = malloc(sizeof(t_path*) * (i + 2))))
		return (NULL);
	ft_printf("tab created\n");
	if (previous)
	{
		j = -1;
		while (++j < i)
			tab[j] = duplicate(previous[j], ant->room);
	}
	ft_printf("previous copied\n");
	tab[i + 1] = NULL;
	if (!(tab[i] = ft_memalloc(sizeof(t_path))))
	{
		free(tab);
		return (NULL);
	}
	ft_printf("new path allocated\n");
	if ((ret = path(ant->room, tab[i], ant->escape)) == 0) //a changer
	{
		ft_printf("path not found\n");
		return (NULL);
	}
	ft_printf("path found\n");
	return (tab);
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

	restore_initial_len(ant);
	while (--nb_path > -1)
	{
		i = -1;
		while (++i < path[nb_path]->len_path - 1)
		{
			if (i)
				room[path[nb_path]->chain[i]].is_passed = nb_path;
			change_len(room, path[nb_path]->chain[i], path[nb_path]->chain[i + 1], 2000000);
			change_len(room, path[nb_path]->chain[i + 1], path[nb_path]->chain[i], 0);
		}
	}
	return (0);
}

