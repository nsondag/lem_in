/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:22:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 17:48:36 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int main()
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
	return (0);
}
