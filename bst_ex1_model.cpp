/*
1. Se va introduce urmatoarea secventa de chei numerice intr-un arbore binar ordonat (ABO): 12, -7,
45, 32, 2, 22, 1, 2, 3, 4, 9, 90, 89, 225, 0. Se va respecta ordinea din secventa.
a) sa se determine daca arborele binar ordonat obtinut in urma insertiilor este echilibrat in sens
AVL sau nu.
b) se vor sterge din ABO toate numerele pare si se va afisa rezultatul folosind parcurgerea
inordine.

*/

#include <bits/stdc++.h>

using namespace std;

typedef struct Nod
{
    int key;
    int ech;
    int height;
    Nod *left;
    Nod *right;
    Nod *parent;
} Node;

bool isEch = true;

Node *newNode(int key)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->ech = 0;
    temp->height = 1;
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}

int height(Node *lista)
{
    if (!lista)
        return 0;
    return lista->height;
}

Node *add_lista(Node *lista, int key)
{

    if (!lista)
    {
        lista = newNode(key);
        return lista;
    }
    if (key < lista->key)
    {
        lista->left = add_lista(lista->left, key);
        lista->left->parent = lista;
        // lista->left->height = lista->height + 1;
    }
    else if (key > lista->key)
    {
        lista->right = add_lista(lista->right, key);
        lista->right->parent = lista;
        // lista->right->height = lista->height + 1;
    }
    else
    {
        return lista;
    }

    lista->height = 1 + max(height(lista->left), height(lista->right));

    return lista;
}
void inOrder(Node *lista)
{
    if (lista)
    {
        inOrder(lista->left);
        cout << lista->key << " h:" << lista->ech << endl;
        inOrder(lista->right);
    }
}
void setEch(Node *lista)
{
    if (lista)
    {
        setEch(lista->left);

        lista->ech = height(lista->left) - height(lista->right);

        setEch(lista->right);
    }
}
void checkEch(Node *lista)
{
    if (lista)
    {
        checkEch(lista->left);

        if (lista->ech < -1 || lista->ech > 1)
        {
            isEch = false;
        }

        checkEch(lista->right);
    }
}
void deleteNode(Node* node)
{
    if(node)
    {
        deleteNode(node->left);
        //node->left = NULL;
        deleteNode(node->right);
        // node->right = NULL;
        free(node);
        node = NULL;
    }
}
void deletePare(Node* lista)
{
    if(lista)
    {
        deletePare(lista->left);
        if(lista->key % 2 == 0)
        {
            if(!lista->parent == NULL)
                if(lista->key > lista->parent->key)
                {
                    lista->parent->right = NULL;
                }
                else
                {
                    lista->parent->left = NULL;
                }
            deleteNode(lista);
        }
        else
            deletePare(lista->right);
        
    }
}
int main()
{
    Node *lista;

    // lista = add_lista(lista, 12);
    // lista = add_lista(lista, -7);
    // lista = add_lista(lista, 45);
    // lista = add_lista(lista, 32);
    // lista = add_lista(lista, 2);
    // lista = add_lista(lista, 22);
    // lista = add_lista(lista, 1);
    // lista = add_lista(lista, 2);
    // lista = add_lista(lista, 3);
    // lista = add_lista(lista, 4);
    // lista = add_lista(lista, 9);
    // lista = add_lista(lista, 90);
    // lista = add_lista(lista, 89);
    // lista = add_lista(lista, 225);
    // lista = add_lista(lista, 0);
    
    lista = add_lista(lista, 25);
    lista = add_lista(lista, 21);
    lista = add_lista(lista, 10);
    lista = add_lista(lista, 22);
    lista = add_lista(lista, 41);
    lista = add_lista(lista, 30);
    lista = add_lista(lista, 50);

    setEch(lista);
    checkEch(lista);
    if(isEch)
        cout << "\nEchilibrat!\n";
    else
        cout << "\nNu e echilibrat!\n";
    isEch = true;

    if(lista->key % 2 == 0)
    {
        deletePare(lista);
        lista = NULL;
    }
    else
        deletePare(lista);

    cout << "Keys: " << endl;
    inOrder(lista);

    return 0;
}
