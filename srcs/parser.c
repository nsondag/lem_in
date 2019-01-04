/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 16:10:55 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdio.h>

int	parser(t_a *ant)
{
	char	*line;
	char	*room1;
	char	*room2;
	int		dash;
	int		end;
	int		i;
	int		j;
	int		len_tab;

	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		j = 0;
		dash = ft_indexof(line, '-');
		end = ft_last_indexof(line, '\0');
		if (*line != '#' && dash != -1)
		{
			room1 = ft_strsub(line, 0, dash);
			room2 = ft_strsub(line, dash + 1, end - dash);	
		}
		while (ft_strcmp(ant->adj[i].name, room1))
			i++;
		while (ft_strcmp(ant->adj[j].name, room2))
			j++;
		len_tab = ft_tablen((void**)ant->adj[i].tab);
		ant->adj[i].tab = (int*)malloc(sizeof(int) * len_tab + 1);
		ant->adj[i].tab[len_tab] = j;
		len_tab = ft_tablen((void**)ant->adj[j].tab);
		ant->adj[j].tab = (int*)malloc(sizeof(int) * len_tab + 1);
		ant->adj[j].tab[len_tab] = i;
		free(line);
	}
	return (0);
}
