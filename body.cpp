/*
File        : body.cpp
Deskripsi   : body prototype program convert non binary tree ke binary tree (AVL)
Anggota     : Bhisma Chandra Yudha      221524037
              Sarah                     221524059  
              Zahran Augerah Rizqullah  221524063
Kelas/Prodi : 1B/D4 Teknik Informatika
*/

#include "boolean.h"
#include "header.h"
#include <malloc.h>

/* Traversal Non Binary Tree */
void NBLevelOrder(NBaddr NBroot){
    //perlu queue
}

void NBPostOrder(NBaddr NBroot){
    if (NBroot != NULL){
        NBPostOrder(NBroot->fs);
        printf(" %c", NBroot->info);
		NBPostOrder(NBroot->nb);
    }
}

void NBPreOrder(NBaddr NBroot){
    if (NBroot != NULL){
		printf(" %c", NBroot->info);
		NBPreOrder(NBroot->fs);
		NBPreOrder(NBroot->nb);
	}
}

void NBInOrder(NBaddr NBroot){
    if (NBroot != NULL){
		NBInOrder(NBroot->fs);
		if (NBroot->fs==NULL){
            printf(" %c", NBroot->info);
        } 
		if (NBroot->parent != NULL)
			if (NBroot->parent->fs == NBroot)
				printf(" %c", NBroot->parent->info);
		NBInOrder(NBroot->nb);
	}
}

void ViewTraversalNB(NBaddr NBroot){
    if(NBroot == NULL){
        printf("\n\tTree masih kosong!");
    }
    printf("\n\tNon Binary Tree");
    printf("\n\tLEVELORDER : ");
    NBLevelOrder(NBroot); printf("\n");
    printf("\tPOSTORDER : ");
    NBPostOrder(NBroot); printf("\n");
    printf("\tPREORDER  : ");
    NBPreOrder(NBroot);  printf("\n");
    printf("\tINORDER   : ");
    NBInOrder(NBroot);   printf("\n");
}


/* Traversal Binary Tree*/
void BLevelOrder(Baddr Broot){
    //perlu queue
}

void BPostOrder(Baddr Broot){
    if (Broot != NULL){
		BPostOrder(Broot->left);
		BPostOrder(Broot->right);
		printf(" %c", Broot->info);
	}
}

void BPreOrder(Baddr Broot){
    if (Broot != NULL){
		printf(" %c", Broot->info);
		BPreOrder(Broot->left);
		BPreOrder(Broot->right);
	}
}

void BInOrder(Baddr Broot){ 
    if (Broot != NULL){
		BInOrder(Broot->left);
		printf(" %c", Broot->info);
		BInOrder(Broot->right);
	}
}

void ViewTraversalB(Baddr Broot){
    if(Broot == NULL){
        printf("\n\tTree masih kosong!");
    }
    printf("\n\tLEVELORDER : ");
    BLevelOrder(Broot); printf("\n");
    printf("\tPOSTORDER : ");
    BPostOrder(Broot); printf("\n");
    printf("\tPREORDER  : ");
    BPreOrder(Broot);  printf("\n");
    printf("\tINORDER   : ");
    BInOrder(Broot);   printf("\n");
}

