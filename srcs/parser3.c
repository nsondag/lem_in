/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:18:25 by hvromman          #+#    #+#             */
/*   Updated: 2019/03/19 23:18:27 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	read_comment(char *line)
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

int	is_digit_str(char *str)
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
