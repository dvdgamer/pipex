/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: dponte <dponte@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/07/11 13:58:49 by dponte       #+#    #+#                  */
/*   Updated: 2025/09/02 00:05:51 by dponte       ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Need to get the env variables by splitting $PATH through :
int	main(int argc,char *argv[], char *env[])
{
	char *cmd1;
	char *cmd2;
	char *file1;
	char *file2;
	int fd;
	int	pipefd[2];

	/* 1 -> process commands */
	file1 = argv[1];
	file2 = argv[4];
	cmd1 = argv[2];
	cmd2 = argv[3];

	/* open pipe */
	if (pipe(pipefd) < 0)
		exit(1);
	/* open file1 */
	printf("pipe opened\n");
	fd = open_file(file1);
	/* pipe it into file2 */

	/* close pipe */
	close(fd);
	return (0);
}

/* second step -> replicate > and < commands */
/* 3rd step -> run commands */
