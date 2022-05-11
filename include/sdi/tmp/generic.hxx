#pragma once

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <type_traits>

namespace sdi {
  namespace tmp {
    namespace generic {
      /**
       * Helper to ensure Value is evaluated at compile time.
       *
       * @tparam T The type of the value.
       * @tparam Value The value.
       */
      template<typename T, T Value>
      static T constexpr force_constexpr = Value;

      /**
       * Placeholder value for search algorithms to return if the searched value is not found.
       */
      static std::size_t constexpr NOT_FOUND = std::numeric_limits<std::size_t>::max();

      /**
       * Search for the Needle in the HayStack. Return the index or NOT_FOUND in value.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      struct find_type;

      template<typename Needle>
      struct find_type<Needle> final {
        static std::size_t constexpr value = NOT_FOUND;
      };

      template<typename Needle, typename Head, typename... Tail>
      struct find_type<Needle, Head, Tail...> final {
      private:
        static constexpr std::size_t find_impl() noexcept
        {
          std::size_t idx{0U};
          for (bool const found: {std::is_same<Needle, Head>::value, std::is_same<Needle, Tail>::value...}) {
            if (found) {
              return idx;
            }
            ++idx;
          }
          return NOT_FOUND;
        }

      public:
        static std::size_t constexpr value = force_constexpr<std::size_t, find_impl()>;
      };

      /**
       * Search for the Needle in the HayStack. Return the index or NOT_FOUND.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      static std::size_t constexpr find_type_v = find_type<Needle, HayStack...>::value;

      /**
       * Search for the Needle in the HayStack. Returns whether the HayStack contains the Needle.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      static bool constexpr contains_type_v = find_type_v<Needle, HayStack...> != NOT_FOUND;

      /**
       * Search for the a type derived from Needle in the HayStack. Return the index or NOT_FOUND in value.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      struct find_derived_type;

      template<typename Needle>
      struct find_derived_type<Needle> final {
        static std::size_t constexpr value = NOT_FOUND;
      };

      template<typename Needle, typename Head, typename... Tail>
      struct find_derived_type<Needle, Head, Tail...> final {
      private:
        static constexpr std::size_t find_impl() noexcept
        {
          std::size_t idx{0U};
          for (bool const found: {std::is_convertible<Head&, Needle&>::value, std::is_convertible<Tail&, Needle&>::value...}) {
            if (found) {
              return idx;
            }
            ++idx;
          }
          return NOT_FOUND;
        }

      public:
        static std::size_t constexpr value = force_constexpr<std::size_t, find_impl()>;
      };

      /**
       * Search for the a type derived from Needle in the HayStack. Return the index or NOT_FOUND.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      static std::size_t constexpr find_derived_type_v = find_derived_type<Needle, HayStack...>::value;

      /**
       * Search for the a type derived from Needle in the HayStack. Returns whether the HayStack contains the Needle.
       *
       * @tparam Needle The type to search for.
       * @tparam HayStack A pack of types that might contain the Needle.
       */
      template<typename Needle, typename... HayStack>
      static bool constexpr contains_derived_type_v = find_derived_type_v<Needle, HayStack...> != NOT_FOUND;
    }
  }
}
