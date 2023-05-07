/*
File        : main.cpp
Deskripsi   : driver / main program untuk program convert non binary tree ke binary tree (AVL)
Anggota     : Bhisma Chandra Yudha      221524037
              Sarah                     221524059  
              Zahran Augerah Rizqullah  221524063
Kelas/Prodi : 1B/D4 Teknik Informatika
*/

#include "header.h"

int main(){
	/* KAMUS DATA */
	NBTree nb = NULL;
	BTree b = NULL;
	BTree avl = NULL;
	int opsi = 0;
//	char filename[] = "FileTree.txt";

	/* INISIALISASI NON-BINARY TREE */
	InsertNBnode(&nb, SearchNBnode(nb,'0'),'A');
	InsertNBnode(&nb, SearchNBnode(nb,'A'),'B');
	InsertNBnode(&nb, SearchNBnode(nb,'B'),'C');
	
	/* KONVERSI NON-BINARY TREE */
//	insertNBTreeFromFile(&nb, filename);
	ConvertNBtree(nb,&b,&avl);
	ViewTraversalNB(nb);
	printf("\n\tBinary Tree\n");
	ViewTraversalB(b);
	printf("\n\tAVL Tree\n");
	ViewTraversalB(avl);
	
	DeleteNodeNB(&nb, 'B');
    
	ConvertNBtree(nb,&b,&avl);
    ViewTraversalNB(nb);
	printf("\n\tBinary Tree\n");
	ViewTraversalB(b);
	printf("\n\tAVL Tree\n");
	ViewTraversalB(avl);
	
    return 0;
}