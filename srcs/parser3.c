/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:21:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/15 21:52:13 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				read_nb_ant(t_a *all, t_var *for_this)
{
	bzero(for_this, sizeof(t_var));
	all->nb_room = 2;
	while (get_next_line(0, &(all->buf)) > 0)
	{
		all->data = rea(all, all->data, all->buf);
		if (read_comment(all->buf) != COMMENT)
		{
			all->nb_ant = ft_atoi(all->buf);
			if (all->nb_ant <= 0)
				return (INVALID);
			break ;
		}
	}
	return (VALID);
}

inline int		read_comment(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (!len)
		return (INVALID);
	else if (*line == '#')
	{
		if (len == 5 && !ft_strcmp(line, "##end"))
			return (END);
		else if (len == 7 && !ft_strcmp(line, "##start"))
			return (START);
		else
			return (COMMENT);
	}
	else if (*line == 'L')
		return (INVALID);
	else
		return (VALID);
}
