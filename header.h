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

typedef struct Node {
    NBaddr dataNB;
	Baddr dataB;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;


void initQueue(Queue* q);
int isEmpty(Queue* q);
void enqueue(Queue* q, NBaddr dataNB, Baddr dataB);
void dequeue(Queue* q);
NBaddr front(Queue* q);
int getSize(Queue* q);


/* Konstruktor Node */
NBaddr CreateNBnode(infotype info);
/*Function untuk mengalokasikan node non-binary tree dan mengembalikan alamat node baru
*/
Baddr CreateBnode(infotype info);
/*Function untuk mengalokasikan node binary tree dan mengembalikan alamat node baru
*/


/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBTree NBtree, BTree* Broot, BTree* AVLroot);
/*Procedure untuk membuat binary tree dari bentuk non-binary tree 
	I.S.: Broot, NBroot, dan AVLroot terdefinisi 
	F.S.: Broot menjadi binary tree dari non-binary tree, dan AVLroot menjadi balanced binary tree dari non-binary tree
*/


/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertNBnode(NBTree* NBroot, NBaddr parent, infotype info);
/*Function untuk mengalokasikan node non-binary tree dan mengembalikan alamat node baru
	I.S.: NBtree, parent, dan info terdefinisi
	F.S.: Non-binary tree bertambah satu node
*/
void InsertBnode(BTree* Broot, NBaddr nbNode);
/*Procedure untuk menambahkan node ke dalam binary tree
	I.S.: Btree, dan Bnode terdefinisi
	F.S.: Non-binary tree bertambah satu node
*/
void InsertAVLnode(BTree* Broot, infotype info);
/*Procedure untuk menambahkan node baru ke dalam binary tree yang seimbang (AVL tree)
	I.S.: Btree, dan Bnode terdefinisi
	F.S.: Non-binary tree bertambah satu node
*/


/* Modul Pembantu Untuk AVL Tree */
int Max(int a, int b);
/*Function untuk membandingkan dua nilai integer dan mengembalikan nilai terbesar
*/
int NodeHeight(BTree node);
/*Function untuk mengembalikan ketinggian suatu binary node dan mengembalikan 0 jika node tersebut tidak ada
*/
Baddr RightRotation(Baddr pivot);
/*Function untuk mengembalikan tree setelah melakukan right rotation 
*/
Baddr LeftRotation(Baddr pivot);
/*Function untuk menembalikan tree setelah melakukan left rotation 
*/
int GetDifference(Baddr node);
/*Function untuk menembalikan nilai keseimbangan node
*/


/* Search dengan mengembalikan address Node tertentu */
Baddr SearchBnode(BTree Broot, infotype info);
/*Function untuk mencari node dalam binary tree berdasarkan nilai info dan mengembalikan alamat node tersebut
*/
NBaddr SearchNBnode (NBTree NBroot, infotype info);
/*Function untuk mencari node dalam non-binary tree berdasarkan nilai info dan mengembalikan alamat node tersebut
*/
NBaddr SearchBeforeNB (NBTree NBroot, NBaddr target);
/*Function untuk mencari node dalam non-binary tree berdasarkan nilai info dan mengembalikan alamat node tersebut
*/


/* Traversal Non Binary Tree */
void ViewTraversalNB(NBTree NBroot);
/*Procedure untuk menampilkan keempat traversal non binary tree ke layar
	I.S.: NBtree terdefinisi
	F.S.: Keempat traversal non binary tree ditampilkan di layar
*/
void NBLevelOrder(NBTree NBroot);
/*Procedure untuk menampilkan elemen non binary tree secara traversal level order
	I.S.: NBtree terdefinisi
	F.S.: Elemen non-binary tree ditampilkan di layar dengan urutan traversal level order
*/
void NBPostOrder(NBTree NBroot);
/*Procedure untuk menampilkan elemen non binary tree secara traversal post order
	I.S.: NBtree terdefinisi
	F.S.: Elemen non-binary tree ditampilkan di layar dengan urutan traversal post order
*/
void NBPreOrder(NBTree NBroot);
/*Procedure untuk menampilkan elemen non binary tree secara traversal pre order
	I.S.: NBtree terdefinisi
	F.S.: Elemen non-binary tree ditampilkan di layar dengan urutan traversal pre order
*/
void NBInOrder(NBTree NBroot);
/*Procedure untuk menampilkan elemen non binary tree secara traversal in order
	I.S.: NBtree terdefinisi
	F.S.: Elemen non-binary tree ditampilkan di layar dengan urutan traversal in order
*/


