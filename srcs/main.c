/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/08 12:49:20 by nsondag          ###   ########.fr       */
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
	ant.start_room = ant.adj[0].len_tab < ant.adj[1].len_tab ? 0 : 1;
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	return (0);
}
