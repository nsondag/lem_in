/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:49:18 by nsondag           #+#    #+#             */
/*   Updated: 2019/01/29 13:59:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int sending_ants(t_a *ant)
{
	int i;
	int j;
	int k;
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
	i = 0;
	k = 0;
	while (ant->nb_ant + ant->len_path[i] > 0)
	{
		j = 0;
		k = k - nb_move + 1;
		while (j < nb_move)
		{
			if (k > ant->nb_ant_per_path[i] + 1)
			{
				j++;
				k++;
				continue ;
			}
			ft_printf("L%d-%d", start_ant[i] + k,
					ant->path[i][nb_move - j - 1]);
			j++;
			k++;
			(j < nb_move && k <= ant->nb_ant_per_path[i] + 1)
				? ft_printf(" ") : ft_printf("\n");
		}
		if (nb_move < ant->len_path[i])
			nb_move++;
		if (nb_move == ant->len_path[i])
			ant->nb_ant--;
	}
	return (0);
}
