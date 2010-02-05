#define LIST_H

#if !defined(CORE_H)
#  include "Paws.o/Core/Core.h"
#endif
#if !defined(LL_H)
#  include "Paws.o/Core/ll.h"
#endif

/* ======================
= `infrastructure list` =
====================== */

/* ### Data Types & Structures ### */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 */
struct list {
  ll  content; /* The `ll` behind this `list` */
};

/* ### Method Declarations ### */

struct List {
  /* `List` functions */
  list  (*create)         (void);
  list  (*create_naughty) (void);
  
  /* `struct list` methods */
  thing (*to_thing) (list);
  void  (*insert)   (list, thing, ll_usize);
  void  (*prefix)   (list, thing);
  void  (*affix)    (list, thing);
  thing (*at)       (list, ll_usize);
} const List;
