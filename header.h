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

/* Struct Non Binary Tree */
typedef struct NBnode{
	char info;
	NBaddr fs, nb, parent;
};
struct NbTree{
	NBaddr NBroot;
};

/* Struct Binary Tree */
typedef struct Bnode{
	char info;
    int height;
	Baddr left, right;
};
struct BTree{
	Baddr Broot;
};

/* Konstruktor Node */
NBaddr CreateNBnode(char info);
Baddr CreateBnode(char info);

/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBaddr NBroot, Baddr Broot);

/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertNBnode(NBaddr NBroot);
void InsertBnode(Baddr Broot);

/* Search dengan mengembalikan address Node tertentu */
NBaddr SearchBnode(Baddr root, char info);
NBaddr SearchBeforeNB (NBaddr NBroot, NBaddr info);

/* Traversal Non Binary Tree */
void NBLevelOrder(NBaddr NBroot);
void NBPostOrder(NBaddr NBroot);
void NBPreOrder(NBaddr NBroot);
void NBInOrder(NBaddr NBroot);
void ViewTraversalNB(NBaddr NBroot);

/* Traversal Binary Tree*/
void BLevelOrder(Baddr Broot);
void BPostOrder(Baddr Broot);
void BPreOrder(Baddr Broot);
void BInOrder(Baddr Broot);
void ViewTraversalB(Baddr Broot);

/* Delete Node Non Binary Tree */
NBaddr DeleteNodeNB(NBaddr NBroot, char info);
NBaddr DeleteRootNB(NBaddr NBroot, NBaddr info);
NBaddr DeleteLeafNB(NBaddr NBroot, NBaddr info);
NBaddr DeleteStemNB(NBaddr NBroot, NBaddr info);
bool IsLeafNB(NBaddr NBroot);
NBaddr UpgradePositionNB(NBaddr NBroot, NBaddr info);

#endif