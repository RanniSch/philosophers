/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:41:56 by rschlott          #+#    #+#             */
/*   Updated: 2022/12/31 17:18:27 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/*
* prints out a message and returns 0 or 1 based on failure/success;
* Passes string from header prints out long sentence without multiple spaces;
char *infos is for debugging details;
*/
int	input_error_msg(char *str, char *infos, int exit_no)
{
	if (!infos)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, infos);
	return (exit_no);
}
