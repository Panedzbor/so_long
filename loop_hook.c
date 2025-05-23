/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:41:36 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:41:40 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	background_activities(t_gamedata *gd)
{
	static int	counter;

	if (counter == 7000)
	{
		draw_map(gd);
		display_sprites(gd);
		counter = 0;
	}
	counter++;
	return (0);
}
