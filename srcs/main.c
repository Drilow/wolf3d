/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:47:13 by adleau            #+#    #+#             */
/*   Updated: 2018/03/15 15:20:42 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <full_run.h>
#include <libft.h>
#include <fcntl.h>

int		check_arg(char *arg)
{
	int		ret;
	char	*buff;
	int		fd;

	if (!(fd = open(arg, O_RDONLY)))
		return (0);
	buff = (char*)malloc(sizeof(char) * 32000);
	if ((ret = read(fd, buff, 32000)) <= 0)
	{
		free(buff);
		return (0);
	}
	if (strncmp(buff, "{", 1))
	{
		free(buff);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		mandatory_part(NULL, NULL);
	else if (ac == 2)
	{
		if (check_arg(av[1]))
			mandatory_part(NULL, av[1]);
	}
	return (0);
}
