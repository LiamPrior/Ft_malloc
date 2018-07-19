/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liamprior <liamprior@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:41:38 by lprior            #+#    #+#             */
/*   Updated: 2018/07/18 21:03:12 by liamprior        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_malloc.h"


void			*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};

void    create_next_page(t_meta **meta, void **given_block, int page_size)
{
    void *tmp;

    if ((tmp = mmap(NULL, page_size, PROT_ALL, FT_MAP_ANON, -1, 0)))
    {
        (*meta)->next = tmp;
        (*meta)->check = chksum(*meta);
        *given_block = tmp;
        (*meta) = (t_meta *)(*given_block);
    }
}

void    *ft_alloc(size_t page_size, size_t req_size, int thread_num)
{
    pthread_mutex_t *thread_block;
    void **given_block;
    void *void_page;
    t_meta *meta;

    given_block = &(g_pages[thread_num]);
	thread_block = &(g_mutex[thread_num]);
    pthread_mutex_lock(thread_block);//so this singles it down to one thread because if there are two it can fuck up the time schedule its doing things.
    if ((!*given_block) && given_block = mmap(NULL, page_size, PROT_ALL, MAP_PERMS, -1, 0) == MAP_FAILED);//could be a problem becuz it may need to be 2 ifs
        return (NULL);
    meta = (t_meta *)*given_block;
    while (meta && (void *)meta < (*given_block + page_size))
    {
        if (meta->free)
        {
            meta->start_addr = given_block;
            if (!meta->size)//i need to see if i can fit my meta into the zone
            {
                if (void_page + req_size + sizeof(t_meta) <= (*given_block + page_size) && (void_page = meta))
                {
                    meta->free = false;
                    meta->size = req_size;
                    if (void_page + req_size + sizeof(t_meta) <= *given_block + page_size - sizeof(t_meta))
                    {    
                        ((t_meta *)(void_page) + req_size + sizeof(t_meta))->next = meta->next;//may be able to just set it to NULL
                        meta->next = NULL;
                    }
                }
                else if (meta->next)
                {
                    *given_block = meta->next;
                    meta = (t_meta *)*given_block;
                    continue ;
                }
                create_next_page(&meta, given_block, page_size);//should only hit this if its a large alloc
                continue ;
            }
            else//this below is weird becuase i would have to continue on every elseif
            {
                if (meta->size >= req_len)
                    meta->free = false;
                else if (meta->next)//continue
                {
                    *given_block = meta->next;
                    meta = (t_meta *)*given_block;
                }
                else if ((meta + req_size + sizeof(t_meta)) < (*given_block + page_size))//i may need to cast meta to a void *
                    meta += req_size + sizeof(t_meta);
                else
                    create_next_page(&meta, given_block, page_size);
            }
        }
    }
}

void    *ft_malloc(size_t req_size)
{
    static int zone_size = 0;
    size_t  page;
    int     thread_num;
    t_alloc *alloc;
    t_meta *meta;

    if (!zone_size)
        zone_size = getpagesize();
    if (!req_size)
        return (NULL);
    else if (req_size <= TINY && (thread_num = 0))
        (page = (TINY + sizeof(meta)) * 300)
    else if (req_size <= SMALL && size > TINY && (thread_num = 1))
        page = (SMALL + sizeof(meta)) * 300;
    else if ((thread_num = 2))
        page = req_size + sizeof(meta);
    page += (page % zone_size);
     return (thread_num < 2 ? ft_alloc(page, req_size, thread_num)
            : ft_alloc_large(page, req_size,thread_num));
}

int main(void)
{
    char *str;

    str

    printf("%lu\n", sizeof(x));    
}