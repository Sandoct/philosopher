/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:06 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 18:07:23 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (write(2, "Error\n", 6));
	if (parser(argv))
		return (write(2, "Error prout\n", 11));
/*	if (argc == 3)
		if (philo(argv[1], argv[2], argv[3], -1))
			return (1);
	if (argc == 4)
		if (philo(argv[1], argv[2], argv[3], argv[4]))
			return (1);
*/	return (0);
}
