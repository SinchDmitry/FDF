/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:14 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/26 21:05:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <stdio.h>

int	ft_atoi(const char *str, int *flag)
{
	int		i;
	int		a;
	long	res;

	i = 0;
	a = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			a = -a;
	if (str[i] >= 48 && str[i] <= 57)
		while (str[i] >= 48 && str[i] <= 57)
			res = res * 10 - (str[i++] - '0');
	if (str[i] == ',')
		*flag = i;
	return (a * (int)res);
}
