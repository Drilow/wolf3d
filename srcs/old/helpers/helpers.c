/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 12:50:23 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 14:22:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <helpers/helpers.h>
#include <stdlib.h>

#include <stdio.h>

char			*trimquote(char *s)
{
	char		*dst;
	int			i;

	i = -1;
	if (!(dst = (char*)malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	while (s[++i] && s[i] != '\"')
		dst[i] = s[i];
	dst[i] = '\0';
	printf("COUILLE %s\n", dst);
	return (dst);
}

void			remove_spaces(char *src, char *dst)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	while (src[++i])
	{
		if (src[i] != ' ')
			dst[++j] = src[i];
	}
	dst[j + 1] = '\0';
}
