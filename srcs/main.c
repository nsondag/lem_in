/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/27 21:10:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <time.h>

//void	racc_path(t_a *ant, int l, int offset, int len)
//{
//	for (int m = offset + len; m < ant->len_path[l]; m++)
//	{
//		ant->path[l][m - len] = ant->path[l][m];
//	}
//	ant->len_path[l] -= len;
//}

int		main()
{
	t_a		ant;
	int		ret;

	ft_bzero(&ant, sizeof(ant));
	read_room(&ant);
	if (!(ant.room) || !(ant.room + 1) || !(ant.buf))
		exit_func(INVALID, &ant);
	if ((ret = parse(&ant)))
		exit_func(ret, &ant);
	//ft_printf("nb_ant %d\n", ant.nb_ant);
	search_for_deadend(ant.room, ant.nb_room);
	search_for_mult_path(&ant, 2);
	ant.start_room = ant.room[0].nb_tubes > ant.room[1].nb_tubes ? 1 : 0;
	clock_t i = clock();
	if (smallest(&ant))
		exit_func(INVALID, &ant);
	clock_t j = clock();
	ft_printf("ici %f\n", ((float)j - i)/CLOCKS_PER_SEC);
	int c = 0;
	for (int m = 0; m < ant.nb_room; m++)
	{
		ft_printf("-- nb_tubes %d : %d --\n", m, ant.room[m].nb_tubes);
		if (ant.room[m].nb_tubes > 2)
			c++;
		for (int l = 0; l < ant.room[m].nb_tubes; l++)
			ft_printf("-- %d: %d: %d\n", m, ant.room[m].tubes[l].len, ant.room[m].tubes[l]);
		ft_printf("\n");
	}
	modify_tubes_first(&ant);
	ft_printf("---after_modif---\n");
	for (int m = 0; m < ant.nb_room; m++)
	{
		ft_printf("-- nb_tubes %d : %d --\n", m, ant.room[m].nb_tubes);
		for (int l = 0; l < ant.room[m].nb_tubes; l++)
			ft_printf("-- %d: %d: %d: %d\n", m, ant.room[m].tubes[l].tmp_len, ant.room[m].tubes[l].dest, ant.room[m].tubes[l].tree);
		ft_printf("\n");
	}
	int m = 0;
	for (int l = 0; l < ant.nb_room; l++)
		if (ant.room[l].dist != -1)
			m++;
	ft_printf("nb start_room connection(s) : %d\n", ant.room[ant.start_room].nb_tubes);
	ft_printf("nb not tube room(s) : %d\n", c);
	ft_printf("nb room(s) connected : %d / %d\n", m, ant.nb_room);

	int f = 1;
	t_path **s = start_searching(&ant, NULL, 0);
	for (int j=0;j<f;j++)
		for (int d=0;d<s[j]->len_path;d++)
			ft_printf("---- %d\n", s[j]->chain[d]);
	return (0);
}
