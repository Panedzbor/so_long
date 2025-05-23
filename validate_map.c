/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:04:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 19:04:34 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	valid_chars(t_gamedata *gd)
{
	const char	*allowed_chars;
	int			i;

	allowed_chars = "01CEP\n";
	i = 0;
	while (gd->map[i])
	{
		if (!ft_strchr(allowed_chars, gd->map[i]))
			return (false);
		i++;
	}
	return (true);
}

int	valid_amount(t_gamedata *gd)
{
	int		i;
	int		c;
	int		e;
	int		p;
	char	ch;

	sl_init_ints(&i, &c, &e, &p);
	while (gd->map[i])
	{
		ch = gd->map[i];
		if (ch == 'C')
			c++;
		else if (ch == 'E')
			e++;
		else if (ch == 'P')
			p++;
		i++;
	}
	if (c <= 0)
		return (2);
	if (e != 1)
		return (3);
	if (p != 1)
		return (4);
	return (0);
}

bool	valid_shape(t_gamedata *gd)
{
	int	row_len;
	int	i;

	row_len = 0;
	i = 0;
	while (gd->map[i])
	{
		if (gd->map[i] == '\n')
		{
			if (row_len != gd->map_width)
				return (false);
			row_len = 0;
		}
		else
			row_len++;
		i++;
	}
	if (row_len != gd->map_width && row_len)
		return (false);
	return (true);
}

bool	valid_walls(t_gamedata *gd)
{
	int		i;
	char	ch;

	i = 0;
	while (gd->map[i])
	{
		ch = gd->map[i];
		if (ch == '\n' && i == (gd->map_width + 1) * gd->map_height - 1)
			return (true);
		if (i < gd->map_width && ch != '1')
			return (false);
		if (i >= (gd->map_width + 1) * (gd->map_height - 1) && ch != '1')
			return (false);
		if (i % (gd->map_width + 1) == 0 && ch != '1')
			return (false);
		if ((i + 2) % (gd->map_width + 1) == 0 && ch != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	valid_path(t_gamedata *gd, int pos)
{
	int			up;
	int			right;
	int			down;
	int			left;
	static bool	completed;

	up = -(gd->map_width + 1);
	right = 1;
	down = gd->map_width + 1;
	left = -1;
	if (!completed)
		move_check(up, pos, gd, &completed);
	if (!completed)
		move_check(right, pos, gd, &completed);
	if (!completed)
		move_check(down, pos, gd, &completed);
	if (!completed)
		move_check(left, pos, gd, &completed);
	return (completed);
}
