/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:56:06 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/21 19:41:59 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (write(2, "Error\n", 6));
	if (parser(argv))
		return (write(2, "Error prout\n", 11));
	if (philo(argv))
		return (1);
	return (0);
}
