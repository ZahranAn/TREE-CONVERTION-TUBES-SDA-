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

/* Konstruktor Node */
NBaddr CreateNBnode(char info){
    NBaddr newNode;
	newNode = (NBaddr)malloc(sizeof(NBnode));
	if (newNode != NULL){
        newNode->info = info;
		newNode->fs = NULL;
		newNode->nb = NULL;
		newNode->parent = NULL;
	}
	return newNode;
}

Baddr CreateBnode(char info){
    Baddr newNode;
	newNode = (Baddr)malloc(sizeof(Bnode));
	if (newNode != NULL){
        newNode->info = info;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 0;
	}
	return newNode;
}

/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBTree NBroot, BTree Broot){
    NBaddr Pcur;
    boolean arah;

    arah = false;
    if (NBroot != NULL){
        Pcur = NBroot;
        InsertBnode(Broot,Pcur);
        do{
            if ((Pcur->fs != NULL) && (arah == false)){
                Pcur = Pcur->fs;
                InsertBnode(Broot, Pcur);
            }else{
                if (Pcur->nb != NULL){
                	arah = false;
                    Pcur = Pcur->nb;
                    InsertBnode(Broot,Pcur);
                }else{
                    Pcur = Pcur->pr;
                    arah = true;
                }
            }
        } while (Pcur != NULL);
    }
}

/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertBnode(BTree Broot, NBaddr nbNode){
	Baddr parent;
    Baddr newNode = CreateBnode (nbNode->info);
    if (nbNode->parent ==  NULL){
        Broot = newNode;
    }else{
        parent = SearchBnode(Broot, nbNode->parent->info);
        if (parent->left ==  NULL){
            parent->left = newNode;
        }else{
            parent = parent->left;
            while (parent->right != NULL){
                parent = parent->right;
            }
            parent->right = newNode;
        }
    }
}

void InsertNBnode(NBTree NBroot, NBaddr parent, char info){
    NBaddr newNode = CreateNBnode(info);
    newNode->parent = parent;
    if (parent == NULL){
        NBroot = newNode;
    }else if (parent->fs == NULL){
        parent->fs = newNode;
    }else{
        parent = parent->fs;
        while (parent->nb != NULL){
            parent = parent->nb;
        }
        parent->nb = newNode;
    }
}

Baddr SearchBnode(BTree Broot, char info){
    Baddr node;
    if (Broot == NULL){
        return NULL;
    }else if (Broot->info == info){
        return Broot;
    }else{
        node = SearchBnode(Broot->left,info);
        if (node != NULL){
            return node;
        }else{
            return SearchBnode(Broot->right,info);
        }
    }
}

NBaddr SearchNBnode (NBTree NBroot, char info){
    NBaddr node;
    if (NBroot == NULL){
        return NULL;
    }else if (NBroot->info == info){
        return NBroot;
    }else{
        node = SearchNBnode(NBroot->fs,info);
        if (node != NULL){
            return node;
        }else{
            return SearchNBnode(NBroot->nb,info);
        }
    }
}

NBaddr SearchBeforeNB (NBTree NBroot, NBaddr info){
    
}

/* Traversal Non Binary Tree */
void NBLevelOrder(NBTree NBroot){
    //perlu queue
}

void NBPostOrder(NBTree NBroot){
    if (NBroot != NULL){
        NBPostOrder(NBroot->fs);
        printf(" %c", NBroot->info);
		NBPostOrder(NBroot->nb);
    }
}

void NBPreOrder(NBTree NBroot){
    if (NBroot != NULL){
		printf(" %c", NBroot->info);
		NBPreOrder(NBroot->fs);
		NBPreOrder(NBroot->nb);
	}
}

void NBInOrder(NBTree NBroot){
    if (NBroot != NULL){
		NBInOrder(NBroot->fs);
		if (NBroot->fs==NULL){
            printf(" %c", NBroot->info);
        } 
		if (NBroot->pr != NULL)
			if (NBroot->pr->fs == NBroot)
				printf(" %c", NBroot->pr->info);
		NBInOrder(NBroot->nb);
	}
}

void ViewTraversalNB(NBTree NBroot){
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
void BLevelOrder(BTree Broot){
    //perlu queue
}

void BPostOrder(BTree Broot){
    if (Broot != NULL){
		BPostOrder(Broot->left);
		BPostOrder(Broot->right);
		printf(" %c", Broot->info);
	}
}

void BPreOrder(BTree Broot){
    if (Broot != NULL){
		printf(" %c", Broot->info);
		BPreOrder(Broot->left);
		BPreOrder(Broot->right);
	}
}

void BInOrder(BTree Broot){ 
    if (Broot != NULL){
		BInOrder(Broot->left);
		printf(" %c", Broot->info);
		BInOrder(Broot->right);
	}
}

void ViewTraversalB(BTree Broot){
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

NBaddr DeleteNodeNB(NBTree NBroot, char info){

}

NBaddr DeleteRootNB(NBTree NBroot, NBaddr info){

}

NBaddr DeleteLeafNB(NBTree NBroot, NBaddr info){

}

NBaddr DeleteStemNB(NBTree NBroot, NBaddr info){

}

bool IsLeafNB(NBTree NBroot){

}

NBaddr UpgradePositionNB(NBTree NBroot, NBaddr info){
    
}

