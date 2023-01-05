/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:29:51 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/05 21:44:33 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* prints out what the respective philo is doing at the current timestamp */
static void	print_status(t_philo *philo_struct, char *str)
{
	printf("%ld p_%d %s\n", time_in_ms() - philo_struct->table->start_time, \
			philo_struct->id + 1, str);
}

/* prints out what a philo does; 
must be locked by mutex to prevent mixing of messages */
void	write_status(t_philo *philo_struct, bool tf, t_status status)
{
	pthread_mutex_lock(&philo_struct->table->write_lock);
	if (has_simulation_stopped(philo_struct->table) == true && tf == false)
	{
		pthread_mutex_unlock(&philo_struct->table->write_lock);
		return ;
	}
	if (status == DIED)
		print_status(philo_struct, "died");
	else if (status == EATING)
		print_status(philo_struct, "is eating");
	else if (status == SLEEPING)
		print_status(philo_struct, "is sleeping");
	else if (status == THINKING)
		print_status(philo_struct, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
	{
		print_status(philo_struct, "takes a fork");
	}
	pthread_mutex_unlock(&philo_struct->table->write_lock);
}
