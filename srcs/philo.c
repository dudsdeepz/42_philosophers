/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:35:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/06 16:57:00 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void ft_philo(t_philo *philo)
{
	while (1)
	{
        pthread_mutex_lock(&philo->life);
        if (philo->is_dead)
        {
            pthread_mutex_unlock(&philo->life);
            return ;
        }
        pthread_mutex_unlock(&philo->life);
		forks(philo, 1);
		eating(philo);
		forks(philo, 0);
		sleeping(philo);
	}
	return ;
}

void eating(t_philo *philo)
{
    print_action(philo, "is eating");
    pthread_mutex_lock(&philo->food);
    philo->last_meal = gettime() - philo->status->starting_time;
    philo->eat_count++;
    pthread_mutex_unlock(&philo->food);
    wait(philo, philo->status->time_to_eat);
}
void sleeping(t_philo *philo)
{
    print_action(philo, "is sleeping");
    wait(philo, philo->status->time_to_sleep);
    print_action(philo, "is thinking");
}


void forks(t_philo *philo, int stats)
{
    // t_philo next;

    // if (status->philo->num < status->number_of_philosophers)
    //     next = status->philo[1];
    // else
    //     next = status->philo[-1 * (status->number_of_philosophers - 1)];
    if (stats)
    {
        pthread_mutex_lock(&philo->fork_right);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
    }
    else if (!stats)
    {
        pthread_mutex_unlock(&philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
    }
}

void wait(t_philo *philo, time_t time)
{
    time_t start;
    time_t current;

    start = gettime();
    usleep(time);
    while (1)
    {
        pthread_mutex_lock(&philo->life);
        if (philo->is_dead)
        {
            pthread_mutex_unlock(&philo->life);
            return ;
        }
        pthread_mutex_unlock(&philo->life);
        current = gettime();
        if (current - start >= time)
            break ;
    }
}

long long gettime(void)
{
    struct timeval current_time;


    if (gettimeofday(&current_time, NULL) < 0)
        return (0);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void print_action(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->life);
    if (philo->is_dead)
    {
        pthread_mutex_unlock(&philo->life);
        return ;
    }
    pthread_mutex_unlock(&philo->life);
    printf("%s%lli %s%i %s %s\n", YELLOW, (gettime() - philo->status->starting_time)
    , RED, philo->num, DEFAULT, str);
}

void free_all(t_philo *philo)
{
    int i;

    i = -1;
    while (++i < philo->status->number_of_philosophers)
    {
            pthread_mutex_destroy(&philo[i].fork_right);
    }
    pthread_mutex_destroy(&philo->food);
    pthread_mutex_destroy(&philo->life);
    if (philo)
        free(philo);
    philo = NULL;
}
