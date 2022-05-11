#include <sdi/tmp/generic.hxx>

struct foo {
};
struct bar {
};
struct baz {
};

using namespace sdi::tmp::generic;

static_assert(find_type_v<foo> == NOT_FOUND, "Type should not be found in empty haystack");
static_assert(find_type_v<foo, foo, bar, baz> == 0U, "Found index should be 0");
static_assert(find_type_v<bar, foo, bar, baz> == 1U, "Found index should be 1");
static_assert(find_type_v<baz, foo, bar, baz> == 2U, "Found index should be 2");
static_assert(find_type_v<int, foo, bar, baz> == NOT_FOUND, "Missing type should not be found in haystack");

static_assert(!contains_type_v<foo>, "Type should not be found in empty haystack");
static_assert(contains_type_v<foo, foo, bar, baz>, "Type should be found in haystack");
static_assert(contains_type_v<bar, foo, bar, baz>, "Type should be found in haystack");
static_assert(contains_type_v<baz, foo, bar, baz>, "Type should be found in haystack");
static_assert(!contains_type_v<int, foo, bar, baz>, "Missing type should not be found in haystack");
