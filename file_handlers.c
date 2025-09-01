/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   file_handlers.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/09/01 23:56:55 by dponte       #+#    #+#                  */
/*   Updated: 2025/09/02 00:01:21 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

void	open_file(char* file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	printf("%u\n", fd);
}
