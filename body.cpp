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
void InsertBnode(BTree* Broot, NBaddr NBnode){
	Baddr parent;
    Baddr newNode = CreateBnode (NBnode->info);
    if (NBnode->pr ==  NULL){
        (*Broot) = newNode;
    }else{
        parent = SearchBnode((*Broot), NBnode->pr->info);
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
	int balance = 0;
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
	
	balance = GetDifference(*Broot);
	
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

int NodeHeight(Baddr node){
	if (node == NULL)
		return 0;
	return node->height;
}

Baddr RightRotation(Baddr pivot){
	Baddr newRoot = pivot->left;
	Baddr rightSubtree = newRoot->right;

	newRoot->right = pivot;
	pivot->left = rightSubtree;

	pivot->height = Max(NodeHeight(pivot->left), NodeHeight(pivot->right))+1;
	newRoot->height = Max(NodeHeight(newRoot->left), NodeHeight(newRoot->right))+1;
	return newRoot;
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

int GetDifference(Baddr node){
	if (node == NULL)
		return 0;
	return NodeHeight(node->left) - NodeHeight(node->right);
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

NBaddr SearchBeforeNB(NBTree NBroot, NBaddr target) {
    if (NBroot == NULL) {
        return NULL;
    }
    if (NBroot->nb == target) {
        return NBroot;
    }

    NBaddr result = SearchBeforeNB(NBroot->fs, target);
    if (result == NULL) {
        result = SearchBeforeNB(NBroot->nb, target);
    }

    return result;
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

void DeleteNodeNB(NBTree* NBroot, infotype info) {
    NBaddr toDelete = SearchNBnode(*NBroot, info);
    
    if (toDelete == NULL) {
        printf("\nNode not Found!\n");
        return;
    }
    if (toDelete->pr == NULL) {
        DeleteRootNB(NBroot, toDelete);
        printf("\nRoot Node Deleted!\n");
    } else if (IsLeafNB(toDelete)) {
        DeleteLeafNB(NBroot, toDelete);
        printf("\nLeaf Node Deleted!\n");
    } else {
        DeleteStemNB(&(*NBroot), toDelete);
        printf("\nStem Node Deleted!\n");
    }
}

void DeleteRootNB(NBTree* NBroot, NBaddr toDelete){
    NBaddr child = NULL;
	
    if(IsLeafNB(toDelete)){
        *NBroot = NULL;
    } else {
        child = toDelete->fs;
        child->pr = NULL;
        UpgradePositionNB(&child);
        *NBroot = child;
    }
    free(toDelete);
}

void DeleteLeafNB(NBTree* NBroot, NBaddr toDelete){
    NBaddr parent = SearchBeforeNB(*NBroot, toDelete);
    
    if(parent == NULL){
        return;
    } else if(parent->fs == toDelete){
        if(toDelete->nb != NULL){
            parent->fs = toDelete->nb;
        } else {
            parent->fs = NULL;
        }
    } else {
        parent = parent->nb;
        while(parent->nb != toDelete){
            parent = parent->nb;
        }
        if(toDelete->nb != NULL){
            parent->nb = toDelete->nb;
        } else {
            parent->nb = NULL;
        }
    }
    free(toDelete);
}

void DeleteStemNB(NBTree* NBroot, NBaddr toDelete){
    NBaddr child = toDelete->fs;
    NBaddr nextbrother = NULL;
    NBaddr prevBrother = NULL;
    
    child->pr = toDelete->pr;
    if (SearchBeforeNB(*NBroot, toDelete) == 0) {
        toDelete->pr->fs = child;
        if (toDelete->nb == NULL) {
            UpgradePositionNB(&child);
        } else {
            nextbrother = toDelete->nb;
            UpgradePositionNB(&child);
            child->nb = nextbrother;
        }
    } else {
        nextbrother = toDelete->nb;
        UpgradePositionNB(&child);
        child->nb = nextbrother;
        prevBrother = SearchBeforeNB(*NBroot, toDelete);
        prevBrother->nb = child;
    }
    free(toDelete);
}


/* Modul Pembantu Untuk Delete Non Binary Tree */
bool IsLeafNB(NBTree NBroot){
    if(NBroot->fs == NULL){
        return true;
    } else {
        return false;
    }
}

void UpgradePositionNB(NBaddr* node) {
    NBaddr lastChild = NULL;
    NBaddr sibling = NULL;
	
    if ((*node)->fs && (*node)->nb) {
        lastChild = (*node)->fs;
        while (lastChild->nb) {
            lastChild = lastChild->nb;
        }
        sibling = (*node)->nb;
        lastChild->nb = sibling;
        (*node)->nb = NULL;
        while (sibling) {
            sibling->pr = *node;
            sibling = sibling->nb;
        }
    } else if ((*node)->fs == NULL) {
        sibling = (*node)->nb;
        (*node)->nb = NULL;
        (*node)->fs = sibling;
        while (sibling) {
            sibling->pr = *node;
            sibling = sibling->nb;
        }
    }
}


