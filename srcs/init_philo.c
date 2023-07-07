/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:20:22 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/07 15:48:07 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo (t_all *all, t_status *status, t_philo *philo)
{
	all->philo = philo;
	all->status = status;
    init_mutex(all);
    init_philo(all);
}

void init_philo(t_all *all)
{
    int i;

    i = -1;
    while (++i < all->status->number_of_philosophers)
    {
        if(pthread_create(&all->philo[i].philosophers, NULL, (void *)ft_philo, &all->philo[i]))
            return ;
    }
    end_join(all);
}

void init_mutex(t_all *all)
{
    int i;

    i = 0;
    all->philo = malloc(sizeof(t_philo) * all->status->number_of_philosophers);
    if (pthread_mutex_init(&all->philo->life, NULL)
        || pthread_mutex_init(&all->philo->food, NULL))
            return ;
    while (i < all->status->number_of_philosophers)
    {
        all->philo[i].eat_count = 0;
        all->philo[i].last_meal = gettime();
        all->philo[i].num = i + 1;
        all->philo[i].status = all->status;
		all->philo[i].is_dead = 0;
		all->philo[i].status->starting_time = gettime();
        if(pthread_mutex_init(&all->philo[i].fork_right, NULL))
            return ;
        if (i == 0)
            all->philo[i].fork_left  = &all->philo[all->status->number_of_philosophers - 1].fork_right;
        else
		{
	    	all->philo[i].fork_left  = &all->philo[i - 1].fork_right;
		}
		i++;
	}
}

void end_join(t_all *all)
{
    int i = -1;

    if (all->philo->philosophers)
    {
        while (++i < all->status->number_of_philosophers)
            pthread_join(all->philo[i].philosophers, NULL);
    }
    free(all->philo);
    all->philo = NULL;
}
