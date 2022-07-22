## [getenv](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-getenv-get-value-environment-variables)

- Recherche dans la table des variables d'environnement une entrée correspondant à varname et renvoie un pointeur vers un tampon contenant la valeur de chane actuelle de varname .

- Pour éviter de modifier les variables d'environnement ou le processus de gestion, l'appelant doit s'assurer de ne pas modifier ou libérer le tampon pointé par le pointeur renvoyé.

 - Vous devez copier la chane renvoyée car un appel ultérieur à getenv() l'écrasera.  

#### Prototype 

```c
#include <stdlib.h>

char *getenv(const char *varname);
```

## 
