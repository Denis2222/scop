/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvise.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 05:14:51 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/05/29 09:10:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGVISE_H
# define ARGVISE_H

typedef struct		s_argvise
{
	char			**files;
	int				i;
	int				j;
	int				nfiles;
	int				argc;
	char			**argv;
	char			*flags;
}					t_argvise;

t_argvise			*new_argvise(int argc, char **argv);

#endif
