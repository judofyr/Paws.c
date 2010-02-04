#include "ll.c"

#include <stdbool.h>
/* FIXME: These shouldn’t depend on `list.c` */
#ifndef LIST_H_INCLUDED
#  include "Paws.o/list/list.h"
#endif

#ifndef CEST_H_INCLUDED
#  include "Cest.h"
#endif

#define A_LIST \
  List.to_thing(List.create())

CEST(LL, create) {
  ll a_ll;
  
  a_ll = LL.create();
  ASSERT( a_ll->first  == NULL );
  ASSERT( a_ll->last   == NULL );
  ASSERT( a_ll->length == 0    );
  
  return true;
}

/*
CEST(LL, anterior_insert) {
  return true;
}

CEST(LL, posterior_insert) {
  return true;
}
*/

CEST(LL, prefix) {
  ll    a_ll;
  node  node1, node2, node3;
  
  node1 = Node.create(A_LIST);
  node2 = Node.create(A_LIST);
  node3 = Node.create(A_LIST);
  
  a_ll = LL.create();
  LL.prefix(a_ll, node3);
  ASSERT( a_ll->length == 1     );
  ASSERT( a_ll->first  == node3 );
  ASSERT( a_ll->last   == node3 );
  
  LL.prefix(a_ll, node2);
  ASSERT( a_ll->length == 2     );
  ASSERT( a_ll->first  == node2 );
  ASSERT( a_ll->last   == node3 );
  
  LL.prefix(a_ll, node1);
  ASSERT( a_ll->length == 3     );
  ASSERT( a_ll->first  == node1 );
  ASSERT( a_ll->last   == node3 );
  
  return true;
}

CEST(LL, affix) {
  ll    a_ll;
  node  node1, node2, node3;
  
  node1 = Node.create(A_LIST);
  node2 = Node.create(A_LIST);
  node3 = Node.create(A_LIST);
  
  a_ll = LL.create();
  LL.affix(a_ll, node1);
  ASSERT( a_ll->length == 1     );
  ASSERT( a_ll->first  == node1 );
  ASSERT( a_ll->last   == node1 );
  
  LL.affix(a_ll, node2);
  ASSERT( a_ll->length == 2     );
  ASSERT( a_ll->first  == node1 );
  ASSERT( a_ll->last   == node2 );
  
  LL.affix(a_ll, node3);
  ASSERT( a_ll->length == 3     );
  ASSERT( a_ll->first  == node1 );
  ASSERT( a_ll->last   == node3 );
  
  return true;
}

CEST(LL, at) {
  ll    a_ll;
  node  node1, node2, node3;
  
  a_ll = LL.create();
  ASSERT( LL.at(a_ll,  5) == NULL );
  ASSERT( LL.at(a_ll,  1) == NULL );
  ASSERT( LL.at(a_ll,  0) == NULL );
  ASSERT( LL.at(a_ll, -1) == NULL );
  ASSERT( LL.at(a_ll, -5) == NULL );
  
  node1 = Node.create(A_LIST); LL.affix(a_ll, node1);
  node2 = Node.create(A_LIST); LL.affix(a_ll, node2);
  node3 = Node.create(A_LIST); LL.affix(a_ll, node3);
  
  ASSERT( LL.at(a_ll, 0) == node1 ); /* FAIL */
  ASSERT( LL.at(a_ll, 1) == node2 ); /* FAIL */
  ASSERT( LL.at(a_ll, 2) == node3 ); /* FAIL */
  
  return true;
}


CEST(Node, create) {
  node  a_node;
  
  a_node = Node.create( A_LIST );
  ASSERT( a_node->next     == NULL );
  ASSERT( a_node->previous == NULL );
  
  return true;
}

CEST(Node, prefix) {
  node  node1, node2, node3,
        nodeA, nodeB, nodeC;
  
  node1 = Node.create(A_LIST),
  node2 = Node.create(A_LIST),
  node3 = Node.create(A_LIST);
  
  
  /* A basic single prefix */
  /* > [***] node3
   * 
   *         node1
   * > [***]    └→ node3
   * 
   * > [***] node1 node3
   */
  Node.prefix(node3, node1);
  ASSERT( node1->previous == NULL  && node1->next == node3 );
  ASSERT( node3->previous == node1 && node3->next == NULL  );
  
  
  /* A single prefix that pushes old nodes */
  /* > [***] node1 node3
   * 
   *               node2
   * > [***] node1    └→ node3
   * 
   * > [***] node1 node2 node3
   */
  Node.prefix(node3, node2);
  ASSERT( node1->previous == NULL  && node1->next == node2 );
  ASSERT( node2->previous == node1 && node2->next == node3 );
  ASSERT( node3->previous == node2 && node3->next == NULL  );
  
  nodeA = Node.create(A_LIST),
  nodeB = Node.create(A_LIST),
  nodeC = Node.create(A_LIST);
  Node.affix(nodeA, nodeB);
  Node.affix(nodeB, nodeC);
  
  
  /* A splicing-prefix that pushes old nodes */
  /* > [***] node1 node2 node3
   * 
   * > [***] nodeA nodeB nodeC
   * > [***] node1    └→ node2 node3
   * 
   * > [***] nodeA nodeB node2 node3
   *   [***] node1   …   [***] nodeC
   */
  Node.prefix(node2, nodeB);
  ASSERT( nodeA->previous == NULL  && nodeA->next == nodeB );
  ASSERT( nodeB->previous == nodeA && nodeB->next == node2 );
  ASSERT( node2->previous == nodeB && node2->next == node3 );
  ASSERT( node3->previous == node2 && node3->next == NULL  );
  
  ASSERT( nodeC->previous != nodeB );
  ASSERT( node1->next     != node2 );
  
  
  return true;
}

CEST(Node, affix) {
  node  node1, node2, node3,
        nodeA, nodeB, nodeC;
  
  node1 = Node.create(A_LIST),
  node2 = Node.create(A_LIST),
  node3 = Node.create(A_LIST);
  
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Node.affix(node1, node3);
  ASSERT( node1->previous == NULL  && node1->next == node3 );
  ASSERT( node3->previous == node1 && node3->next == NULL  );
  
  
  /* A single affix that pushes old nodes */
  /* > node1 node3 [***]
   * 
   *         node2
   * > node1 ←┘    node3 [***]
   * 
   * > node1 node2 node3 [***]
   */
  Node.affix(node1, node2);
  ASSERT( node1->previous == NULL  && node1->next == node2 );
  ASSERT( node2->previous == node1 && node2->next == node3 );
  ASSERT( node3->previous == node2 && node3->next == NULL  );
  
  nodeA = Node.create(A_LIST),
  nodeB = Node.create(A_LIST),
  nodeC = Node.create(A_LIST);
  Node.affix(nodeA, nodeB);
  Node.affix(nodeB, nodeC);
  
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC [***]
   *   nodeA [***]   …   node3 [***]
   */
  Node.affix(node2, nodeB);
  ASSERT( node1->previous == NULL  && node1->next == node2 );
  ASSERT( node2->previous == node1 && node2->next == nodeB );
  ASSERT( nodeB->previous == node2 && nodeB->next == nodeC );
  ASSERT( nodeC->previous == nodeB && nodeC->next == NULL  );
  
  ASSERT( node3->previous != node2 );
  ASSERT( nodeA->next     != nodeB );
  
  
  return true;
}