/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:49:18 by nsondag           #+#    #+#             */
/*   Updated: 2019/02/05 17:07:45 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int sending_ants(t_a *ant, int max_path)
{
	int i;
	int j;
	int k;
	int l;
	int	*start_ant;
	int	nb_move;
	int	nb;
	char ****output;

	if (!(start_ant = ft_memalloc(sizeof(int) * ant->nb_path)))
		return (MERROR);
	if (!(output = ft_memalloc(sizeof(char****) * ant->nb_path)))
		return (MERROR);
	i = 0;
	start_ant[i] = 1;
	while (++i < ant->nb_path)
		start_ant[i] = start_ant[i - 1] + ant->nb_ant_per_path[i - 1];
	i = 0;
	while (i < ant->nb_path)
	{
		if (!(output[i] = ft_memalloc(sizeof(char***) * max_path)))
			return (MERROR);
		nb_move = 1;
		k = 0;
		nb = ant->nb_ant_per_path[i];
		l = 0;
		while (nb + ant->len_path[i] > 0)
		{
			j = 0;
			k = k - nb_move + 1;
			if (!(output[i][l] = ft_memalloc(sizeof(char**) * 127)))
				return (MERROR);
			if (!(output[i][l][j] = ft_memalloc(sizeof(char*) * ant->len_path[i])))
				return (MERROR);
			while (j < nb_move)
			{
				j++;
				k++;
				if (k - 1 >= ant->nb_ant_per_path[i] || start_ant[i] + k - 1> ant->nb_ant)
					continue ;
				ft_printf("L%d-%s%#>", start_ant[i] + k - 1,
						ant->adj[ant->path[i][nb_move - j]].name, &output[i][l][j-1]);
				if (j >= nb_move || k >= ant->nb_ant_per_path[i] ||
						start_ant[i] + k > ant->nb_ant)
					l++;
			}
			nb_move < ant->len_path[i] ? nb_move++ : 0;
			nb_move == ant->len_path[i] ? nb-- : 0;
		}
		i++;
	}
	l = 0;
	while (l < max_path)
	{
		i = 0;
		while (i < ant->nb_path)
		{
			if (!ant->nb_ant_per_path[i])
			{
				i++;
				continue ;
			}
			j = 0;
			while (output[i][l][j])
			{
				ft_printf("%s", output[i][l][j]);
				j++;
				if (i + 1 < ant->nb_path || output[i][l][j])
					ft_printf(" ");
			}
			i++;
		}
		ft_printf("\n");
		l++;
	}
	return (0);
}
