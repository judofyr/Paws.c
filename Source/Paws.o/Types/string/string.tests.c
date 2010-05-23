#include "string.c"
#include "Cest.h"


CEST(String, allocate) {
  string  a_string;
  
  a_string = String->allocate("foo", 4);
  ASSERT( a_string->content->first  == NULL );
  ASSERT( a_string->content->last   == NULL );
  ASSERT( a_string->content->length == 0    );
  
  a_string = String->allocate("bar", 4);
  ASSERT( strcmp(a_string->native.short_array, "bar") == 0 );
  ASSERT( a_string->bytes == 4 );
  
  a_string = String->allocate(
    "May the forces of evil become confused on the way to your house.", 65);
  ASSERT( strcmp(a_string->native.otherwise.long_array,
    "May the forces of evil become confused on the way to your house.") == 0 );
  ASSERT( a_string->bytes == 65 );
  
  SUCCEED;
}

CEST(string, thing) {
  string  a_string = String->allocate("", 1);
  
  ASSERT( String->thing(a_string).isa            == STRING   );
  ASSERT( String->thing(a_string).pointer.string == a_string );
  
  SUCCEED;
}

CEST(string, native) {
  string  a_string;
  
  a_string = String->allocate("foo", 4);
  ASSERT( strcmp(String->native(a_string), "foo") == 0 );
  
  a_string = String->allocate(
    "May the forces of evil become confused on the way to your house.", 65);
  ASSERT( strcmp(String->native(a_string),
    "May the forces of evil become confused on the way to your house.") == 0 );
  
  SUCCEED;
}
