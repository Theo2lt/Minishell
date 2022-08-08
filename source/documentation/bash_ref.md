## C'est quoi le shell ? 

- Bash (Bourn again shell) c'est le shell de base des systeme unix.
- Le shell est un interpreteur de commande, il agit comme une interface entre le user et le noyaux.
- il permet d'excuter des commandes, qui peuvent etre soit des utilitaires installer sur le systeme, soit des commandes intergrer directement dans le shell.
- Le shell bash est aussi un language de programamtion, ce si permet de pousser utilisation du shell, et de realiser des tache complexe.

### Syntaxe du shell 

```c
$ cat file     |          kls -al       |           wc -l 
     ^         ^          ^             ^    	    ^  
    mot       operateur   mot           operateur   mot
```

### Cas a gerer pour Minishell 

- Ici le cat n'est pas excuter, car le '#' est interpreter comme un commentaire.

#### Commentaire 

```bash
$ ls #cat 
```
#### Single quote, Double quote et '\'

- Entre quote le \n est traiter comme un retour a ligne.
- Sans quote le \ va interprete le charactere suivant de maniere 
literale, il va iniber sa fonction si c'est in charactere special.

##### \ 

```txt
cas 1:
$ echo '\n' 

$

cas 2:
$ echo \n
n
$ 

cas 3:
$ echo \g
g
$

cas 4:
$ echo '\g'
\g
$

cas 5:
$ echo '\'
\
$

cas 6:
$ echo \
$ 

cas 7:
$ echo \\
\ 
$
```

#### Single Quote

- Touts ce qui entre un single est interprete litteralement.

```txt
cas 1:
$ echo ''
$

cas 2:
$ echo '''
quote>

cas 3:
$ echo '\''
quote>

cas 4
$ echo '\'
$ \

cas 5:
$ echo ''''
$
```

#### Double quote

- Touts se qui entre double est quote est interpreter litteralement, sauf:
    - $, \`, \ eux garde leur signification

```txt
Minishell/doc [ echo "$HOME"                                             master * ] 2:34 PM
/mnt/nfs/homes/engooh
Minishell/doc [ echo "\$HOME"                                            master * ] 2:34 PM
$HOME
Minishell/doc [                                                          master * ] 2:34 PM

Minishell/doc [ echo "``"                                                     master * ] 2:38 PM
Minishell/doc [ echo "`"                                                      master * ] 2:38 PM
dquote bquote> 
Minishell/doc [ echo "`ls`"                                                   master * ] 2:39 PM
a.out
bash_ref.md
compilation.md
environement.md
fd_terminal.md
manipulation_de_dossier.md
path
readline
signal
test.c
```


#### L'expantion de l'historique

- le charactere ! appeller devant une commande permet, de faire appelle a l'historique

#### Charactere antislash

```
\a
alerte (cloche)

\b
retour arrière

\e
\E
un caractère d'échappement (pas ANSI C)

\f
saut de formulaire

\n
nouvelle ligne

\r
retour chariot

\t
tabulation horizontale

\v
onglet vertical

\\
barre oblique inverse

\'
simple citation

\"
double citation

\?
point d'interrogation

\nnn
le caractère huit bits dont la valeur est la valeur octale nnn (un à trois chiffres octaux)

\xHH
le caractère huit bits dont la valeur est la valeur hexadécimale HH (un ou deux chiffres hexadécimaux)

\uHHHH
le caractère Unicode (ISO/IEC 10646) dont la valeur est la valeur hexadécimale HHHH (un à quatre chiffres hexadécimaux)

\UHHHHHHHH
le caractère Unicode (ISO/IEC 10646) dont la valeur est la valeur hexadécimale HHHHHHHH (un à huit chiffres hexadécimaux)

\cx
un caractère contrôle- x
```


