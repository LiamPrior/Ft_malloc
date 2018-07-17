/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprior <lprior@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:29:46 by lprior            #+#    #+#             */
/*   Updated: 2018/07/16 22:32:12 by lprior           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int main(int argc, char **argv)
{
    char *string;

    string = (char *)malloc(sizeof(char) * 2049);
    printf("done\n");
}