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
	ant.start_room = 0;
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
			ft_printf("-- dest %2d: len %2d\n", ant.room[m].tubes[l].dest, ant.room[m].tubes[l].len);
		ft_printf("\n");
	}
	modify_tubes_first(&ant);
	ft_printf("---after_modif---\n");
	for (int m = 0; m < ant.nb_room; m++)
	{
		ft_printf("-- %d --\n", m);
		for (int l = 0; l < ant.room[m].nb_tubes; l++)
			ft_printf("-- dest %2d: tmp_len %2d: tree %2d\n", ant.room[m].tubes[l].dest, ant.room[m].tubes[l].tmp_len, ant.room[m].tubes[l].tree);
		ft_printf("\n");
	}
	int m = 0;
	for (int l = 0; l < ant.nb_room; l++)
		if (ant.room[l].dist != -1)
			m++;
	ft_printf("nb start_room connection(s) : %d\n", ant.room[ant.start_room].nb_tubes);
	ft_printf("nb not tube room(s) : %d\n", c);
	ft_printf("nb room(s) connected : %d / %d\n", m, ant.nb_room);

	ant.path = malloc(sizeof(t_path**) * ant.room[ant.start_room].nb_tubes);
	int f = 0;
	ant.path[f] = start_searching(&ant, NULL, f);
	for (int j=0;j<f+1;j++)
		for (int d=0;d<ant.path[f][j]->len_path;d++)
			ft_printf("---- %d\n", ant.path[f][j]->chain[d]);
	calculate_move(&ant, ant.path[f], 1);
	calculate_start(&ant, ant.path[f], 1);
	print_sol(&ant, ant.path[f], 1);
	clock_t i1 = clock();
	change_all_len(&ant, ant.room, ant.path[f], 1);
	for (int m = 0; m < ant.nb_room; m++)
	{
		ft_printf("-- is_passed %d : %d --\n", m, ant.room[m].is_passed);
		for (int l = 0; l < ant.room[m].nb_tubes; l++)
			ft_printf("-- %d: %d: %d: %d\n", m, ant.room[m].tubes[l].len, ant.room[m].tubes[l].dest, ant.room[m].tubes[l].tree);
		ft_printf("\n");
	}
	f++;
	if (smallest2(&ant))
		exit_func(INVALID, &ant);
	ant.path[f] = start_searching(&ant, ant.path[f-1], f);
	if (!(ant.path[f]))
	{
		ft_printf("path not found\n");
		return (0);
	}
	for (int j=0;j<f+1&&ft_printf("\n");j++)
		for (int d=0;d<ant.path[f][j]->len_path;d++)
			ft_printf("---- %d\n", ant.path[f][j]->chain[d]);
	clock_t j1 = clock();
	ft_printf("ici %lf\n", ((double)j1 - i1)/CLOCKS_PER_SEC);
	return (0);
}
