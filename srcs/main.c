/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/08 14:58:32 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main()
{
	t_a		ant;

	bzero(&ant, sizeof(ant));
	read_room(&ant);
	ft_printf("-- nb_ant %d\n", ant.nb_ant);
	for (int count = 0; ant.adj[count].name; count++)
		ft_printf("-- %s\n", ant.adj[count].name);
	ft_printf("-- tab_size %d\n", ant.tab_size);
	if (!(ant.adj) || !(ant.adj + 1) || !(ant.buf) || parse(&ant))
		exit_func(INVALID, &ant);
	dead_ends(&ant);
	ft_printf("-- tab_size %d\n", ant.tab_size);
	//--------------------------------------------------------------
	for (int m = 0; m < ant.tab_size; m++)
		for (int l = 0; l < ant.adj[m].len_tab; l++)
			ft_printf("-- %d: %d: %d\n", m, l, ant.adj[m].tab[l]);
	//--------------------------------------------------------------
	ant.start_room = ant.adj[0].len_tab < ant.adj[1].len_tab ? 0 : 1;
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	return (0);
}
