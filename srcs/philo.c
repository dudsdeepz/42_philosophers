/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/06/23 14:57:14 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo (t_status status)
{
    pthread_t *philo;
    int        i;

    philo = malloc(sizeof(pthread_t) * status.number_of_philosophers);\
    while (i <= status.number_of_philosophers)
    {
        pthread_create(&philo[i], NULL, );
    }
}