#pragma once

#include "tmp/type_list.hxx"

namespace sdi {
  /**
   * A type_list declaring the dependencies of a component.
   */
  template<typename... Types>
  using dependencies = tmp::type_list<Types...>;
}
