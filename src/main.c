/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:06 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/23 14:21:16 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error\n", 6));
	if (parser(argv))
		return (write(2, "Error wrong numbers of argument\n", 11));
	if (philo(argv))
		return (1);
	return (0);
}
