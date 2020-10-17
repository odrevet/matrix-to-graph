#ifndef EDGE_H
#define EDGE_H

#include "node.h"

/**
 @struct connexion between nodes
 @param the source node
 @param the destination node
 @param the weight of the node
*/

typedef struct
{
  node *src;
  node *dest;
  int i_weight;
} edge;

#endif
