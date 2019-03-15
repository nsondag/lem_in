/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:06:48 by nsondag           #+#    #+#             */
/*   Updated: 2019/03/15 20:32:35 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	print_all(int nb_ant, char *dest)
{
	int		i;

	i = 1;
	while (i < nb_ant)
		ft_printf("L%d-%s ", i++, dest);
	ft_printf("L%d-%s\n", i, dest);
	return (0);
}
