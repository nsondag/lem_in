/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:46:14 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/11 16:26:28 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		chained_path(t_a *ant, int  i, int j)
{
	int		next;

	next = -1;
	while (ant->path[i][j] > 1 && ant->adj[ant->path[i][j]].len_tab == 2)
	{
		if (next != -1)
			ant->adj[next].is_passed = i;
		if (ant->adj[ant->path[i][j]].tab[0] == ant->start_room)
			next = ant->adj[ant->path[i][j]].tab[1];
		else if (ant->adj[ant->path[i][j]].tab[1] == ant->start_room)
			next = ant->adj[ant->path[i][j]].tab[0];
		else
			next = ant->adj[ant->adj[ant->path[i][j]].tab[0]].dist2 < ant->adj[ant->adj[ant->path[i][j]].tab[1]].dist2 ? ant->adj[ant->path[i][j]].tab[0] : ant->adj[ant->path[i][j]].tab[1];
		ant->path[i][++j] = next;
		ft_printf("path %d next %d\n", ant->path[i][0], next);
		ant->len_path[i]++;
	}
	return (next);
}

int		search_path(t_a *ant, int **path)
{
	int		i;
	int		j;
	int		min;
	int		found;
	int		last_index;
	int		next_index;

	found = 1;
	while (found)
	{
		found = 0;
		i = -1;
		while (++i < ant->nb_path)
		{
			last_index = path[i][ant->len_path[i]];
//			ft_printf("i %d last_index %d\n", i , last_index);
			if (last_index == !(ant->start_room))
				continue;
			min = -1;
			j = -1;
			while (++j < ant->adj[last_index].len_tab)
			{
				next_index = ant->adj[last_index].tab[j];
				if (ant->adj[next_index].is_passed == -1)
					if (min == -1 || ant->adj[min].dist2 > ant->adj[next_index].dist2)
						min = next_index;
			}
//			ft_printf("i %d min %d\n", last_index, min);
			if (min == -1)
			{
				if (ant->len_path[i])
					ant->len_path[i]--;
//				ft_printf("victim\n");
			}
			else
			{
				ant->len_path[i]++;
				path[i][ant->len_path[i]] = min;
//				ft_printf("%d %d %d\n", path[i][0], last_index, path[i][ant->len_path[i]]);
				found = 1;
				if (min != !(ant->start_room))
					ant->adj[min].is_passed = i;
			}
		}
	}
	return (VALID);
}

int		calc_used_path(t_a *ant)
{
	int nb_ant;
	int sum_diff;
	int max;
	int max_index;
	int l;

	nb_ant = ant->nb_ant;
	while (nb_ant > 0)
	{
		sum_diff = 0;
		max = 0;
		max_index = -1;
		l = -1;
		while (++l < ant->nb_path)
		{
			if (ant->is_used[l])
			{
				if (ant->len_path[l] > max)
				{
					max_index = l;
					max = ant->len_path[l];
				}
			}
		}
		l = -1;
		while (++l < ant->nb_path)
		{
			if (ant->is_used[l] && l != max_index)
			{
				sum_diff += max - ant->len_path[l];
			}
		}
		if (nb_ant <= sum_diff)
			ant->is_used[max_index] = 0;
		else
			break ;
	}
	return (0);
}

int		clean_room(t_a *ant, int **path)
{
	int		i;
	int		j;

	if (!(ant->nb_ant_per_path = ft_memalloc(sizeof(int) * ant->nb_path)))
		return (MERROR);
	if (!(ant->is_used = ft_memalloc(sizeof(int) * ant->nb_path)))
		return (MERROR);
	i = -1;
	while (++i < ant->tab_size)
		ant->adj[i].is_passed = -1;
	ant->adj[0].is_passed = -2;
	ant->adj[1].is_passed = -2;
	i = -1;
	while (++i < ant->nb_path)
		if (path[i][ant->len_path[i]] == !(ant->start_room))
		{
			j = -1;
			ant->is_used[i] = 1;
			ant->len_path[i]++;
		}
	calc_used_path(ant);
	i = -1;
	while (++i < ant->nb_path)
		if (ant->is_used[i])
		{
			j = -1;
			while (++j < ant->len_path[i] - 1)
				ant->adj[path[i][j]].is_passed = i;
			ft_printf ("path used : %d\n", i);
		}
	return (VALID);
}

int		racc_path2(t_a *ant, int **path)
{
	int		offset;
	int		len;
	int		i;
	int		adj_first;
	int		adj_second;

	len = 3;
	i = -1;
	while (++i < ant->nb_path)
	{
		offset = -1;
		if (ant->is_used[i])
		while (++offset + len < ant->len_path[i])
		{
			adj_first = -1;
			while (++adj_first < ant->adj[path[i][offset]].len_tab)
			{
				adj_second = -1;
				if (ant->adj[adj_first].is_passed == -1)
				while (++adj_second < ant->adj[ant->adj[path[i][offset]].tab[adj_first]].len_tab)
				{
					if (ant->adj[ant->adj[path[i][offset]].tab[adj_first]].tab[adj_second] == path[i][offset + len])
					{
						ft_printf("3 to 2 : path %d offset %d start %d end %d inter %d\n", i, offset, path[i][offset], path[i][offset + len], adj_first);
					}
				}
			}
		}
	}
	return (0);
}

int		path(t_a *ant)
{
	int		i;

	if (!(ant->path = malloc(sizeof(int*) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	if (!(ant->len_path = ft_memalloc(sizeof(int) * ant->adj[ant->start_room].len_tab)))
		return (MERROR);
	i = 0;
	ant->adj[ant->start_room].is_passed = -2;
	ant->adj[!(ant->start_room)].is_passed = -1;
	while (i < ant->adj[ant->start_room].len_tab)
	{
		if (!(ant->path[i] = malloc(sizeof(int) * ant->adj[ant->start_room].dist2 * 100))) // a modifier
			return (MERROR);
		ant->path[i][ant->len_path[i]] = ant->adj[ant->start_room].tab[i];
		ant->adj[ant->adj[ant->start_room].tab[i]].is_passed = i;
		int ret = chained_path(ant, i, ant->len_path[i]);
		if (ret != !(ant->start_room))
			ant->adj[ret].is_passed = i;
		ant->nb_path++;
		i++;
	}
	search_path(ant, ant->path);
	clean_room(ant, ant->path);
	return (VALID);
}
