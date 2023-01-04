/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:41:56 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/04 22:04:36 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* destroys mutexes by uninitializing them */
void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->eat_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->do_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

/* frees allocated memory and returns NULL */
void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
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
or any of its included	variables;
frees memory via	free_table(void) */
void	*error_null(char *str, char *infos, t_table *table)
{
	if (table != NULL)
		free_table(table);
	input_error_msg(str, infos, EXIT_FAILURE);
	return (NULL);
}

/* error management;
frees allocated memory and returns 0 indicating failure */
int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (input_error_msg(str, details, 0));
}
