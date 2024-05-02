#include "minishell_lib.h"
#include <stdio.h>
int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	printf("ENV[0] : %s",envp[0]);	
}
