# minishell

![gif_minishell](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExZjZjM2Q5MTBlYjQ5OTdhY2Q2Zjc4ZDJmOTlmNmQ0ZWMyODNiZjc4MyZlcD12MV9pbnRlcm5hbF9naWZzX2dpZklkJmN0PWc/mZ6A7RtfQRlIA3YUTW/giphy.gif)

Le projet Minishell consiste à créer un shell minimaliste en C qui peut interpréter des commandes simples.

Objectifs
Créer un shell qui peut afficher un prompt en attente d'une nouvelle commande
Posséder un historique fonctionnel
Chercher et lancer le bon exécutable en se basant sur la variable d'environnement PATH, ou sur un chemin relatif ou absolu
Ne pas utiliser plus d'une variable globale
Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule)
Gérer les single quotes (') qui doivent empêcher le shell d'interpréter les caractères spéciaux

Fonctions autorisées
Les fonctions suivantes sont autorisées pour le projet :

readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
printf, malloc, free, write
access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
Utilisation
Pour compiler le programme, vous pouvez utiliser le Makefile fourni en tapant la commande make.

Une fois le programme compilé, vous pouvez l'exécuter en tapant ./minishell.

Conclusion
Le projet Minishell a permis de développer des compétences en programmation en C, en particulier dans la manipulation de processus et de descripteurs de fichier. Cela a également permis de mieux comprendre le fonctionnement d'un shell et de mieux appréhender l'histoire de l'informatique.

N'oubliez pas de consulter le sujet complet du projet pour plus de détails sur les règles et les exigences.

