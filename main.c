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

int main()
{
  // create root node
  Node *n0 = (Node *)malloc(sizeof(Node));
  n0->data = 1;

  // create left child node
  Node *n2 = insleft(2, n0);

  // create left child node's children
  insleft(4, n2);
  insright(5, n2);

  // create right child node
  Node *n3 = insright(3, n0);

  // create right child node's children
  insleft(6, n3);
  insright(7, n3);

  // go through the tree and set the peer nodes
  setchildpeers(n0);

  return 0;
}