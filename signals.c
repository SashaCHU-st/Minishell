/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-05 15:25:17 by epolkhov          #+#    #+#             */
/*   Updated: 2024-07-05 15:25:17 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void signal_handler(int signal)
{
    if (signal == SIGINT) //cntr-C
    {
        write(1, "\n", 1);
        write(1, "^C\n", 3);
        
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

static void hd_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        write(1, "^C\n", 3);
        rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
		rl_redisplay();
        // write (1, "\n", 1);
        // exit (1);
    }
}

static void toggle_caret(int is_on)
{
    struct termios new_attr;

    if (tcgetattr(STDIN_FILENO, &new_attr) == -1)
        error_message("tcgetattr in signals failed");
    if (!is_on)
        new_attr.c_lflag &= ~ECHOCTL;
    else
        new_attr.c_lflag |= ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) == -1)
        error_message ("tcsetattr in signals failed");
}

static void	set_signal_handler(int signum, void(*handler)(int))
{
	struct	sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(signum, &sa, NULL) == -1)
        error_message("Sigaction failed");
}

void    get_signal(t_signal mode)
{
    if (mode == DEFAULT)
    {
        toggle_caret(1);
        set_signal_handler(SIGQUIT, SIG_DFL);
        set_signal_handler(SIGINT, SIG_DFL);
    }
    else if (mode == HANDLER)
    {
        toggle_caret(0);
        set_signal_handler(SIGQUIT, SIG_IGN);
        set_signal_handler(SIGINT, signal_handler);
    }
    else if (mode == HEREDOC)
    {
        set_signal_handler(SIGQUIT, SIG_IGN);
        set_signal_handler(SIGINT, hd_handler);
    }
    else
    {
        set_signal_handler(SIGQUIT, SIG_IGN);
        set_signal_handler(SIGINT, SIG_IGN);
    }
}
