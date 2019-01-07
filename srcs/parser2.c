/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 14:21:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/01/04 14:21:33 by hvromman         ###   ########.fr       */
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
	t_adj	*tmp;

	tmp = all->adj;
	if (!(all->adj = ft_memalloc((10 + index) * sizeof(t_adj))))
		return (MERROR);
	ft_memcpy(all->adj, tmp, index * sizeof(t_adj));
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
	if (!is_digit_str(split[1]) || !is_digit_str(split[2]))
		return (end_add_entry(&split, INVALID));
	if (for_this->is_start && for_this->is_end)
		return (end_add_entry(&split, INVALID));
	else if (for_this->is_start)
		all->adj[0].name = ft_strdup(*split);
	else if (for_this->is_end)
		all->adj[1].name = ft_strdup(*split);
	else
	{
		if (!(all->tab_size % 10) && realloc_adj(all->tab_size, all))
			return (end_add_entry(&split, MERROR));
		all->adj[all->tab_size].name = ft_strdup(*split);
		all->tab_size++;
	}
	for_this->is_start = 0;
	for_this->is_end = 0;
	return (end_add_entry(&split, VALID));
}

int		read_room(t_a *all)
{
	t_var	for_this;

	if (!(all->adj = ft_memalloc(10 * sizeof(t_adj))))
		return (MERROR);
	bzero(&for_this, sizeof(for_this));
	all->tab_size = 2;
	if (get_next_line(0, &(all->buf)) > 0)
		all->nb_ant = ft_atoi(all->buf);
	ft_printf("%s\n", all->buf); // pas retirer
	ft_strdel(&(all->buf));
	while (get_next_line(0, &(all->buf)) > 0)
	{
		ft_printf("%s\n", all->buf); // pas retirer
		if (read_comment(all->buf) == VALID)
		{
			if ((for_this.ret = add_entry(&for_this, all)) == ENDFUNCTION)
				break ;
			else if (for_this.ret == MERROR || for_this.ret == INVALID)
				exit_func(for_this.ret, all);
		}
		else if (read_comment(all->buf) == START)
			for_this.is_start = 1;
		else if (read_comment(all->buf) == END)
			for_this.is_end = 1;
		else if (read_comment(all->buf) == INVALID)
			exit_func(INVALID, all);
		ft_strdel(&(all->buf));
	}
	return (for_this.ret);
}
