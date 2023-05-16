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
#include <ctype.h>

/*ADT Queue untuk Level Order*/
void initQueue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

void enqueue(Queue *q, NBaddr dataNB, Baddr dataB)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dataNB = dataNB;
    newNode->dataB = dataB;
    newNode->next = NULL;

    if (newNode == NULL)
    {
        printf("Alokasi gagal, memori penuh!\n");
    }

    if (isEmpty(q))
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return;
    }

    Node *temp = q->front;
    q->front = q->front->next;
    free(temp);

    if (isEmpty(q))
    {
        q->rear = NULL;
    }
}

NBaddr front(Queue *q)
{
    if (isEmpty(q))
    {
        return NULL;
    }

    return q->front->dataNB;
}

int getSize(Queue *q)
{
    int size = 0;
    Node *current = q->front;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

/* Konstruktor Node */
NBaddr CreateNBnode(infotype info)
{
    NBaddr newNode;
    newNode = (NBaddr)malloc(sizeof(NBnode));
    if (newNode != NULL)
    {
        newNode->info = info;
        newNode->fs = NULL;
        newNode->nb = NULL;
        newNode->pr = NULL;
    }
    return newNode;
}

Baddr CreateBnode(infotype info)
{
    Baddr newNode;
    newNode = (Baddr)malloc(sizeof(Bnode));
    if (newNode != NULL)
    {
        newNode->info = info;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
    }
    return newNode;
}

/* Modul untuk konversi Non Binary Tree ke Binary Tree */
void ConvertNBtree(NBTree NBroot, BTree *Broot, BTree *AVLroot)
{
    NBaddr Pcur;
    DeleteBtree(&(*Broot));
    DeleteBtree(&(*AVLroot));
    int step = 1;
    bool arah = false;
    if (NBroot != NULL)
    {
        Pcur = NBroot;
        printf("\n=========================================================================================================\n");
        printf("Step %d\n", step);
        step++;
        InsertBnode(&(*Broot), Pcur);
        printf("\nBinary Tree:\n");
        print_tree(*Broot, 0);
        InsertAVLnode(&(*AVLroot), Pcur->info);
        printf("\nAVL Tree:\n");
        print_tree(*AVLroot, 0);
        printf("\n=========================================================================================================\n");
        system("pause");
        do
        {
            if ((Pcur->fs != NULL) && (arah == false))
            {
                Pcur = Pcur->fs;
                printf("\n=========================================================================================================\n");
                printf("Step %d\n", step);
                step++;
                InsertBnode(&(*Broot), Pcur);
                printf("\nBinary Tree:\n");
                print_tree(*Broot, 0);
                InsertAVLnode(&(*AVLroot), Pcur->info);
                printf("\nAVL Tree:\n");
                print_tree(*AVLroot, 0);
                printf("\n=========================================================================================================\n");
                system("pause");
            }
            else
            {
                if (Pcur->nb != NULL)
                {
                    arah = false;
                    Pcur = Pcur->nb;
                    printf("\n=========================================================================================================\n");
                    printf("Step %d\n", step);
                    step++;
                    InsertBnode(&(*Broot), Pcur);
                    printf("\nBinary Tree:\n");
                    print_tree(*Broot, 0);
                    InsertAVLnode(&(*AVLroot), Pcur->info);
                    printf("\nAVL Tree:\n");
                    print_tree(*AVLroot, 0);
                    printf("\n=========================================================================================================\n");
                    system("pause");
                }
                else
                {
                    Pcur = Pcur->pr;
                    arah = true;
                }
            }
        } while (Pcur != NULL);
    }
}

/* Modul untuk alokasi sebuah node yang dimasukkan */
void InsertBnode(BTree *Broot, NBaddr NBnode)
{
    Baddr parent;
    Baddr newNode = CreateBnode(NBnode->info);
    if (NBnode->pr == NULL)
    {
        (*Broot) = newNode;
    }
    else
    {
        parent = SearchBnode((*Broot), NBnode->pr->info);
        if (parent->left == NULL)
        {
            parent->left = newNode;
        }
        else
        {
            parent = parent->left;
            while (parent->right != NULL)
            {
                parent = parent->right;
            }
            parent->right = newNode;
        }
    }
}

void InsertNBnode(NBTree *NBroot, NBaddr parent, infotype info)
{
    NBaddr newNode = CreateNBnode(info);
    newNode->pr = parent;
    if (parent == NULL)
    {
        (*NBroot) = newNode;
    }
    else if (parent->fs == NULL)
    {
        parent->fs = newNode;
    }
    else
    {
        parent = parent->fs;
        while (parent->nb != NULL)
        {
            parent = parent->nb;
        }
        parent->nb = newNode;
    }
}

void InsertAVLnode(BTree *Broot, infotype info)
{
    int balance = 0;
    if (*Broot == NULL)
    {
        *Broot = CreateBnode(info);
        return;
    }
    if (info < (*Broot)->info)
    {
        InsertAVLnode(&((*Broot)->left), info);
    }
    else if (info > (*Broot)->info)
    {
        InsertAVLnode(&((*Broot)->right), info);
    }
    else
    {
        return;
    }

    (*Broot)->height = 1 + Max(NodeHeight((*Broot)->left), NodeHeight((*Broot)->right));

    balance = GetDifference(*Broot);

    // Left Left Case
    if (balance > 1 && info < (*Broot)->left->info)
    {
        *Broot = RightRotation(*Broot);
        printf("\nRotasi Kiri\n");
        return;
    }
    // Right Right Case
    if (balance < -1 && info > (*Broot)->right->info)
    {
        *Broot = LeftRotation(*Broot);
        printf("\nRotasi Kanan\n");
        return;
    }
    // Left Right Case
    if (balance > 1 && info > (*Broot)->left->info)
    {
        (*Broot)->left = LeftRotation((*Broot)->left);
        *Broot = RightRotation(*Broot);
        printf("\nRotasi Kiri Lalu Kanan\n");
        return;
    }
    // Right Left Case
    if (balance < -1 && info < (*Broot)->right->info)
    {
        (*Broot)->right = RightRotation((*Broot)->right);
        *Broot = LeftRotation(*Broot);
        printf("\nRotasi Kanan Lalu Kiri\n");
        return;
    }
}

/* Modul Pembantu Untuk AVL Tree */
int Max(int a, int b)
{
    return (a > b) ? a : b;
}

int NodeHeight(Baddr node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

Baddr RightRotation(Baddr pivot)
{
    Baddr newRoot = pivot->left;
    Baddr rightSubtree = newRoot->right;

    newRoot->right = pivot;
    pivot->left = rightSubtree;

    pivot->height = Max(NodeHeight(pivot->left), NodeHeight(pivot->right)) + 1;
    newRoot->height = Max(NodeHeight(newRoot->left), NodeHeight(newRoot->right)) + 1;
    return newRoot;
}

Baddr LeftRotation(Baddr x)
{
    Baddr y = x->right;
    Baddr T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = Max(NodeHeight(x->left), NodeHeight(x->right)) + 1;
    y->height = Max(NodeHeight(y->left), NodeHeight(y->right)) + 1;
    return y;
}

int GetDifference(Baddr node)
{
    if (node == NULL)
        return 0;
    return NodeHeight(node->left) - NodeHeight(node->right);
}

Baddr SearchBnode(BTree Broot, infotype info)
{
    Baddr node;
    if (Broot == NULL)
    {
        return NULL;
    }
    else if (Broot->info == info)
    {
        return Broot;
    }
    else
    {
        node = SearchBnode(Broot->left, info);
        if (node != NULL)
        {
            return node;
        }
        else
        {
            return SearchBnode(Broot->right, info);
        }
    }
}

NBaddr SearchNBnode(NBTree NBroot, infotype info)
{
    NBaddr node;
    if (NBroot == NULL)
    {
        return NULL;
    }
    else if (NBroot->info == info)
    {
        return NBroot;
    }
    else
    {
        node = SearchNBnode(NBroot->fs, info);
        if (node != NULL)
        {
            return node;
        }
        else
        {
            return SearchNBnode(NBroot->nb, info);
        }
    }
}

NBaddr SearchBeforeNB(NBTree NBroot, NBaddr target)
{
    if (NBroot == NULL)
    {
        return NULL;
    }
    if (NBroot->fs == target)
    {
        return NBroot;
    }

    NBaddr result = SearchBeforeNB(NBroot->fs, target);
    if (result == NULL)
    {
        result = SearchBeforeNB(NBroot->nb, target);
    }

    return result;
}

/* Traversal Non Binary Tree */
void NBLevelOrder(NBTree NBroot)
{
    if (NBroot == NULL)
    {
        return;
    }

    BTree Broot;
    Queue q;
    initQueue(&q);
    enqueue(&q, NBroot, Broot);

    while (!isEmpty(&q))
    {
        int n = getSize(&q);
        for (int i = 0; i < n; i++)
        {
            NBaddr node = front(&q);
            dequeue(&q);

            // Proses data pada node (misalnya, cetak nama node)
            printf(" %c", node->info);

            // Jika node memiliki anak, tambahkan semua anak ke dalam queue
            NBaddr child = node->fs;
            while (child != NULL)
            {
                enqueue(&q, child, Broot);
                child = child->nb;
            }
        }
    }
}

void NBPostOrder(NBTree NBroot)
{
    if (NBroot != NULL)
    {
        NBPostOrder(NBroot->fs);
        printf(" %c", NBroot->info);
        NBPostOrder(NBroot->nb);
    }
}

void NBPreOrder(NBTree NBroot)
{
    if (NBroot != NULL)
    {
        printf(" %c", NBroot->info);
        NBPreOrder(NBroot->fs);
        NBPreOrder(NBroot->nb);
    }
}

void NBInOrder(NBTree NBroot)
{
    if (NBroot != NULL)
    {
        NBInOrder(NBroot->fs);
        if (NBroot->fs == NULL)
        {
            printf(" %c", NBroot->info);
        }
        if (NBroot->pr != NULL)
            if (NBroot->pr->fs == NBroot)
                printf(" %c", NBroot->pr->info);
        NBInOrder(NBroot->nb);
    }
}

void ViewTraversalNB(NBTree NBroot)
{
    printf("\n\tNon Binary Tree");
    printf("\n\tLEVELORDER : ");
    NBLevelOrder(NBroot);
    printf("\n");
    printf("\tPOSTORDER : ");
    NBPostOrder(NBroot);
    printf("\n");
    printf("\tPREORDER  : ");
    NBPreOrder(NBroot);
    printf("\n");
    printf("\tINORDER   : ");
    NBInOrder(NBroot);
    printf("\n");
}

/* Traversal Binary Tree*/
void BLevelOrder(BTree Broot)
{
    if (Broot == NULL)
    {
        return;
    }

    NBTree NBroot;
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    enqueue(&q, NBroot, Broot);

    while (q.front != NULL)
    {
        Baddr node = q.front->dataB;
        dequeue(&q);

        // Proses data pada node (misalnya, cetak info node)
        printf(" %c", node->info);

        // Jika node memiliki anak kiri, tambahkan anak kiri ke dalam queue
        if (node->left != NULL)
        {
            enqueue(&q, NBroot, node->left);
        }
        // Jika node memiliki anak kanan, tambahkan anak kanan ke dalam queue
        if (node->right != NULL)
        {
            enqueue(&q, NBroot, node->right);
        }
    }
}

void BPostOrder(BTree Broot)
{
    if (Broot != NULL)
    {
        BPostOrder(Broot->left);
        BPostOrder(Broot->right);
        printf(" %c", Broot->info);
    }
}

void BPreOrder(BTree Broot)
{
    if (Broot != NULL)
    {
        printf(" %c", Broot->info);
        BPreOrder(Broot->left);
        BPreOrder(Broot->right);
    }
}

void BInOrder(BTree Broot)
{
    if (Broot != NULL)
    {
        BInOrder(Broot->left);
        printf(" %c", Broot->info);
        BInOrder(Broot->right);
    }
}

void ViewTraversalB(BTree Broot)
{
    print_tree(Broot, 0);
    printf("\tLEVELORDER : ");
    BLevelOrder(Broot);
    printf("\n");
    printf("\tPOSTORDER : ");
    BPostOrder(Broot);
    printf("\n");
    printf("\tPREORDER  : ");
    BPreOrder(Broot);
    printf("\n");
    printf("\tINORDER   : ");
    BInOrder(Broot);
    printf("\n");
}

void ViewTraversal(NBTree NBroot, BTree Broot, BTree AVLroot)
{
    if (NBroot == NULL)
    {
        printf("\n\tTree masih kosong!\n");
    }
    else
    {
        ViewTraversalNB(NBroot);
        printf("\n\tBinary Tree\n");
        ViewTraversalB(Broot);
        printf("\n\tAVL Tree\n");
        ViewTraversalB(AVLroot);
    }
}

void DeleteNodeNB(NBTree *NBroot, infotype info)
{
    NBaddr toDelete = SearchNBnode(*NBroot, info);

    if (toDelete == NULL)
    {
        printf("\nNode not Found!\n");
        return;
    }
    if (toDelete->pr == NULL)
    {
        DeleteRootNB(NBroot, toDelete);
        printf("\nRoot Node Deleted!\n");
    }
    else if (IsLeafNB(toDelete))
    {
        DeleteLeafNB(NBroot, toDelete);
        printf("\nLeaf Node Deleted!\n");
    }
    else
    {
        DeleteStemNB(&(*NBroot), toDelete);
        printf("\nStem Node Deleted!\n");
    }
}

void DeleteRootNB(NBTree *NBroot, NBaddr toDelete)
{
    NBaddr child = NULL;

    if (IsLeafNB(toDelete))
    {
        *NBroot = NULL;
    }
    else
    {
        child = toDelete->fs;
        child->pr = NULL;
        UpgradePositionNB(&child);
        *NBroot = child;
    }
    free(toDelete);
}

void DeleteLeafNB(NBTree *NBroot, NBaddr toDelete)
{
    NBaddr parent = SearchBeforeNB(*NBroot, toDelete);

    if (parent == NULL)
    {
        return;
    }
    else if (parent->fs == toDelete)
    {
        if (toDelete->nb != NULL)
        {
            parent->fs = toDelete->nb;
        }
        else
        {
            parent->fs = NULL;
        }
    }
    else
    {
        parent = parent->nb;
        while (parent->nb != toDelete)
        {
            parent = parent->nb;
        }
        if (toDelete->nb != NULL)
        {
            parent->nb = toDelete->nb;
        }
        else
        {
            parent->nb = NULL;
        }
    }
    free(toDelete);
}

void DeleteStemNB(NBTree *NBroot, NBaddr toDelete)
{
    NBaddr child = toDelete->fs;
    NBaddr nextBrother = NULL;
    NBaddr prevBrother = NULL;

    child->pr = toDelete->pr;
    if (SearchBeforeNB(*NBroot, toDelete) == NULL)
    {
        toDelete->pr->fs = child;
        if (toDelete->nb == NULL)
        {
            UpgradePositionNB(&child);
        }
        else
        {
            nextBrother = toDelete->nb;
            UpgradePositionNB(&child);
            child->nb = nextBrother;
        }
    }
    else
    {
        nextBrother = toDelete->nb;
        UpgradePositionNB(&child);
        child->nb = nextBrother;
        prevBrother = SearchBeforeNB(*NBroot, toDelete);
        if (prevBrother->fs == toDelete)
        {
            prevBrother->fs = child;
        }
        else
        {
            prevBrother->nb = child;
        }
    }
    free(toDelete);
}

/* Modul Pembantu Untuk Delete Non Binary Tree */
bool IsLeafNB(NBTree NBroot)
{
    if (NBroot->fs == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void UpgradePositionNB(NBaddr *node)
{
    NBaddr lastChild = NULL;
    NBaddr sibling = NULL;

    if ((*node)->fs && (*node)->nb)
    {
        lastChild = (*node)->fs;
        while (lastChild->nb)
        {
            lastChild = lastChild->nb;
        }
        sibling = (*node)->nb;
        lastChild->nb = sibling;
        (*node)->nb = NULL;
        while (sibling)
        {
            sibling->pr = *node;
            sibling = sibling->nb;
        }
    }
    else if ((*node)->fs == NULL)
    {
        sibling = (*node)->nb;
        (*node)->nb = NULL;
        (*node)->fs = sibling;
        while (sibling)
        {
            sibling->pr = *node;
            sibling = sibling->nb;
        }
    }
}

void nbTreeToFile(NBTree root, FILE *fp)
{
    if (root == NULL)
    {
        return;
    }

    NBaddr child = root->fs; // pointer ke node anak pertama
    if (root->pr == NULL)
    {
        // jika root, simpan dengan parent 0
        fprintf(fp, "(%c, %c) ", '0', root->info);
    }
    while (child != NULL)
    {
        // menyimpan pasangan (parent, child) ke file
        fprintf(fp, "(%c, %c) ", root->info, child->info);

        // rekursif untuk setiap anak
        nbTreeToFile(child, fp);

        // menuju sibling berikutnya
        child = child->nb;
    }
}

void saveNBTreeToFile(NBTree root, char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Gagal membuka file\n");
        return;
    }

    nbTreeToFile(root, fp); // menyimpan data ke file
    fclose(fp);             // menutup file
    printf("Save Berhasil!\n");
}

void insertNBTreeFromFile(NBTree *NBroot, char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Gagal membuka file");
        return;
    }

    char parent, node;
    while (fscanf(fp, "(%c, %c) ", &parent, &node) != EOF)
    {
        InsertNBnode(&(*NBroot), SearchNBnode(*NBroot, parent), node);
    }

    fclose(fp);
    printf("Insert From File Berhasil!\n");
}

int menu()
{
    int nilai;
    char input[5];
awal:
    printf("PROGRAM KONVERSI NON BINARY TREE - BINARY TREE MENGGUNAKAN AVL\n");
    printf("D4 Teknik Informatika - 1B\n");
    printf("~ Bhisma Chandra Yudha - 221524037\n");
    printf("~ Sarah - 221524059\n");
    printf("~ Zahran Anugerah Rizqullah - 221524063\n\n");
    printf("1. Input Tree\n");
    printf("2. Edit Tree\n");
    printf("3. Delete Node\n");
    printf("4. Delete Tree\n");
    printf("5. Convert, Search(Level/Depth) & Print Tree (Traversal)\n");
    printf("6. Save Tree To File\n");
    printf("7. Exit\n");
    printf("Pilihan Anda: ");
    scanf(" %s", input);

    for (int i = 0; input[i]; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("\nMasukkan angka bukan huruf!\n");
            system("pause");
            system("cls");
            goto awal;
        }
    }

    nilai = atoi(input);

    if (nilai < 1 || nilai > 8)
    {
        printf("Masukkan angka dari 1-7 !\n");
        system("pause");
        system("cls");
        goto awal;
    }
    else
    {
        return nilai;
    }
}

void nbInput(NBTree *NBroot)
{
    infotype parent;
    infotype nama;
    if (*NBroot == NULL)
    {
        printf("DAFTAR PARENTS\n");
        printf("Tree Masih Kosong!\n");
    }
    else
    {
        printf("DAFTAR PARENTS\n");
        listParent(*NBroot);
    }
    printf("Masukkan Nama Node Yang Akan Dimasukkan: ");
    scanf(" %c", &nama);
    if (*NBroot == NULL)
    {
        InsertNBnode(&(*NBroot), SearchNBnode(*NBroot, '0'), nama);
        printf("\nInput Berhasil!\n");
    }
    else
    {
    a:
        printf("Masukkan Nama Parent: ");
        scanf(" %c", &parent);
        if (SearchNBnode((*NBroot), parent) == NULL)
        {
            printf("\nInput Gagal! Masukkan Nama Parent yang sesuai\n");
            goto a;
        }
        else
        {
            InsertNBnode(&(*NBroot), SearchNBnode((*NBroot), parent), nama);
            printf("\nInput Berhasil!\n");
        }
    }
}

void listParent(NBaddr NBroot)
{
    if (NBroot != NULL)
    {
        printf("~ %c.\n", NBroot->info);
        listParent(NBroot->fs);
        listParent(NBroot->nb);
    }
}

void deleteNode(NBTree *NBroot)
{
    infotype nama;
    if (*NBroot == NULL)
    {
        printf("Tree Masih Kosong!\n");
        return;
    }
    printf("DAFTAR PARENTS\n");
    listParent(*NBroot);
    printf("Masukkan Node Yang Ingin Dihapus: ");
    scanf(" %c", &nama);
    DeleteNodeNB(&(*NBroot), nama);
}

void editTree(NBTree *NBroot)
{
    NBaddr change;
    infotype oldname, newname;

    if ((*NBroot) == NULL)
    {
        printf("\nTree Belum Dibuat!\n");
    }
    else
    {
    ulang:
        printf("DAFTAR PARENTS\n");
        listParent(*NBroot);
        printf("\nMasukkan Nama Yang Ingin Diedit: ");
        scanf(" %c", &oldname);
        change = SearchNBnode(*NBroot, oldname);
        if (change != NULL)
        {
            printf("Masukan Nama Baru: ");
            scanf(" %c", &newname);
            change->info = newname;
            printf("\nUpdate Sukses!\n");
        }
        else
        {
            printf("\nNama Tidak Ada, Ulangi. \n");
            system("pause");
            goto ulang;
        }
    }
}

void deleteTree(NBTree *NBroot, BTree *Broot, BTree *AVLroot)
{
    if (*NBroot == NULL)
    {
        printf("Tree Masih Kosong!\n");
        return;
    }
    DeleteNBtree(&(*NBroot));
    DeleteBtree(&(*Broot));
    DeleteBtree(&(*AVLroot));
    printf("Tree berhasil dihapus!\n");
}

void DeleteNBtree(NBTree *NBroot)
{
    if (*NBroot == NULL)
    {
        return;
    }
    DeleteNBtree(&(*NBroot)->fs);
    DeleteNBtree(&(*NBroot)->nb);
    free(*NBroot);
    *NBroot = NULL;
}
void DeleteBtree(BTree *Broot)
{
    if (*Broot == NULL)
    {
        return;
    }
    DeleteBtree(&((*Broot)->left));
    DeleteBtree(&((*Broot)->right));
    free(*Broot);
    *Broot = NULL;
}

int depth(BTree node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        if (leftDepth > rightDepth) {
            return (leftDepth + 1);
        } else {
            return (rightDepth + 1);
        }
    }
}

int findLevel(BTree node, char data, int level) {
    if (node == NULL) {
        return 0;
    }
    if (node->info == data) {
        return level;
    }
    int downLevel = findLevel(node->left, data, level + 1);
    if (downLevel != 0) {
        return downLevel;
    }
    downLevel = findLevel(node->right, data, level + 1);
    return downLevel;
}

void print_tree(BTree tree, int level) {
    if (tree != NULL) {
        print_tree(tree->right, level+1);
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        printf("-> %c\n", tree->info);
        print_tree(tree->left, level+1);
    }
<<<<<<< Updated upstream

void print_tree(BTree tree, int level) {
    if (tree != NULL) {
        print_tree(tree->right, level+1);
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        printf("-> %c\n", tree->info);
        print_tree(tree->left, level+1);
    }
}
>>>>>>> Stashed changes
