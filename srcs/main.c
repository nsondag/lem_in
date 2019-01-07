/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/07 20:21:40 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		main()
{
	t_a		ant;

	bzero(&ant, sizeof(ant));
	read_room(&ant);
	ft_printf("%d\n", ant.nb_ant);
	for (int count = 0; ant.adj[count].name; count++)
		ft_printf("%s\n", ant.adj[count].name);
	ft_printf("%d\n", ant.tab_size);
	ft_printf("%s\n", ant.buf);
	if (!(ant.adj) || !(ant.adj + 1) || !(ant.buf) || parse(&ant))
		exit_func(INVALID, &ant);
	ant.start_room = ant.adj[0].len_tab < ant.adj[1].len_tab ? 0 : 1;
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	return (0);
}
