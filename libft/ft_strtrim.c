/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:50 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/11 17:44:51 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		a;
	int		tmp;
	char	*res;

	i = 0;
	a = -1;
	if (s1 && set)
	{
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		tmp = i - 1;
		while (s1[i])
			i++;
		while (i >= 0 && ft_strchr(set, s1[i]) && i > tmp)
			i--;
		res = malloc(sizeof(char) * ((i - tmp) + 1));
		if (!res)
			return (NULL);
		while (tmp <= i)
			res[++a] = s1[++tmp];
		res[a] = '\0';
		return (res);
	}
	return (NULL);
}
