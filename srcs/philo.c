/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/12 18:46:52 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_philo(t_philo *philo)
{
    if (status()->number_of_philosophers == 1)
    {
        print_action(philo, "has taken a fork");
        print_action(philo, "has died");
        return;
    }
    while (1)
    {
        check_dead(philo); 
        if(check_things())
            return ;
        forks(philo, 1);
        eating(philo);
        forks(philo, 0);
        sleeping(philo);
    }
    return;
}

void eating(t_philo *philo)
{
    print_action(philo, "is eating");
    pthread_mutex_lock(&status()->food);
    philo->last_meal = gettime() - status()->starting_time;
    philo->eat_count += 1;
    pthread_mutex_unlock(&status()->food);
    wait(philo, status()->time_to_eat);
}

void sleeping(t_philo *philo)
{
    check_full();
    check_dead(philo); 
    print_action(philo, "is sleeping");
    wait(philo, status()->time_to_sleep);
    print_action(philo, "is thinking");
}

void forks(t_philo *philo, int stats)
{
    if (stats)
    {
        if (philo->num % 2 == 0)
            fork_take(philo, 1);
        else
            fork_take(philo, 0);
        return ;
    }
    else if (!stats)
    {
        if (philo->num % 2 == 0)
            fork_leave(philo, 0);
        else
            fork_leave(philo, 1);
        return ;
    }
}

void wait(t_philo *philo, time_t time)
{
    time_t start;
    time_t current;
        
    start = gettime();
    while (1)
    {
        check_dead(philo);
        if(check_things())
            return ;
        current = gettime();
        if (current - start > time)
            return ;
    }
    return ;
}
