/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:45:32 by gpouzet           #+#    #+#             */
/*   Updated: 2023/06/08 17:55:06 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n-- && (*s1 || *s2))
		if (*s1++ != *s2++)
			break ;
	return ((unsigned char)*--s1 - (unsigned char)*--s2);
}

static size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

static int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (1);
	return (0);
}

static int	ft_isnumber(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
		if (ft_isdigit(*str++))
			return (1);
	return (0);
}

int	parser(char **arg)
{
	int		i;

	while (*(++arg))
	{
		if (ft_isnumber(*arg))
			return (1);
		i = 0;
		if (**arg == '-' || **arg == '+')
			i++;
		while (*(*arg + i) == '0')
			i++;
		if (**arg == '-' && ft_strlen(*arg + i) >= 10)
			if (0 < ft_strncmp(*arg + i, "2147483648", 11))
				return (1);
		if (**arg != '-' && ft_strlen(*arg + i) >= 10)
			if (0 < ft_strncmp(*arg + i, "2147483647", 11))
				return (1);
	}
	return (0);
}
