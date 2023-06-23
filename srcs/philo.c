/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/23 16:43:31 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void* ft_test(void *statuss)
{
    t_status *status = statuss;

    printf("philosopher %i has %f miliseconds till he dies\n", status->philosophers, status->time_to_die);
    return (0);
}

void philo (t_status status)
{
    pthread_t *philos;

    status.philosophers = 1;;
    philos = malloc(sizeof(pthread_t) * status.number_of_philosophers);
    while (status.philosophers <= status.number_of_philosophers)
    {
        pthread_create(&philos[status.philosophers], NULL, ft_test, &status);
        pthread_join(philos[status.philosophers], NULL);
        status.philosophers++;
    }
}