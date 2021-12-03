/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:56:46 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/11 16:18:14 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	to_malloc(long num)
{
	long	f;

	f = 0;
	if (num <= 0)
		f = 1;
	while (num)
	{
		num /= 10;
		f++;
	}
	return (f + 1);
}

static char	*input(long tmp, long nb, char *str, long f)
{
	while (tmp >= 1)
	{
		str[f++] = (nb / tmp) + '0';
		nb %= tmp;
		tmp /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	f;
	char	*str;
	long	tmp;
	long	nb;

	tmp = n;
	f = to_malloc(tmp);
	str = malloc(sizeof(char) * f);
	if (!str)
		return (NULL);
	str[--f] = '\0';
	nb = n;
	tmp = 1;
	while (f-- > 1)
		tmp *= 10;
	if (nb < 0)
	{
		nb = -nb;
		str[f++] = '-';
		tmp /= 10;
	}	
	return (input(tmp, nb, str, f));
}
