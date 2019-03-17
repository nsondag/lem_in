/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:19:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 20:32:12 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**rea(t_a *ant, char **s1, char *s2)
{
	char		**to_return;
	static int	start = 0;

	if (!(to_return = malloc(sizeof(char*) * (ant->nb_data + 1))))
		return (NULL);
	if (start)
	{
		memcpy(to_return, s1, sizeof(char*) * ant->nb_data);
		free(s1);
	}
	else
		start++;
	to_return[ant->nb_data] = s2;
	if (s2)
		ant->nb_data++;
	return (to_return);
}

int		realloc_tab(t_room *room)
{
	t_tube	*tmp;

	tmp = room->tubes;
	if (!(room->tubes = (t_tube*)malloc(sizeof(t_tube) * (room->nb_tubes + 1))))
	{
		free(tmp);
		return (MERROR);
	}
	memcpy(room->tubes, tmp, sizeof(t_tube) * room->nb_tubes);
	free(tmp);
	room->nb_tubes++;
	return (0);
}

int		link_room(t_a *ant, int i, int j)
{
	int		k;
	int		tmp;

	k = -1;
	while (++k < ant->room[i].nb_tubes)
		if (j == ant->room[i].tubes[k].dest)
		{
			ant->buf[ft_strlen(ant->buf)] = '-';
			return (0);
		}
	if (realloc_tab(&(ant->room[i])))
		return (MERROR);
	tmp = ant->room[i].nb_tubes - 1;
	ft_bzero(&ant->room[i].tubes[tmp], sizeof(t_tube));
	ant->room[i].tubes[tmp].dest = j;
	ant->room[i].tubes[tmp].len = 1;
	if (realloc_tab(&(ant->room[j])))
		return (MERROR);
	tmp = ant->room[j].nb_tubes - 1;
	ft_bzero(&ant->room[j].tubes[tmp], sizeof(t_tube));
	ant->room[j].tubes[tmp].dest = i;
	ant->room[j].tubes[tmp].len = 1;
	ant->buf[ft_strlen(ant->buf)] = '-';
	return (0);
}

int		get_tube(t_a *ant)
{
	char	*room1;
	char	*room2;
	int		i;
	int		j;

	i = ft_indexof(ant->buf, '-');
	if (ant->buf[0] != '#' && i != -1)
	{
		room1 = ant->buf;
		room2 = ant->buf + i + 1;
		ant->buf[i] = 0;
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
	(i + j == 1) ? ant->direct = 1 : 0;
	if (i == j)
	{
		ant->buf[ft_strlen(ant->buf)] = '-';
		return (0);
	}
	return (link_room(ant, i, j));
}

int		parse(t_a *ant)
{
	int		ret;

	if (get_tube(ant) < 0)
		return (INVALID);
	while ((ret = get_next_line(0, &ant->buf)) > 0)
	{
		ant->data = rea(ant, ant->data, ant->buf);
		if ((ret = get_tube(ant)) < 0)
			return (ret);
	}
	return (ret == -1 ? MERROR : VALID);
}
