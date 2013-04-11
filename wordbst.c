#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//4/10/2013 CS1
//Program to take in words from file and insert them
//into dynamically allocated binary search tree.

FILE *ifp;

typedef struct node_t{
    char *word;
    struct node_t *left, *right;
}node_t;

/**Function Prototypes**/
node_t *create_node(char* words);
node_t *insert(node_t *root, node_t* element);
void printTree(node_t* myTree);
node_t* findNode(node_t *p, char* words);
node_t* findSubtree(node_t *p, char* words);
int findHeight(node_t* p);

int main()
{
    int i, n, numNodes, commands, code, height = 0;
    char words[31];

    node_t* my_root = NULL, *temp_node;

    ifp = fopen("words.txt", "r");

    fscanf(ifp, "%d", &numNodes);

    for(i = 0; i < numNodes; i++){

        //Scan in words
        fscanf(ifp, "%s", &words);

        //Create nodes with the words in a node
        temp_node = create_node(words);

        //Insert node
        my_root = insert(my_root, temp_node);
    }


                /***COMMANDS***/

    //Scans for the number of commands to receive
    fscanf(ifp, "%d", &commands);

    //For each command, execute an operation
    for(n = 0; n < commands; n++){
    fscanf(ifp, "%d", &code);

        switch (code){
            case 1:
                //Insert Word
                fscanf(ifp, "%s", &words);
                temp_node = create_node(words);
                my_root = insert(my_root, temp_node);
                printf("Inserted %s.\n", words);
                break;

            case 2:
              //Is word in tree?
              fscanf(ifp, "%s", &words);
              findNode(my_root, words);
              break;

            case 3:
                //Print tree height
                height = findHeight(my_root);
                printf("The height is %d.\n", height);

                break;

            case 4:
                //Find the word and print the height where the word is
                fscanf(ifp, "%s", words);
                findSubtree(my_root, words);
                break;

            case 5:
                //print in-order
                printTree(my_root);
                printf("\n");
                break;
            }
    }

    fclose(ifp);
    return 0;
}

node_t *create_node(char* words){
    int numChars;
    node_t* temp;
    temp = (node_t*)malloc(sizeof(node_t));

    //Determine length of word + \n
     numChars = strlen(words)+1;

    //Dynamically allocate for each word in struct
    temp->word = (char*)malloc(sizeof(char*) * numChars);

    //and use strcpy to move the string stored at words into the new memory at temp->word
    strcpy(temp->word, words);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node_t *insert(node_t *root, node_t* element){

    //Base case, if inserting into an already empty tree
    if(root == NULL){
        return element;

    }
    else{
        //If the new element is 'less than' the root, go left
       if(strcmp(element->word, root->word) < 0){

            //If there is a subtree to the left, move that way and recursively
            //call
            if (root->left != NULL)
                root->left = insert(root->left, element);

            //If there is no subtree, put element there
            else{
                root->left = element;
            }
       }
        else{

            //Same as above but to the right
            if(root->right != NULL)
                root->right = insert(root->right, element);

            else
                root->right = element;
        }
            return root;
    }
}

//Print the tree inorder
void printTree(node_t* myTree){
     // Only traverse the node if it's not null.
  if (myTree != NULL) {
    printTree(myTree->left); // Go Left.
    printf("%s ", myTree->word); // Print the root.
    printTree(myTree->right); // Go Right.
  }
}

//Searchs tree to find where target word is located
//Prints whether it's been found or not
node_t* findNode(node_t *p, char* words) {

  // Check if there are nodes in the tree.
  if (p != NULL) {

    // Found it!
    if (strcmp(p->word, words) == 0){
      printf("%s is present.\n", words);
      return p;
    }

    // Search to the left, call again after

    if (strcmp(words, p->word) < 0)
      return findNode(p->left, words);

    // Right
    else
      return findNode(p->right, words);
  }

  else
    //End case, couldn't find it
    printf("%s is not present.\n", words);
    return NULL;
}

//Almost carbon copy of findNode, except
//it keeps it calls to findHeight from where ever
//the target word was found, then calculates from there
node_t* findSubtree(node_t *p, char* words) {

  // Check if there are nodes in the tree.
  if (p != NULL) {

    // Found the value at the root.
    if (strcmp(p->word, words) == 0){
        int height = 0;
        height = findHeight(p);
        printf("The height of the subtree at %s is %d.\n", words, height);
      return p;
    }

    // Search to the left.
    if (strcmp(words, p->word) < 0)
      return findSubtree(p->left, words);

    // Or...search to the right.
    else
      return findSubtree(p->right, words);
  }

  else
    printf("%s is not present.\n", words);
    return NULL; // No node found.
}

//Finds height of the tree from root
int findHeight(node_t* p)
{
    //Base case, if tree has no elements
    if(p == 0)
        return -1;

    int left_height = findHeight(p->left);
    int right_height = findHeight(p->right);

    if(left_height > right_height)
        return left_height + 1;
    else
        return right_height +1;
}
