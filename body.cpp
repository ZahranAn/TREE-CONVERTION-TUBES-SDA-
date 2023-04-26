/*
File        : body.cpp
Deskripsi   : body prototype program convert non binary tree ke binary tree (AVL)
Anggota     : Bhisma Chandra Yudha      221524037
              Sarah                     221524059  
              Zahran Augerah Rizqullah  221524063
Kelas/Prodi : 1B/D4 Teknik Informatika
*/

#include "header.h"
#include <malloc.h>

/* Konstruktor Node */
NBaddr CreateNBnode(infotype info){
    NBaddr newNode;
	newNode = (NBaddr)malloc(sizeof(NBnode));
	if (newNode != NULL){
        newNode->info = info;
		newNode->fs = NULL;
		newNode->nb = NULL;
		newNode->pr = NULL;
	}
	return newNode;
}

Baddr CreateBnode(infotype info){
    Baddr newNode;
	newNode = (Baddr)malloc(sizeof(Bnode));
	if (newNode != NULL){
        newNode->info = info;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1;
	}
	return newNode;
}

/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBTree NBroot, BTree* Broot, BTree* AVLroot){
    NBaddr Pcur;
    bool arah = false;
    if (NBroot != NULL){
        Pcur = NBroot;
        InsertBnode(&(*Broot),Pcur);
        InsertAVLnode(&(*AVLroot),Pcur->info);
        do{
            if ((Pcur->fs != NULL) && (arah == false)){
                Pcur = Pcur->fs;
                InsertBnode(&(*Broot), Pcur);
                InsertAVLnode(&(*AVLroot),Pcur->info);
            }else{
                if (Pcur->nb != NULL){
                	arah = false;
                    Pcur = Pcur->nb;
                    InsertBnode(&(*Broot),Pcur);
                    InsertAVLnode(&(*AVLroot),Pcur->info);
                }else{
                    Pcur = Pcur->pr;
                    arah = true;
                }
            }
        } while (Pcur != NULL);
    }
}

/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertBnode(BTree* Broot, NBaddr nbNode){
	Baddr parent;
    Baddr newNode = CreateBnode (nbNode->info);
    if (nbNode->pr ==  NULL){
        (*Broot) = newNode;
    }else{
        parent = SearchBnode((*Broot), nbNode->pr->info);
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

void InsertNBnode(NBTree* NBroot, NBaddr parent, infotype info){
    NBaddr newNode = CreateNBnode(info);
    newNode->pr = parent;
    if (parent == NULL){
        (*NBroot) = newNode;
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

void InsertAVLnode(BTree* Broot, infotype info){
	if (*Broot == NULL){
	*Broot = CreateBnode(info);
	return;
	}
	if (info < (*Broot)->info){
		InsertAVLnode(&((*Broot)->left), info);
	}else if (info > (*Broot)->info){
		InsertAVLnode(&((*Broot)->right), info);
	}else {	return;	}

	(*Broot)->height = 1 + Max(NodeHeight((*Broot)->left),NodeHeight((*Broot)->right));
	
	int balance = GetDifference(*Broot);
	
	// Left Left Case
	if (balance > 1 && info < (*Broot)->left->info){
		*Broot = RightRotation(*Broot);
		return;
	}
	// Right Right Case
	if (balance < -1 && info > (*Broot)->right->info){
		*Broot = LeftRotation(*Broot);
		return;
	}
	// Left Right Case
	if (balance > 1 && info > (*Broot)->left->info){
		(*Broot)->left = LeftRotation((*Broot)->left);
		*Broot = RightRotation(*Broot);
		return;
	}
	// Right Left Case
	if (balance < -1 && info < (*Broot)->right->info){
		(*Broot)->right = RightRotation((*Broot)->right);
		*Broot = LeftRotation(*Broot);
		return;
	}
}

/* Modul Pembantu Untuk AVL Tree */
int Max(int a, int b){
	return (a > b)? a : b;
}

int NodeHeight(Baddr root){
	if (root == NULL)
		return 0;
	return root->height;
}

Baddr RightRotation(Baddr y){
	Baddr x = y->left;
	Baddr T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = Max(NodeHeight(y->left), NodeHeight(y->right))+1;
	x->height = Max(NodeHeight(x->left), NodeHeight(x->right))+1;
	return x;
}

Baddr LeftRotation(Baddr x){
	Baddr y = x->right;
	Baddr T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = Max(NodeHeight(x->left), NodeHeight(x->right))+1;
	y->height = Max(NodeHeight(y->left), NodeHeight(y->right))+1;
	return y;
}

int GetDifference(Baddr N){
	if (N == NULL)
		return 0;
	return NodeHeight(N->left) - NodeHeight(N->right);
}

Baddr SearchBnode(BTree Broot, infotype info){
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

NBaddr SearchNBnode (NBTree NBroot, infotype info){
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
        printf("\n\tTree masih kosong!\n");
    }
//    printf("\tLEVELORDER : ");
//    BLevelOrder(Broot); printf("\n");
    printf("\tPOSTORDER : ");
    BPostOrder(Broot); printf("\n");
    printf("\tPREORDER  : ");
    BPreOrder(Broot);  printf("\n");
    printf("\tINORDER   : ");
    BInOrder(Broot);   printf("\n");
}

NBaddr DeleteNodeNB(NBTree NBroot, infotype info){

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