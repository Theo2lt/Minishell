/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:04:45 by engooh            #+#    #+#             */
/*   Updated: 2022/07/05 14:58:41 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

// getcwd return le repertoire courant dans buf si la taile de buf et pas bonne la fonction return null 
// chdir c'est comment cd en mode fonction

int	test_stat_and_fstat()
{
	struct stat info_file;

	if (stat("getcwd", &info_file) == -1)
        	perror("stat");
}
// dans stat ya tout ca  
/*
   dev_t     st_dev;       /* ID du périphérique contenant le fichier */
    // ino_t     st_ino;      /* Numéro inœud */
    // mode_t    st_mode;     /* Protection */
//    nlink_t   st_nlink;    /* Nb liens matériels */
 //   uid_t     st_uid;      /* UID propriétaire */
  //  gid_t     st_gid;      /* GID propriétaire */
   // dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
    // off_t     st_size;     /* Taille totale en octets */
    // blksize_t st_blksize;  /* Taille de bloc pour E/S */
//    blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
 //   time_t    st_atime;    /* Heure dernier accès */
  //  time_t    st_mtime;    /* Heure dernière modification */
   // time_t    st_ctime;    /* Heure dernier changement état */
//};

int	main(void)
{
	char	buf[256];

	printf("res %s\n", getcwd(buf, sizeof(buf)));
	return (0);
}

