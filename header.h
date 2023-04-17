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

typedef char infotype;

typedef struct NBnode* NBaddr;
typedef struct Bnode* Baddr;

/* Struct Non Binary Tree */
struct NBnode{
	infotype info;
	NBaddr fs, nb, pr;
};
typedef NBaddr NBTree;

/* Struct Binary Tree */
struct Bnode{
	infotype info;
    int height;
	Baddr left, right;
};
typedef Baddr BTree;

/* Konstruktor Node */
NBaddr CreateNBnode(infotype info);
Baddr CreateBnode(infotype info);

/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBTree NBtree, BTree Broot);

/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertBnode(BTree Broot, NBaddr nbNode);
void InsertNBnode(NBTree NBroot, NBaddr parent, infotype info);
void InsertAVLnode(BTree Broot, infotype info);

/* Modul Pembantu Untuk AVL Tree */
int Max(int a, int b);
int NodeHeight(BTree root);
Baddr RightRotation(Baddr y);
Baddr LeftRotation(Baddr x);
int GetDifference(Baddr N);

/* Search dengan mengembalikan address Node tertentu */
Baddr SearchBnode(BTree Broot, infotype info);
NBaddr SearchBeforeNB (NBTree NBroot, NBaddr info);
NBaddr SearchNBnode (NBTree NBroot, infotype info);

/* Traversal Non Binary Tree */
void NBLevelOrder(NBTree NBroot);
void NBPostOrder(NBTree NBroot);
void NBPreOrder(NBTree NBroot);
void NBInOrder(NBTree NBroot);
void ViewTraversalNB(NBTree NBroot);

/* Traversal Binary Tree*/
void BLevelOrder(BTree Broot);
void BPostOrder(BTree Broot);
void BPreOrder(BTree Broot);
void BInOrder(BTree Broot);
void ViewTraversalB(BTree Broot);

/* Delete Node Non Binary Tree */
NBaddr DeleteNodeNB(NBTree NBroot, infotype info);
NBaddr DeleteRootNB(NBTree NBroot, NBaddr info);
NBaddr DeleteLeafNB(NBTree NBroot, NBaddr info);
NBaddr DeleteStemNB(NBTree NBroot, NBaddr info);
bool IsLeafNB(NBTree NBroot);
NBaddr UpgradePositionNB(NBTree NBroot, NBaddr info);

#endif