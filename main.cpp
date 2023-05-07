/*
File        : main.cpp
Deskripsi   : driver / main program untuk program convert non binary tree ke binary tree (AVL)
Anggota     : Bhisma Chandra Yudha      221524037
			  Sarah                     221524059
			  Zahran Augerah Rizqullah  221524063
Kelas/Prodi : 1B/D4 Teknik Informatika
*/

#include "header.h"
#include "body.cpp"

int main()
{
	/* KAMUS DATA */
	NBTree nb = NULL;
	BTree b = NULL;
	BTree avl = NULL;
	char filename[20]; //= "FileTree.txt";

	/* INISIALISASI NON-BINARY TREE */
	/*InsertNBnode(&nb, SearchNBnode(nb,'0'),'A');
	InsertNBnode(&nb, SearchNBnode(nb,'A'),'B');
	InsertNBnode(&nb, SearchNBnode(nb,'A'),'C');
	InsertNBnode(&nb, SearchNBnode(nb,'A'),'D');
	InsertNBnode(&nb, SearchNBnode(nb,'B'),'E');
	InsertNBnode(&nb, SearchNBnode(nb,'C'),'F');
	InsertNBnode(&nb, SearchNBnode(nb,'C'),'G');
	InsertNBnode(&nb, SearchNBnode(nb,'C'),'H');
	InsertNBnode(&nb, SearchNBnode(nb,'D'),'I');
	InsertNBnode(&nb, SearchNBnode(nb,'D'),'J');
	InsertNBnode(&nb, SearchNBnode(nb,'J'),'K'); */

	/* KONVERSI NON-BINARY TREE */
	for (;;)
	{
		switch (menu())
		{
		case 1:
			// input
			char opsi[5];
			int opsiInt;
			for (;;)
			{
			b:
				printf("1. Insert Manual\n");
				printf("2. Insert From File\n");
				scanf(" %s", opsi);
				for (int i = 0; opsi[i]; i++)
				{
					if (!isdigit(opsi[i]))
					{
						printf("\nMasukkan angka bukan huruf!\n");
						goto b;
					}
				}
				opsiInt = atoi(opsi);
				if (opsiInt < 1 || opsiInt > 2)
				{
					printf("Inputan salah!\n");
					goto b;
				}
				else
				{
					if (opsiInt == 1)
					{
						nbInput(&nb);
						break;
					}
					else
					{
						printf("Silahkan Masukkan Nama File (.txt): ");
						scanf(" %s", &filename);
						insertNBTreeFromFile(&nb, filename);
						break;
					}
				}
			}
			system("pause");
			system("cls");
			break;
		case 2:
			// edit
			editTree(&nb);
			system("pause");
			system("cls");
			break;
		case 3:
			// delete node
			deleteNode(&nb);
			system("pause");
			system("cls");
			break;
		case 4:
			// delete tree
			deleteTree(&nb, &b, &avl);
			system("pause");
			system("cls");
			break;
		case 5:
			// convert & print
			ConvertNBtree(nb, &b, &avl);
			ViewTraversal(nb, b, avl);
			system("pause");
			system("cls");
			break;
		case 6:
			// save tree to file
			if (nb == NULL)
			{
				printf("Tree Masih Kosong!\n");
				system("pause");
				system("cls");
				break;
			}
			else
			{
				printf("Silahkan Masukkan Nama File (.txt): ");
				scanf(" %s", &filename);
				saveNBTreeToFile(nb, filename);
			}
			system("pause");
			system("cls");
			break;
		case 7:
			// exit
			printf("Terima kasih telah menggunakan program kami!");
			exit(0);
			break;
		default:
			printf("Input yang dimasukkan salah!");
			break;
		}
	}
	return 0;
}