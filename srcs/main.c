/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:47:13 by adleau            #+#    #+#             */
/*   Updated: 2018/03/08 11:10:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <full_run.h>
#include <libft.h>

int		main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		mandatory_part(NULL, NULL);
	else if (ac == 2)
		mandatory_part(NULL, av[1]);
	return (0);
}
