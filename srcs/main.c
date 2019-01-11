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
	ft_printf("-- nb_ant %d\n", ant.nb_ant);
	for (int count = 0; ant.adj[count].name; count++)
		ft_printf("-- %s\n", ant.adj[count].name);
	ft_printf("-- tab_size %d\n", ant.tab_size);
	if (!(ant.adj) || !(ant.adj + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	if ((ret = parse(&ant)))
		exit_func(ret, &ant);
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
	int m = 0;
	for (int l = 0; l < ant.tab_size; l++)
		if (ant.adj[l].dist == -1)
			m++;
	ft_printf("nb start_room connection(s) : %d\n", ant.adj[ant.start_room].len_tab);
	ft_printf("nb not tube room(s) : %d\n", c);
	ft_printf("nb room(s) not connected : %d / %d\n", m, ant.tab_size);
	return (0);
}
