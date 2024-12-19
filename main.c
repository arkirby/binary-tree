#include <stdio.h>
#include <stdlib.h>

// define the node structure
typedef struct Node
{
  int data;
  struct Node *left;
  struct Node *right;
  struct Node *peer;
} Node;

// function to create a new node
Node *create(int data)
{
  Node *node = (Node *)malloc(sizeof(Node));

  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->peer = NULL;

  return node;
}

// function to insert a left child
Node *insleft(int data, Node *parent)
{
  Node *node = create(data);
  parent->left = node;

  return node;
}

// function to insert a right child
Node *insright(int data, Node *parent)
{
  Node *node = create(data);
  parent->right = node;

  return node;
}

// function to find the next available peer node.
Node *findpeer(Node *peer)
{
  if (peer->left != NULL) // if there is a left child, return it
    return peer->left;
  else if (peer->right != NULL) // if there is a right child, return it
    return peer->right;
  else if (peer->peer != NULL) // if there is a peer, call find peer on the peer
    return findpeer(peer->peer);
  else
    return NULL; // if there is no peer, return NULL
}

// function to set the peer nodes
void setchildpeers(Node *node)
{
  if (node == NULL)
    return;

  // if the node has a left child and a right child, set the left child's peer
  // to the right child and if there is a left child and a peer, but no right child,
  // set the left child's peer to the next available peer node.
  if (node->left != NULL)
    if (node->right != NULL)
      node->left->peer = node->right;
    else if (node->peer != NULL)
      node->left->peer = findpeer(node->peer);

  // if the node has a right child and a peer, then set the right child's peer
  // to the next available peer node.
  if (node->right != NULL && node->peer != NULL)
    node->right->peer = findpeer(node->peer);

  setchildpeers(node->right);
  setchildpeers(node->left);
}

// initialize the tree based on the diagram in the README
Node *initializeTree()
{
  Node *n1 = create(1);
  n1->data = 1;

  // commented out nodes below are to make the tree resemble the diagram
  // in the README
  Node *n2 = insleft(2, n1);
  Node *n3 = insright(3, n1);
  Node *n4 = insleft(4, n2);
  Node *n5 = insright(5, n2);
  Node *n6 = insleft(6, n3);
  Node *n7 = insright(7, n3);
  // Node *n8 = insleft(8, n4);
  Node *n9 = insright(9, n4);
  Node *n10 = insleft(10, n5);
  Node *n11 = insright(11, n5);
  // Node *n12 = insleft(12, n6);
  // Node *n13 = insright(13, n6);
  Node *n14 = insleft(14, n7);
  Node *n15 = insright(15, n7);
  // Node *n16 = insleft(16, n8);
  // Node *n17 = insright(17, n8);
  // Node *n18 = insleft(18, n9);
  // Node *n19 = insright(19, n9);
  Node *n20 = insleft(20, n10);
  // Node *n21 = insright(21, n10);
  // Node *n22 = insleft(22, n11);
  // Node *n23 = insright(23, n11);
  // Node *n24 = insleft(24, n14);
  // Node *n25 = insright(25, n14);
  Node *n26 = insleft(26, n15);
  // Node *n27 = insright(27, n15);

  return n1;
}

// prints out the tree and the data from each node's peer if it has a peer
void printtree(Node *node)
{
  if (node == NULL)
    return;

  printf("Node: %02d   [ ", node->data);
  if (node->peer != NULL)
    printf("peer: %02d   ", node->peer->data);
  else
    printf("peer:      ");

  if (node->left != NULL)
    printf("left: %02d   ", node->left->data);
  else
    printf("left:      ");

  if (node->right != NULL)
    printf("right: %02d ]\n", node->right->data);
  else
    printf("right:    ]\n");

  printtree(node->left);
  printtree(node->right);
}

int main()
{
  // initialize the tree
  Node *tree = initializeTree();

  // go through the tree and set the peer nodes
  setchildpeers(tree);

  // print the tree
  printtree(tree);

  return 0;
}