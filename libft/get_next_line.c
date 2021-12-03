/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:31:29 by aarchiba          #+#    #+#             */
/*   Updated: 2021/11/23 17:51:04 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_back_n(t_gnl **lst, void *content, int fd)
{
	t_gnl	*last;
	t_gnl	*buf;

	last = *lst;
	buf = malloc(sizeof(t_gnl));
	if (!buf)
		return ;
	buf->fd = fd;
	buf->buff = content;
	buf->next = NULL;
	buf->i = 0;
	if (!(*lst))
		*lst = buf;
	else
	{
		while (last->next)
			last = last->next;
		last->next = buf;
	}
}

static int	checkbuff(char *buff, t_gnl **bank, long *counter)
{
	long	st_c;

	st_c = *counter;
	while (buff[*counter])
	{
		if (buff[*counter] == '\n')
		{
			*counter = *counter + 1;
			add_back_n(bank, ft_substr(buff, st_c, *counter - st_c), 0);
			return (1);
		}
		*counter = *counter + 1;
	}
	if (*counter != st_c)
		add_back_n(bank, ft_substr(buff, st_c, *counter - st_c), 0);
	*counter = 0;
	return (0);
}

void	ft_lstclear_gnl(t_gnl **lst)
{
	t_gnl	*tmp;

	tmp = *lst;
	if (lst && *lst)
	{
		while (tmp)
		{
			tmp = (*lst)->next;
			free ((*lst)->buff);
			free (*lst);
			*lst = tmp;
		}
	}
}

static char	*ret_res(t_gnl *bank)
{
	t_gnl	*tmp;
	long	len;
	char	*res;

	tmp = bank;
	len = 0;
	while (tmp)
	{
		len = len + ft_strlen(tmp->buff);
		tmp = tmp->next;
	}
	if (!len)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	*res = '\0';
	tmp = bank;
	while (tmp)
	{
		ft_strlcat(res, tmp->buff, len + 1);
		tmp = tmp->next;
	}
	ft_lstclear_gnl(&bank);
	return (res);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	static long		i;
	long			byte;
	t_gnl			*fd_bank;

	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		fd_bank = NULL;
		while (1)
		{
			if (!i)
			{
				byte = read(fd, buff, BUFFER_SIZE);
				if (byte <= 0)
					break ;
				buff[byte] = '\0';
			}
			if (checkbuff(buff, &fd_bank, &i))
				break ;
		}
		return (ret_res(fd_bank));
	}
	return (NULL);
}
