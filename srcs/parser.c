/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/10 14:52:36 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
# include <stdio.h>

int		realloc_tab(t_room *room)
{
	t_tube	*tmp;

	tmp = room->tubes;
	room->nb_tubes++;
	if (!(room->tubes = (t_tube*)malloc(sizeof(t_tube) * (room->nb_tubes))))
	{
		free(tmp);
		return (MERROR);
	}
	memcpy(room->tubes, tmp, sizeof(t_tube) * (room->nb_tubes - 1));
	free(tmp);
	return (0);
}

int		get_tube(t_a *ant)
{
	char	*room1;
	char	*room2;
	int		dash;
	int		end;
	int		i;
	int		j;
	int		k;

	dash = ft_indexof(ant->buf, '-');
	end = ft_strlen(ant->buf + dash) + dash;
	if (ant->buf[0] != '#' && dash != -1)
	{
		room1 = ft_strsub(ant->buf, 0, dash);
		room2 = ft_strsub(ant->buf, dash + 1, end - dash);	
	}
	else
		return (ant->buf[0] == '#' ? VALID : INVALID);
	i = 0;
	while (i < ant->nb_room && ft_strcmp(ant->room[i].name, room1))
		i++;
	j = 0;
	while (j < ant->nb_room && ft_strcmp(ant->room[j].name, room2))
		j++;
	if (i == ant->nb_room || j == ant->nb_room)
		return (INVALID);
	if (i == j)
		return (0);
	k = -1;
	while (++k < ant->room[i].nb_tubes)
		if (j == ant->room[i].tubes[k].dest)
			return (0);
	if (realloc_tab(&(ant->room[i])))
		return (MERROR);
	bzero(&ant->room[i].tubes[ant->room[i].nb_tubes - 1], sizeof(t_tube));
	ant->room[i].tubes[ant->room[i].nb_tubes - 1].dest = j;
	ant->room[i].tubes[ant->room[i].nb_tubes - 1].len = 1;
	if (realloc_tab(&(ant->room[j])))
		return (MERROR);
	bzero(&ant->room[j].tubes[ant->room[j].nb_tubes - 1], sizeof(t_tube));
	ant->room[j].tubes[ant->room[j].nb_tubes - 1].dest = i;
	ant->room[j].tubes[ant->room[j].nb_tubes - 1].len = 1;
	return (0);
}

int		parse(t_a *ant)
{
	int		ret;

	if (get_tube(ant) < 0)
		return (INVALID);
	while ((ret = get_next_line(0, &ant->buf)) > 0)
	{
		ft_printf("%s\n", ant->buf); //a remettre a la fin
		if ((ret = get_tube(ant)) < 0)
			return (ret);
		ft_strdel(&(ant->buf));
	}
	return (ret == -1 ? MERROR : VALID);
}
