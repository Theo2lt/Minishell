# Minishell


## [Opendir](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-opendir-open-directory)

#### Prototype

- ouvre un dossier et retourne un pointer sur ce dossier

```
#define _POSIX_SOURCE
#include <dirent.h>

DIR *opendir(const char *dirname);
```


## [readdir](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-readdir-read-entry-from-directory)

- a chaque appelle de readdir la fonction va retourner un fichier contenue dans le repertoir pointer le retour de opendir.
- Enfaite readdir va parcourir le flux de fichier du repertoire.

#### Prototype 

```c
#define_POSIX_SOURCE
#include <dirent.h>

struct dirent *readdir(DIR *dir);
```

####   Example:

```c
/* CELEBR04

   This example reads the contents of a root directory.

 */
#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

main() {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir("/")) == NULL)
    perror("opendir() error");
  else {
    puts("contents of root:");
    while ((entry = readdir(dir)) != NULL)
      printf("  %s\n", entry->d_name);
    closedir(dir);
  }
}
```

#### Sortie: 

```
contents of root:
  .
  ..
  bin
  dev
  etc
  lib
  tmp
  u
  usr
```




### [Closedir](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-closedir-close-directory#rtclod)

- Ferme le répertoire indiqué par dir . Il libère le tampon utilisé par readdir() lors de la lecture du flux de répertoire.

#### Prototype 

```c
#define _POSIX_SOURCE
#include <dirent.h>

int closedir(DIR *dir);
```
