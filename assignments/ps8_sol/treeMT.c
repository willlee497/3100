#include "treeMT.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Tree* makeEmptyTree()
{
    /* TODO: 
     * Create a new Tree, setting the root to NULL. Initialize any necessary mutexes. 
     * Return Tree*.
    */
   Tree * t = (Tree*)malloc(sizeof(Tree));
   pthread_mutex_init(&t->lock, NULL);
   t->root = NULL;
   return t;

}

void insertIntoTree(Tree* t, int val)
{
    /* TODO: 
     * This function should construct a new Node, traverse the BST to find the correct insertion location, and insert it. 
     * If there is already a node with that value, nothing needs to be inserted.
     * Use mutexes to prevent threads from interfering with one another. 
     * Read the description in the pdf for more instructions.  
    */
   TNode* new = (TNode*)malloc(sizeof(TNode));
   new->left = NULL; new->right = NULL; new->val = val; pthread_mutex_init(&new->lock, NULL);
   
   pthread_mutex_lock(&t->lock);
   TNode* cur = t->root;
   TNode* parent = NULL;
   if(cur == NULL){

        t->root = new;
        pthread_mutex_unlock(&t->lock);

   }

    pthread_mutex_unlock(&t->lock);


    
    while(cur != NULL){
        pthread_mutex_lock(&cur->lock);
        if(cur->val == val){
            pthread_mutex_unlock(&cur->lock);
            return;
        }

        parent = cur;

        if(cur->val > val){
            if(cur->left == NULL){
                cur->left = new;
                pthread_mutex_unlock(&cur->lock);
                return;

            }else{
                cur = cur->left;
                pthread_mutex_unlock(&parent->lock);
            }

        } else if(cur->val < val){
            if(cur->right == NULL){
                cur->right = new;
                pthread_mutex_unlock(&cur->lock);
                return;

            }else{
                cur = cur->right;
                pthread_mutex_unlock(&parent->lock);
            }
        }
    }

}

void printTreeAux(TNode* root)
{
    if (root == NULL)
        return;
    else {
        printf("(");
        printTreeAux(root->left);
        printf(" %d ",root->val);
        printTreeAux(root->right);
        printf(")");      
    }
}

void printTree(Tree* t)
{
    printTreeAux(t->root);
}

void destroyTreeAux(TNode* root)
{
    if(root != NULL){
        destroyTreeAux(root->left);
        destroyTreeAux(root->right);
        pthread_mutex_destroy(&root->lock);
        free(root);
    }
}

void destroyTree(Tree* t)
{
    destroyTreeAux(t->root);
    pthread_mutex_destroy(&t->lock);
    free(t);
}


