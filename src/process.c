/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:36:55 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/01 20:12:05 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

/* puts values to variables */
t_table *init_process (int argc, char **argv)
{
    t_table *table;
    int i;

    i = 1;
    table = malloc(sizeof(t_table));
    if (!table)
        return (error_null(STR_ERR_MALLOC, NULL, 0));
    table->nb_philos = ft_atoi(argv[i]);
	i++;
	table->time_to_die = ft_atoi(argv[i]);
	i++;
	table->time_to_eat = ft_atoi(argv[i]);
	i++;
	table->time_to_sleep = ft_atoi(argv[i]);
	i++;
	table->must_eat_count = -1;
    if (argc == 6)
		table->must_eat_count = ft_atoi(argv[i]);
    // fehlt noch was
    printf("philos: %d, time to die %ld, time to eat %ld, time to sleep %ld, must eat %d.\n", table->nb_philos, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->must_eat_count);
    return (table);
}
