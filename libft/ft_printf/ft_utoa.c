/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:45:52 by earutiun          #+#    #+#             */
/*   Updated: 2024/12/06 19:55:31 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		count_digits(unsigned int n);
static void		convert(char *number, unsigned int n, int digits);

char	*ft_utoa(unsigned int n)
{
	int					digits;
	char				*ptr;

	digits = count_digits(n);
	ptr = (char *)ft_calloc(digits + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	convert(ptr, n, digits);
	ptr[digits] = '\0';
	return (ptr);
}

static int	count_digits(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static void	convert(char *number, unsigned int n, int digits)
{
	unsigned int	r;
	unsigned int	i;

	r = n % 10;
	i = n / 10;
	number[digits - 1] = r + '0';
	digits--;
	while (i > 0)
	{
		n = i;
		r = n % 10;
		i = n / 10;
		number[digits - 1] = r + '0';
		digits--;
	}
}
