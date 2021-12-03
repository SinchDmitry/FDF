/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba <aarchiba@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:23 by aarchiba          #+#    #+#             */
/*   Updated: 2021/10/11 15:36:51 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	dlen = i;
	if (dlen >= 0)
	{
		while (i + 1 < dstsize && src[j])
			dst[i++] = src[j++];
	}
	if (dlen < dstsize)
		dst[i] = 0;
	return (dlen + slen);
}
