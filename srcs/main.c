/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/10 14:32:34 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <time.h>

int		main()
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	read_room(&ant);
	if (!(ant.adj) || !(ant.adj + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	if ((ret = parse(&ant)))
		exit_func(ret, &ant);
	//ft_printf("nb_ant %d\n", ant.nb_ant);
	search_for_deadend(ant.adj, ant.tab_size);
	search_for_mult_path(&ant, 2);
	ant.start_room = ant.adj[0].len_tab > ant.adj[1].len_tab ? 1 : 0;
	clock_t i = clock();
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	if (smallest2(&ant))
		exit_func(INVALID, &ant);
	clock_t j = clock();
	ft_printf("ici %f\n", ((float)j - i)/CLOCKS_PER_SEC);
	int c = 0;
	for (int m = 0; m < ant.tab_size; m++)
	{
		ft_printf("-- len_tab %d : %d --\n", m, ant.adj[m].len_tab);
		if (ant.adj[m].len_tab > 2)
			c++;
		for (int l = 0; l < ant.adj[m].len_tab; l++)
			ft_printf("-- %d: %d: %d\n", m, l, ant.adj[m].tab[l]);
		ft_printf("\n");
	}
	for (int l = 0; l < ant.adj[!(ant.start_room)].dist; l++)
	{
		int n = 0;
		for (int m = 0; m < ant.tab_size; m++)
			if (ant.adj[m].dist2 == l)
				n++;
		ft_printf("dist : %d nb : %d\n", l, n);
	}
	int m = 0;
	for (int l = 0; l < ant.tab_size; l++)
		if (ant.adj[l].dist != -1)
			m++;
	ft_printf("nb start_room connection(s) : %d\n", ant.adj[ant.start_room].len_tab);
	ft_printf("nb not tube room(s) : %d\n", c);
	ft_printf("nb room(s) connected : %d / %d\n", m, ant.tab_size);
	path(&ant);
	for (int l = 0; l < ant.nb_path; l++)
	{
		ft_printf("%d %d\n", l, ant.len_path[l]);
		for (int m = 0; m <= ant.len_path[l]; m++)
		{
			ft_printf ("%d : %d\n", m, ant.path[l][m]);
		}
		ft_printf("dist2 %d\n", ant.adj[ant.path[l][ant.len_path[l]]].dist2);
	}
	ant.nb_ant_per_path = ft_memalloc(sizeof(int) * ant.nb_path);
	ant.is_used = ft_memalloc(sizeof(int) * ant.nb_path);
	for (int l = 0; l < ant.nb_path; l++)
	{
		if (ant.path[l][ant.len_path[l]] == !(ant.start_room))
		{
			ant.is_used[l] = 1;
			ant.len_path[l]++;
		}

	}
	while (ant.nb_ant > 0)
	{
		int sum_diff = 0;
		int max = 0;
		int max_index = -1;
		for (int l = 0; l < ant.nb_path; l++)
		{
			if (ant.is_used[l])
			{
				if (ant.len_path[l] > max)
				{
					max_index = l;
					max = ant.len_path[l];
				}
			}
		}
		for (int l = 0; l < ant.nb_path; l++)
		{
			if (ant.is_used[l] && l != max_index)
			{
				sum_diff += max - ant.len_path[l];
			}
		}
		if (ant.nb_ant <= sum_diff)
			ant.is_used[max_index] = 0;
		else
		{
			for (int l = 0; l < ant.nb_path; l++)
			{
				if (ant.is_used[l])
				{
					ant.nb_ant_per_path[l]++;
					ant.nb_ant--;
				}
			}
		}
	}
	int max_path = 0;
	for (int l = 0; l < ant.nb_path; l++)
	{
		ft_printf("%d %d %d\n", ant.path[l][0], ant.nb_ant_per_path[l], ant.len_path[l]);
		if (ant.nb_ant_per_path[l])
		max_path = ft_max(max_path, ant.nb_ant_per_path[l] + ant.len_path[l] - 1);
	}
	ft_printf("move : %d\n", max_path);
	return (0);
}
