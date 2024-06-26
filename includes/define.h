/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 17:06:33 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ZERO_INIT 0
# define NULL_INIT 0
# define COMMAND_NOT_FOUND 1
# define UNCLOSED_QUOTES 2
# define SYNTAX_ERROR 3
# define UNEXPECTEDTOKEN 8

# define STDINS 4
# define STDOUTS 5
# define HEREDOCS 6
# define APPEND 7
# define BUFFER_SIZE 1024

#define GENERAL_ERRORS 1
#define MISUSE_BULTINS 2
#define CMD_INVOKED_CANTEXEC 126 
#define CMD_NOT_FOUND 127
#define INVALID_ARG_EXIT 128

enum {
    ENV,
    CMD,
    PWD,
    CD,
    EXPORT,
    UNSET,
    ECHO,
};

/*     Exit code 1: General errors, such as “divide by zero” and other impermissible operations
    Exit code 2: Misuse of shell builtins, according to Bash documentation
    Exit code 126: Command invoked cannot execute
    Exit code 127: “command not found”
    Exit code 128: Invalid argument to exit
    Exit codes 128+n: Fatal error signal “n”*/

#endif
