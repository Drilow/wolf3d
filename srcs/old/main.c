/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:47:13 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 13:02:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		full_run();
	else if (ac == 2)
	{
		if (!ft_strcmp(av[1], "mandatory_part"))
			mandatory_part();
		else if (!ft_strcmp(av[1], "bonus"))
			bonus();
		else
			ft_putendl_fd("Usage : ./wolf3d [mandatory_part | bonus] (optional flags)", 2);
	}
	else
		ft_putendl_fd("Usage : ./wolf3d [mandatory_part | bonus] (optional 	flags)", 2);
	return (0);
}
