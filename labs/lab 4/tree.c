#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TNode{
  char* val;
  struct TNode* left;
  struct TNode* right;
} TNode;

TNode* makeEmptyTree()
{
   return NULL;
}

TNode* insertIntoTree(TNode* root,char* string)
{
  

  /*
    TODO: Insert the string into the tree. First, check if the root is NULL. If it is, then create a new TNode, copy the string into it, and return the pointer to the new TNode. 

    If root is not NULL, then compare root->val and string using strcmp. If root->val < string, then call insertIntoTree again on root->left. Keep in mind that root->left might be NULL. If root->val > string, then call insertIntoTreeAgain on root->right. Again, root->right might be NULL. If root->val is equal to string, then the string is already in the tree, and you don't need to do anything. In any case, return root.
   */
  if(root == NULL){
    root = (TNode*)malloc(sizeof(TNode));
    root->left = NULL;
    root->right = NULL;
    root->val = strdup(string);
    return root;
  }
  if(root != NULL){
    int val = strcmp(root->val, string);

    if(val > 0){
      root->left = insertIntoTree(root->left, string);
    }
    else if(val < 0){
      root->right = insertIntoTree(root->right, string);
    } 
    return root;
    
  }
}

TNode* searchTree(TNode* root, char* string)
{ 

  if(root){
    int val = strcmp(root->val, string);

    if(val == 0){
      return root;
    }
    else if(val < 0){
      return searchTree(root->right, string);
    }
    else{
      return searchTree(root->left, string);
    }
    /*
      TODO: Search the tree for the string. First, use strcmp to compare root->val to string. 

      If string == root->val, return the root. 

      If string < root->val, then call searchTree on the right child of root.

      If string > root->val, then call searchTree on the left child of root.
     */
  }else
    return NULL;
}

void printTree(TNode* root)
{
   if (root == NULL)
      return;
   else {
      printf("(");
      printTree(root->left);
      printf(" %s ",root->val);
      printTree(root->right);
      printf(")");      
   }
}

void destroyTree(TNode* root)
{
  /*
    TODO: Free the nodes in the tree, and the strings stored in those nodes. This is easier to do recursively. 
   */
  if(root == NULL){
    return;
  }
  destroyTree(root->left);
  destroyTree(root->right);

  free(root->val);
  free(root);
}




int main(int argc, char* argv[])
{
  if(argc != 2){
    printf("Usage: ./tree wordList\n");
    return 1;
  }
  TNode* tree = makeEmptyTree();
  /*
    TODO: The path to the file containing the words is stored in argv[1]. Call fopen to open it. 
   */
  char word[200];
  size_t length;
  FILE *f = fopen(argv[1], "r");
  if(f == NULL){
    printf("Could not open File\n");
    return 0;
  }

  while(!feof(f)){
    fscanf(f, "%s", word);
    tree = insertIntoTree(tree, word);
  }
  /*
    TODO: Use fscanf to read a word at a time from the file, and call insertIntoTree to insert the word into the tree.
   */
  /*
    TODO: fclose the file.
   */
  fclose(f);
  while(1){
    printf("word: ");
    int r = scanf("%s", word);
    if(r != 1)
      break;
    length = strlen(word);
    if(length < 1)
      break;
    TNode* node = searchTree(tree, word);
    if(node){
      printf("PRESENT\n");
    }else{
      printf("ABSENT\n");
    }    
  }
  destroyTree(tree);
  return 0;
}
