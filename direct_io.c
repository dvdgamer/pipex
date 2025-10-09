/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   direct_io.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/10/08 15:51:01 by dponte       #+#    #+#                  */
/*   Updated: 2025/10/08 15:56:38 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
#include <unistd.h>
void	create_pipe(char **argv, char **paths)
{
	int	i;
	int	pipefd[2];

	pipe(pipefd);

	printf("0%d\n", pipefd[0]);
	printf("1%d\n", pipefd[1]);
	while (argv != NULL)
	{
		// Create a pipe
		//Execute the function
	}
}

//Dup2 the result as stdin for the next function
// If it can't find a path it'll look for it in the current directory
