/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:30:42 by rschlott          #+#    #+#             */
/*   Updated: 2023/01/02 12:41:31 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void stop_simulation(t_table *table)
{
    destroy_mutexes(table);
    free_table(table);
}

/* First check if input is valid;
then the process gets initialized before simulation starts;
after simulation gets stopped; 
EXIT_SUCCESS is defined as 0 and EXIT_FAILURE as 8 */
int main(int argc, char **argv)
{
    t_table *table;

    table = NULL;
    (void)argv;
    if (argc != 5 && argc != 6)
        return (input_error_msg(STR_INPUT_FORMAT, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (EXIT_FAILURE);
    table = init_process(argc, argv);
    if (!table)
        return (EXIT_FAILURE);
    //if (!start_simulation(table))
    //    return (EXIT_FAILURE);
    stop_simulation(table);
    return (EXIT_SUCCESS);
}
