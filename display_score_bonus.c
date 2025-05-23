/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_score_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:47:35 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 17:47:47 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	display_score(t_gamedata *gd)
{
	char	*num;
	char	*str;

	num = ft_itoa(gd->movements);
	str = ft_strjoin("Moves: ", num);
	free(num);
	mlx_set_font(gd->mlx_ptr, gd->win_ptr, "10x20");
	mlx_string_put(gd->mlx_ptr, gd->win_ptr, 50, 30, 0xFF0000, str);
	free(str);
}
