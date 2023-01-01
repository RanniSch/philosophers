/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:36:12 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/01 19:59:58 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* checks if the string has only numbers. 
static: is limited to its object file; no change possible;
static functions are not declared in the headerfile because
a static function is only visible in the file where its declared in
and thus can only be used there */
static bool input_digits(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

/* Convert a string to an integer. The behavior is the same as 
strtol (The string may begin with an arbitrary amount of white 
space followed by a single optional '+' or '-'  sign.) */
int	ft_atoi(const char *str)
{
	int			sign;
	long int	convert;

	sign = 1;
	convert = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str && *str > 47 && *str < 58)
	{
		convert = (convert * 10) + *str - '0';
		str++;
		if (convert > 2147483647 && sign == 1)
			return (-1);
		if (convert > 2147483648 && sign == -1)
			return (-1);
	}
	return (convert * sign);
}

bool    is_valid_input(int argc, char **argv)
{
    int i;
    int nb;

    i = 0;
    while (++i < argc)
    {
        if (!input_digits(argv[i]))
            return (input_error_msg(STR_ERR_INPUT_DIGIT, argv[i], false));
        nb = ft_atoi(argv[i]);
        if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
            return (input_error_msg(STR_ERR_INPUT_PHILO, STR_MAX_PHILOS, false));
        if (i != 1 && nb == -1)
            return (input_error_msg(STR_ERR_INPUT_DIGIT, argv[i], false));
    }
    return (true);
}
