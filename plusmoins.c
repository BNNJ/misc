#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
**	C'est basique et un peu bancal, mais dans l'esprit de l'exercice je pense.
**	C'est plein de failles, je comprends pas tout à propos du 
**	comportement de scanf (voir les commentaires suivants), mais bon. 
*/

/*
**	do while basique, comme la solution proposée dans le cours.
**	la variable try compte le nombre d'essais
**	un printf affiche le nombre de coups, 
**	et un ternaire modifie l'affichage : "try" pour un coup, "tries" sinon.
**	scanf caramélise complètement si on lui passe autre chose qu'un nombre,
**	le problème est probablement réglable en passant par une chaine de caractère
**	et atoi(), mais ça sort du cadre de l'exercice.
**	bref je laisse comme ça, et ça bouclera vers l'infini et au delà à chaque fois
**	qu'un joueur essayera de passer autre chose que des digits.
*/

void	fct_play(int mystery_nb)
{
	int	input = 0, try = 0;

	do
	{
		printf("Enter a number :\n");
		scanf("%d", &input);
		++try;
		if (input == mystery_nb)
			printf("Well played ! You guessed in %d tr%s !\n",
				try, try == 1 ? "y" : "ies");
		else
			printf("Too %s\n", input > mystery_nb ? "high" : "low");
	} while (input != mystery_nb);
}

/*
**	un char simple pour passer l'option du nombre de joueurs, 
**	à noter que n'importe quoi d'autre que 2 passe le mode en single player.
**	Modifiable en ajoutant une clause à la structure conditionelle,
**	mais franchement c'est mieux comme ça.
**	Il ne boucle pas à l'infini si on passe autre chose qu'un digit, puisque
**	scanf prend un char plutot qu'un int. Contrairement à la difficulté...
**	Qui elle est passée en int, pout avoir l'option  de choisir sa 
**	propre valeur max, en entrant autre chose qu'un niveau de difficulté 
**	pré-établi.
*/

int		get_number(char	opt)
{
	int		number = 0;
	int		difficulty = 2;
	int		max = 100;

	if (opt == '1')
	{
		printf("Select a difficulty level.\n");
		printf("\t1: from 1 to 50\n\t2: from 1 to 100\n\t3: from 1 to 500\n\t4: from 1 to 1000\n\tor enter a custom max value\n");
		scanf("%d", &difficulty);
		if (difficulty == 1)
			max = 50;
		else if (difficulty == 2)
			max = 100;
		else if (difficulty == 3)
			max = 500;
		else if (difficulty == 4)
			max = 1000;
		else
			max = difficulty;
		number = rand() % max + 1;	// Genere un nombre entre 1 et max
	}
	else
	{
		printf("Pick a mystery number :\n");
		scanf("%d", &number);
	}
	return (number);
}

/*
**	Pas grand chose à expliquer ici à mon avis, 
**	à part la foret de printf. C'était juste pour éviter des lignes
**	de 300 caractères...
**	opt et play sont passés en caractères, pour éviter encore une fois les
**	conneries de scanf et %d.
**	Il sont scannés via %c et %s respectivement, je sais pas pourquoi mais play
**	avait un comportement très étrange si je le convertissait par %c.
**	J'ai aussi ajouté un max field (le 1 entre % et s ou c) pour ne prendre
**	que le premier caractère entré. Juste une petite sécurité.
**	Et encore un ternaire dans un printf, rien de méchant.
**	J'ai opté pour un simple if/else dans le cadre du choix du nombre de joueurs, 
**	et pour continuer/arreter la partie. L'alternative était de vérifier chacun
**	des deux choix, puis de renvoyer une erreur et redemander si l'option choisie
**	ne correspondait à aucun des choix proposés. 
**	c'est un peu plus clair comm ça je trouve, et scanf part de toute façon
**	en queue de hareng si on le met dans une boucle.
*/

int		main()
{
	char	opt = '1';
	char	play = '1';

	srand(time(NULL));
	printf("Welcome to Guess the Mystery Number !\n");
	while (opt != '1' && opt != '2')
	printf("Do you want to play alone or with a friend ?\n");
	printf("\t1: play alone\n\tanything else: play with a friend\n");
	scanf("%1c", &opt);
	while (play == '1')
	{
		fct_play(get_number(opt));
		printf("Do you want to play again ?\n");
		printf("\t1: play again\n\tanything else: stop\n");
		scanf("%1s", &play);
		printf(play == '1' ? "Let's play again !\n" : "Okay, byebye !\n");
	}
	return 0;
}
