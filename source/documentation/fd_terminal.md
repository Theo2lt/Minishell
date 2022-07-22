## [isatty](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-isatty-test-if-descriptor-represents-terminal)

- Determine si un fd est associer ou non a un terminal.

#### Prototype

```c
#include POSIX_SOURCE
#include <unistd.h>

Int isatty(int fildes);
```

## [ttyname](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-ttyname-get-name-terminal)

- Return le nom du path du terminal de commande associer en parametre.

#### Prototype

```c
#define _POSIX_SOURCE
#include <unistd.h>

char *ttyname(int fildes);
```

## [ttyslot](https://docstore.mik.ua/manuals/hp-ux/en/B2355-60130/ttyslot.3C.html)

- renvoie l'index de l'entrée de l'utilisateur actuel dans le fichier /etc/utmpx . Ceci est accompli en scannant /etc/utmpx pour avoir le nom du terminal associé à l'entrée standard, la sortie standard ou l'erreur standard (descripteur de fichier 0, 1 ou 2).

#### Prototype

```c
#define _XOPEN_SOURCE_EXTENDED 1
#include <stdlib.h>

int ttyslot(void);
```

### resource complementaire

- [man](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
- [ibm](https://www.ibm.com/docs/en/zos/2.2.0?topic=lf-ttyslot-find-slot-in-utmpx-file-current-user)


## [ioctl](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-ioctl-control-device)

- cette fonction permet de controler les peripheriques, parmit les peripheriques on distinge les sockets, les streams et les terminaux. 

#### Prototype

```c
#define _XOPEN_SOURCE_EXTENDED 1 // cette inlcude n'est valide que pour le controle des terminaux
#include <stdlib.h>

int ttyslot(void);
```


## [tcsetattr](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-tcsetattr-set-attributes-terminal)

- Permet de modifier les attributs lier a un terminal, ces attribut vont inpacter la manier d'ont stdin et stdout se comporte.
- avant d'utiliser cette fonction il faut obtenir la structure terminos a l'aide de tcgetattr().

#### Prototype

```c
#define _POSIX_SOURCE
#include <termios.h>

int tcsetattr(int fd, int when, const struct termios *termptr);
```

## [tcgetattr](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-tcgetattr-get-attributes-terminal)

- perment d'obtenir une structure termios, qui va permettre de controler les atributs d'un terminal a l'aide tcsetattr.

```c
SIX_SOURCE
#include <termios.h>

Int tcgetattr(int fildes, struct termios *termptr);
```

## [Termcap](https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/)

- Termcap est une blibliotheque et une basse de donnees qui permet aux programe d'uttiliser des terminaux d'affichage.
- Voici un exellent [tutoriel](https://zestedesavoir.com/tutoriels/1733/termcap-et-terminfo/) qui d'ecrit comment utiliser Termcap.

### tgetent 
	- permet d'initialiser les informations utile aux fonctionement de termcap.

### tgetnum 
	- permet de recuperere des inforamations numerique en rapport avec votre terminal, commme le nombre de ligne ou de colonne.
	- man 2 termcap decrit les arguments qui permette de recuperrer ces informations numerique.

### tgetflag 
	- tgetflag fonctionne de la même manière que tgetnum à la différence prêt qu’il renvoie un booléen au lieu d’une valeur. Cette fonction est utilisée pour vérifier les capacités d’un terminal, savoir s’il est capable de faire tel ou tel action.

### tgetstr 
	- tgetstr permet de récupérer les fameux termcaps sous la forme d’une séquence d’échappement ! On peut par exemple récupérer le termcap « cl » (pour clean) qui permet de nettoyer (vider) un terminal.
	- tgetstr prend en deuxième paramètre l’adresse du buffer que l’on a utilisé pour tgetent, à savoir NULL. 

### tputs 
	- tputs est la fonction qui marche de pair avec tgetstr, c’est elle qui va se charger d’exécuter le termcap que l’on vient de récupérer.

### tgoto 
 	- permet de deplacer un curseur
