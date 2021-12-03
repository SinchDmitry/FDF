/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:18 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/11 17:38:49 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	long	i;
	long	j;

	i = -1;
	j = -1;
	if (s1 && s2)
	{
		tmp = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
		if (!tmp)
			return (NULL);
		while (s1[++i])
			tmp[i] = s1[i];
		while (s2[++j])
			tmp[j + i] = s2[j];
		tmp[j + i] = '\0';
		return (tmp);
	}
	return (NULL);
}
