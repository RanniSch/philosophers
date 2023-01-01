/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:41:56 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/01 20:00:04 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* frees allocated memory and returns NULL */
void	*free_table(t_table *table)
{
	if (!table)
		return (NULL);
	free(table);
	return (NULL);
}

/* prints out a message and returns 0 or 1 based on failure/success;
Passes string from header prints out long sentence without multiple spaces;
char *infos is for debugging details */
int	input_error_msg(char *str, char *infos, int exit_no)
{
	if (!infos)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, infos);
	return (exit_no);
}

/* error function for any errors during initialization of table struct
or any of its included variables;
frees memory via free_table() */
void	*error_null(char *str, char *infos, t_table *table)
{
	if (table != NULL)
		free_table(table);
	input_error_msg(str, infos, EXIT_FAILURE);
	return (NULL);
}
