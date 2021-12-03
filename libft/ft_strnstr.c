/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:43 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/11 16:03:42 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	tmp = 0;
	if (!needle[i] || !needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((haystack[i] != needle[j]) && haystack[i] && i < len)
			i++;
		if (!haystack[i])
			return (NULL);
		tmp = i;
		while (haystack[i] && (haystack[i] == needle[j++]) && i++ < len)
			if (!needle[j])
				return ((char *)haystack + tmp);
		i = tmp + 1;
	}
	return (NULL);
}
