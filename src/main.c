/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:30:42 by rschlott          #+#    #+#             */
/*   Updated: 2022/12/31 17:41:47 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int main(int argc, char **argv)
{
    //t_table *table;

    //table = NULL;
    (void)argv;
    if (argc != 5 && argc != 6)
        return (input_error_msg(STR_INPUT_FORMAT, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (EXIT_FAILURE);
    return (0);
}
