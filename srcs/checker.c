/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:33:14 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/12 18:46:00 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_things(void)
{
    pthread_mutex_lock(&status()->life);
    pthread_mutex_lock(&status()->food);
    if (status()->is_dead || status()->is_full)
    {
        pthread_mutex_unlock(&status()->food);
        pthread_mutex_unlock(&status()->life); 
        return (1);
    }
    pthread_mutex_unlock(&status()->food);
    pthread_mutex_unlock(&status()->life);
    return (0);
}

void check_dead(t_philo *philo)
{
    int current;

    current = gettime() - status()->starting_time;
    pthread_mutex_lock(&status()->life);
    pthread_mutex_lock(&status()->food);
    if (status()->is_dead || status()->is_full)
    {
        pthread_mutex_unlock(&status()->food);
        pthread_mutex_unlock(&status()->life);
        return ;
    }
    if (current - philo->last_meal >= status()->time_to_die)
    {
        pthread_mutex_unlock(&status()->food);
        status()->is_dead = 1;
        printf("%s%i %s%i %s %s\n", YELLOW, current
            , RED, status()->philo->num, DEFAULT, "has died");
        pthread_mutex_unlock(&status()->life);
        return ;
    }
    pthread_mutex_unlock(&status()->food);
    pthread_mutex_unlock(&status()->life);
    return ;
}

void check_full(void)
{
    int i;
    int counter;
    
    i = 0;
    counter = 0;
    pthread_mutex_lock(&status()->food);
    if (status()->is_full || status()->number_of_times_each_philosopher_must_eat == -1)
    {
        pthread_mutex_unlock(&status()->food);
        return ;
    }
    while (i < status()->number_of_philosophers)
    {
        if (status()->philo[i].eat_count >= status()->number_of_times_each_philosopher_must_eat)
            counter++;
        i++;
    }
    if (counter == status()->number_of_philosophers)
        status()->is_full = 1;
    counter = 0;
    pthread_mutex_unlock(&status()->food);
    return ;
}

void fork_take(t_philo *philo, int condition)
{
    if (condition == 1)
    { 
        pthread_mutex_lock(&philo->fork_right);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->fork_left);
        print_action(philo, "has taken a fork");
        return ;
    }
    else{
        pthread_mutex_lock(philo->fork_left);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->fork_right);
        print_action(philo, "has taken a fork");
        return ;
    }
}

void fork_leave(t_philo *philo, int condition)
{
    if (condition == 1)
    { 
        pthread_mutex_unlock(&philo->fork_right);
        pthread_mutex_unlock(philo->fork_left);
        return ;
    }
    else{
        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(&philo->fork_right);
        return ;
    }
}