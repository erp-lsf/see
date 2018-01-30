#include <criterion/criterion.h>
#include "string_utils.c"

Test(simple, test) {
  cr_assert(0, "Hello World\n");
}

Test(another_test, test) {
  cr_assert(1);
}
