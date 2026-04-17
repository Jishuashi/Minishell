/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_explained.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:00:00 by louka             #+#    #+#             */
/*   Updated: 2026/04/17 12:00:00 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On importe les definitions du minishell et les fonctions utiles. */
#include "includes/minishell.h"

/* Flag global mis a jour quand on recoit Ctrl+C. */
volatile sig_atomic_t	g_signal;

/* Le handler de SIGINT interrompt la saisie et rafraichit le prompt. */
static void	on_sigint(int signum)
{
	/* Le parametre est inutile ici, on l'ignore proprement. */
	(void)signum;
	/* On memorise qu'un SIGINT a ete recu. */
	g_signal = SIGINT;
	/* On saute a la ligne pour garder un affichage propre. */
	write(1, "\n", 1);
	/* On indique a readline qu'on passe a une nouvelle ligne. */
	rl_on_new_line();
	/* On vide la ligne courante pour annuler la saisie. */
	rl_replace_line("", 0);
	/* On affiche de nouveau le prompt. */
	rl_redisplay();
}

/* Cette fonction configure le comportement du terminal et des signaux. */
static void	setup_signals(void)
{
	/* Structure pour configurer SIGINT. */
	struct sigaction	sa_int;
	/* Structure pour configurer SIGQUIT. */
	struct sigaction	sa_quit;
	/* Structure termios pour modifier l'affichage du terminal. */
	struct termios		term;

	/* On lit la configuration actuelle du terminal. */
	tcgetattr(STDIN_FILENO, &term);
	/* On desactive l'affichage des caracteres de controle comme ^C. */
	term.c_lflag &= ~ECHOCTL;
	/* On applique la nouvelle configuration du terminal. */
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	/* On met la structure SIGINT a zero avant de l'utiliser. */
	ft_bzero(&sa_int, sizeof(sa_int));
	/* On met la structure SIGQUIT a zero avant de l'utiliser. */
	ft_bzero(&sa_quit, sizeof(sa_quit));
	/* On associe SIGINT a notre fonction de traitement. */
	sa_int.sa_handler = on_sigint;
	/* On vide le masque de signaux bloque pendant le handler. */
	sigemptyset(&sa_int.sa_mask);
	/* On ignore SIGQUIT pour eviter la fermeture avec Ctrl+\\. */
	sa_quit.sa_handler = SIG_IGN;
	/* On vide aussi le masque de SIGQUIT. */
	sigemptyset(&sa_quit.sa_mask);
	/* On installe la gestion de SIGINT. */
	sigaction(SIGINT, &sa_int, NULL);
	/* On installe l'ignorance de SIGQUIT. */
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/* Cette fonction renvoie le texte affiche avant chaque saisie. */
const char	*get_prompt(void)
{
	/* Le prompt reste simple et fixe. */
	return ("minishell> ");
}

/* Cette fonction contient la boucle principale de lecture du shell. */
int	shell_loop(void)
{
	/* Pointeur vers la ligne lue avec readline. */
	char	*line;

	/* On prepare les signaux avant de commencer la boucle. */
	setup_signals();
	/* Boucle infinie de lecture des commandes. */
	while (1)
	{
		/* On affiche le prompt et on lit une ligne. */
		line = readline(get_prompt());
		/* Si Ctrl+C a ete recu, on nettoie et on recommence. */
		if (g_signal == SIGINT)
		{
			/* On remet le flag a zero pour la prochaine iteration. */
			g_signal = 0;
			/* On libere la ligne qui n'a pas ete exploitee. */
			free(line);
			/* On recommence la boucle sans traiter la saisie. */
			continue ;
		}
		/* Si readline renvoie NULL, cela veut dire EOF ou sortie du terminal. */
		if (!line)
		{
			/* On affiche exit comme un shell classique. */
			ft_printf("exit");
			/* On sort de la boucle. */
			break ;
		}
		/* Si la ligne n'est pas vide, on l'ajoute a l'historique. */
		if (line[0] != '\0')
			add_history(line);
		/* On libere la memoire apres utilisation. */
		free(line);
	}
	/* La fonction se termine normalement. */
	return (0);
}

/* Point d'entree du programme. */
int	main(void)
{
	/* On initialise le flag de signal a l'etat neutre. */
	g_signal = 0;
	/* On lance la boucle interactive du shell. */
	shell_loop();
	/* Le programme se termine sans erreur. */
	return (0);
}