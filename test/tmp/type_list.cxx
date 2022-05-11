#include <sdi/tmp/type_list.hxx>

using namespace sdi::tmp;

static_assert(type_list<>::size == 0, "Size should be 0");
static_assert(type_list<int>::size == 1, "Size should be 1");
static_assert(type_list<int, char>::size == 2, "Size should be 2");
static_assert(type_list<int, char, float>::size == 3, "Size should be 3");

using unique = make_unique_t<type_list<int, int, float, double, float, char, double>>;
static_assert(std::is_same<unique, type_list<int, float, char, double>>::value, "List should only contain unique values");
