/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/17 21:16:36 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** g[0] = r;
** g[1] = k;
** g[2] = f;
** g[3] = i;
** g[4] = min;
*/

static int	find(t_a *all)
{
	int g[5];

	g[2] = 0;
	while (g[2] < all->room[0].nb_tubes &&
			(all->path[g[2]] = start_searching(all, all->path, g[2])))
	{
		g[0] = g[2] + 1;
		while (--g[0] > -1)
		{
			g[1] = g[0];
			while (--g[1] > -1)
				if (crossing_path(all->path, g))
					ft_printf("%>fail\n", 2);
		}
		change_all_len(all, all->room, all->path[g[2]], g[2] + 1);
		moves(all, all->path[g[2]], g[2]);
		smallest2(all);
		g[2]++;
	}
	g[3] = 0;
	g[4] = 0;
	while (++g[3] < g[2])
		(all->nb_move[g[4]] > all->nb_move[g[3]]) ? g[4] = g[3] : 0;
	all->nb_used = g[4];
	return (0);
}

int			main(void)
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	read_room(&ant);
	if (!(ant.room) || !(ant.room + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	(ret = parse(&ant)) ? exit_func(ret, &ant) : 0;
	ant.start_room = 0;
	(smallest(&ant) && ant.direct != 1) ? exit_func(INVALID, &ant) : 0;
	ret = -1;
	while (++ret < ant.nb_data)
		ft_printf("%s\n", ant.data[ret]);
	if (ant.direct == 1)
		exit_func(print_all(ant.nb_ant, ant.room[1].name), &ant);
	modify_tubes_first(&ant);
	ant.path = ft_memalloc(sizeof(t_path**) *
			ant.room[ant.start_room].nb_tubes);
	ant.nb_move = ft_memalloc(sizeof(int) * ant.room[ant.start_room].nb_tubes);
	find(&ant);
	calculate_start(&ant, ant.path[ant.nb_used], ant.nb_used + 1);
	print_sol(&ant, ant.path[ant.nb_used], ant.nb_used);
	exit_func(0, &ant);
}
