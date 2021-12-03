/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:55 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/10 00:10:17 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (s)
	{
		if (start >= ft_strlen(s))
			len = 0;
		if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
		tmp = malloc(sizeof(char) * (len + 1));
		if (tmp == NULL)
			return (NULL);
		while (i < len && s[i + start])
		{
			tmp[i] = s[i + start];
			i++;
		}
		tmp[i] = '\0';
	}
	return (tmp);
}
