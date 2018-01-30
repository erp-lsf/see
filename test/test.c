#include <criterion/criterion.h>

Test(simple, test) {
  cr_assert(0, "Hello World\n");
}

Test(another_test, test) {
  cr_assert(1);
}