/* Traversal Binary Tree */
void ViewTraversalB(BTree Broot);
/*procedure menampilkan keempat traversal binary tree ke layar
	I.S.: Btree terdefinisi
	F.S.: Keempat traversal binary tree ditampilkan di layar
*/
void BLevelOrder(BTree Broot);
/*Procedure untuk menampilkan elemen binary tree secara traversal level order
	I.S.: Btree terdefinisi
	F.S.: Elemen binary tree ditampilkan di layar 
*/
void BPostOrder(BTree Broot);
/*Procedure untuk menampilkan elemen binary tree secara traversal post order
	I.S.: Btree terdefinisi
	F.S.: Elemen binary tree ditampilkan di layar dengan urutan traversal post order
*/
void BPreOrder(BTree Broot);
/*Procedure untuk menampilkan elemen binary tree secara traversal pre order
	I.S.: Btree terdefinisi
	F.S.: Elemen binary tree ditampilkan di layar dengan urutan traversal pre order
*/
void BInOrder(BTree Broot);
/*Procedure untuk menampilkan elemen binary tree secara traversal in order
	I.S.: Btree terdefinisi
	F.S.: Elemen binary tree ditampilkan di layar dengan urutan traversal in order
*/


/* Delete Node Non Binary Tree */
void DeleteNodeNB(NBTree* NBroot, infotype info);
/*Procedure untuk menentukan jenis delete node, memanggil jenis delete untuk dieksekusi sesuai kondisi, 
  dan mengembalikan alamat root terbaru setelah proses delete.
	I.S.: NBtree terdefinisi
	F.S.: Satu node dalam non-binary tree dihapus sesuai info 
*/
void DeleteRootNB(NBTree* NBroot, NBaddr toDelete);
/*Procedure untuk Menghapus node yang berupa root, memanggil modul IsLeaf untuk mengecek apakah hanya ada satu node 
  dan modul UpgradePositionNB untuk mengupdate posisi node-node di tree setelah node yang ingin dihapus diputus dari rantai hirarki.
	I.S.: NBtree dan alamat node yang ingin dihapus terdefinisi
	F.S.: Node root dalam non-binary tree dihapus
*/
void DeleteLeafNB(NBTree* NBroot, NBaddr toDelete);
/*Menghapus node yang berupa leaf.
	I.S.: NBtree dan alamat node yang ingin dihapus terdefinisi
	F.S.: Salah saatu node leaf dalam non-binary tree dihapus
*/
void DeleteStemNB(NBTree* NBroot, NBaddr toDelete);
/*Menghapus node yang berupa stem.
	I.S.: NBtree dan alamat node yang ingin dihapus terdefinisi
	F.S.: Salah saatu node stem dalam non-binary tree dihapus
*/


/* Modul Pembantu Untuk Delete Non Binary Tree */
bool IsLeafNB(NBTree NBroot);
/*Function untuk menentukan sebuah node termasuk daun atau bukan.
*/
void UpgradePositionNB(NBaddr* node);
/*Procedure untuk memindahkan posisi sebuah node dalam non-binary tree dengan menata ulang anak dan saudaranya.

*/

void nbTreeToFile(NBTree root, FILE *fp);
void saveNBTreeToFile(NBTree root, char *filename);
void insertNBTreeFromFile(NBTree *NBroot, char *filename);

int menu();

void nbInput(NBTree *NBroot);

void listParent(NBaddr NBroot);

void deleteNode(NBTree *NBroot);

void editTree(NBTree *NBroot);

#endif