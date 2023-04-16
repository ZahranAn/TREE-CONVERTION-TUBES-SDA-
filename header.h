/*
File        : header.h
Deskripsi   : Deklarasi modul dan kamus data program convert non binary tree ke binary tree (AVL)
Anggota     : Bhisma Chandra Yudha      221524037
              Sarah                     221524059  
              Zahran Augerah Rizqullah  221524063
Kelas/Prodi : 1B/D4 Teknik Informatika
*/

#ifndef header_H
#define header_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

typedef struct NBnode* NBaddr;
typedef struct Bnode* Baddr;
typedef char* String;

/* Struct Non - Binary Tree */
typedef struct NBnode{
	String info;
	NBaddr fs, nb, parent;
};
struct NbTree{
	NBaddr root;
};

/* Struct Binary Tree */
typedef struct Bnode{
	String info;
    int height;
	Baddr left, right;
};
struct BTree{
	Baddr root;
};



#endif