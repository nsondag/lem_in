/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:49:18 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/27 21:10:12 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int sending_ants(t_a *ant)
{
	int i;
	int j;
	int	*start_ant;
	int	nb_move;

	ft_printf("%d\n", ant->len_path[0]);
	if (!(start_ant = ft_memalloc(sizeof(int) * ant->nb_path)))
		return (MERROR);
	i = 0;
	start_ant[i] = 1;
	while (++i < ant->nb_path)
		start_ant[i] = ant->nb_ant_per_path[i - 1] + 1;
	//---------------------------------------------------------------------
	nb_move = 1;
	j = -1;
		ft_printf("L%d-%d ", start_ant[j] + i, ant->path[i][j]);
	ft_printf("\n");
	return (0);
}
