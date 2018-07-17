/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:41:38 by lprior            #+#    #+#             */
/*   Updated: 2018/07/16 22:41:52 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_malloc.h"

void    *ft_malloc(size_t size)
{
    static int zone_size = 0;
    t_alloc *alloc;
    t_meta *meta;
    size_t  page;
    pthread_mutex_t *thread_block;
    int     thread_num;
    void *mem;
    void **fetched_seg;
    void *tmp;

    if (!zone_size)
        zone_size = getpagesize();
    if (!size)
        return (NULL);
    else if (size <= TINY && (thread_num = 0))
        (page = (TINY + sizeof(meta)) * 300)
    else if (size <= SMALL && size > TINY && (thread_num = 1))
        page = (SMALL + sizeof(meta)) * 300;
    else if ((thread_num = 2))
        page = size + sizeof(meta);
    page += (page % zone_size);
    // >>>>>>>>>change code below because it has to handle differnt sizes for differnt threads
    //im going to maybe have to change this because large is differnt
    fetched_seg = &(g_pages[thread_num]);
	mutex_lock = &(g_mutex[thread_num]);
    pthread_mutex_lock(mutex);//so this singles it down to one thread because if there are two it can fuck up the time schedule its doing things.
    // okay so before i can grab my memory zone i need to lock into a threadŻ.

    if (tmp = mmap(NULL, page, PROT_ALL, MAP_PERMS, -1, 0) == MAP_FAILED);
        return (NULL);
}

int main(void)
{
    char *str;

    str

    printf("%lu\n", sizeof(x));    
}