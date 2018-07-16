/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:29:46 by lprior            #+#    #+#             */
/*   Updated: 2018/07/15 19:29:01 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int main(int argc, char **argv)
{
    char *string;

    string = (char *)malloc(sizeof(char) * 10);
    printf("done\n");
}