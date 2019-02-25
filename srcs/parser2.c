/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:21:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/02/24 15:45:23 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		read_comment(char *line)
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

int		is_digit_str(char *str)
{
	int		ok;

	ok = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		ok = 1;
		str++;
	}
	return (ok && !(*str));
}

int		end_add_entry(char ***split, int to_return)
{
	ft_free_tab((void***)split);
	return (to_return);
}

int		realloc_adj(int index, t_a *all)
{
	t_room	*tmp;

	tmp = all->room;
	if (!(all->room = ft_memalloc((REALLOC_SIZE + index) * sizeof(t_room))))
		return (MERROR);
	ft_memcpy(all->room, tmp, index * sizeof(t_room));
	free(tmp);
	return (VALID);
}

int		add_entry(t_var *for_this, t_a *all)
{
	char	**split;

	if (!(split = ft_strsplit(all->buf, ' ')))
		return (MERROR);
	if (ft_tablen((void**)split) != 3)
		return (ft_indexof(all->buf, '-') != -1) ?
end_add_entry(&split, ENDFUNCTION) : end_add_entry(&split, INVALID);
	if (ft_indexof(all->buf, '-') != -1)
		return (end_add_entry(&split, INVALID));
	if (!is_digit_str(split[1]) || !is_digit_str(split[2]))
		return (end_add_entry(&split, INVALID));
	if (for_this->is_start && for_this->is_end)
		return (end_add_entry(&split, INVALID));
	else if (for_this->is_start)
		all->room[0].name = ft_strdup(*split);
	else if (for_this->is_end)
		all->room[1].name = ft_strdup(*split);
	else
	{
		if (!(all->nb_room % REALLOC_SIZE) && realloc_adj(all->nb_room, all))
			return (end_add_entry(&split, MERROR));
		all->room[all->nb_room].name = ft_strdup(*split);
//		all->room[all->nb_room].is_passed = -1;
		all->nb_room++;
	}
	for_this->is_start = 0;
	for_this->is_end = 0;
	return (end_add_entry(&split, VALID));
}

int		read_room(t_a *all)
{
	t_var	for_this;

	if (!(all->room = ft_memalloc(REALLOC_SIZE * sizeof(t_room))))
		return (MERROR);
	bzero(&for_this, sizeof(for_this));
	all->nb_room = 2;
	if (get_next_line(0, &(all->buf)) > 0)
	{
		all->nb_ant = ft_atoi(all->buf);
		if (all->nb_ant <= 0)
			return (INVALID);
	}
	all->data = ft_strdup(all->buf);
	//ft_printf("%s\n", all->buf); //a remettre a la fin
	ft_strdel(&(all->buf));
	while (get_next_line(0, &(all->buf)) > 0)
	{
		all->data = rea(all->data, "\n");
		all->data = rea(all->data, all->buf);
		//ft_printf("%s\n", all->buf);// a remettre a la fin
		if ((for_this.ret = read_comment(all->buf)) == VALID)
		{
			if ((for_this.ret = add_entry(&for_this, all)) == ENDFUNCTION)
				break ;
			else if (for_this.ret < 0)
				exit_func(for_this.ret, all);
		}
		else if (for_this.ret == START)
			for_this.is_start = 1;
		else if (for_this.ret == END)
			for_this.is_end = 1;
		else if (for_this.ret == INVALID)
			exit_func(INVALID, all);
		ft_strdel(&(all->buf));
	}
	return (for_this.ret);
}
