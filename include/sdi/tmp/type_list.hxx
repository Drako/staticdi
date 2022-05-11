#pragma once

#include "generic.hxx"

#include <tuple>

namespace sdi {
  namespace tmp {
    /**
     * A compile time list of types.
     *
     * @tparam Types The types contained in the list.
     */
    template<typename... Types>
    struct type_list final {
      /**
       * The number of types in the list.
       */
      static std::size_t constexpr size = sizeof...(Types);
    };

    /**
     * Type trait checking whether TypeList is a type_list<...>.
     *
     * @tparam TypeList The type to be checked.
     */
    template<typename TypeList>
    struct is_type_list final : std::false_type {
    };

    /**
     * Comfort alias to check a type for being a type_list<...>.
     *
     * @tparam TypeList The type to be checked.
     */
    template<typename TypeList>
    static bool constexpr is_type_list_v = is_type_list<TypeList>::value;

    /**
     * Type trait checking whether TypeList is a type_list<...>.
     * This is the specialization matching type_list's.
     *
     * @tparam Types The types contained in the type_list.
     */
    template<typename... Types>
    struct is_type_list<type_list<Types...>> final : std::true_type {
    };

    /**
     * Concatenate two type_list's.
     *
     * This has no implementation as it is only used with decltype.
     *
     * @tparam Lhs The left hand side type_list.
     * @tparam Rhs The right hand side type_list.
     * @return The resulting type_list.
     */
    template<typename... Lhs, typename... Rhs>
    auto operator+(type_list<Lhs...>, type_list<Rhs...>) -> type_list<Lhs..., Rhs...>;

    /**
     * Get the nth type from a list of types.
     *
     * @tparam Index The index of the type to get.
     * @tparam Types The types.
     */
    template<std::size_t Index, typename... Types>
    struct nth_type final {
      /**
       * The nth type in Types.
       */
      using type = std::decay_t<decltype(std::get<Index>(std::declval<std::tuple<Types...>>()))>;
    };

    /**
     * Comfort alias for nth_type.
     *
     * @tparam Index The index of the type to get.
     * @tparam Types The types.
     */
    template<std::size_t Index, typename... Types>
    using nth_type_t = typename nth_type<Index, Types...>::type;

    /**
     * Remove duplicate types from the given type_list.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeList>
    struct make_unique;

    /**
     * Comfort alias for make_unique.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeList>
    using make_unique_t = typename make_unique<TypeList>::type;

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for empty lists.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<>
    struct make_unique<type_list<>> final {
      using type = type_list<>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for list with single element.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename Type>
    struct make_unique<type_list<Type>> final {
      using type = type_list<Type>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 2 elements which are the same.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename Type>
    struct make_unique<type_list<Type, Type>> final {
      using type = type_list<Type>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 2 elements which are different.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeA, typename TypeB>
    struct make_unique<type_list<TypeA, TypeB>> final {
      using type = type_list<TypeA, TypeB>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 3 elements which are the same.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename Type>
    struct make_unique<type_list<Type, Type, Type>> final {
      using type = type_list<Type>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 3 elements where 2 are the same.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeA, typename TypeB>
    struct make_unique<type_list<TypeA, TypeB, TypeB>> final {
      using type = type_list<TypeA, TypeB>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 3 elements where 2 are the same.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeA, typename TypeB>
    struct make_unique<type_list<TypeA, TypeA, TypeB>> final {
      using type = type_list<TypeA, TypeB>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 3 elements where 2 are the same.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeA, typename TypeB>
    struct make_unique<type_list<TypeA, TypeB, TypeA>> final {
      using type = type_list<TypeA, TypeB>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 3 elements where all are different.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename TypeA, typename TypeB, typename TypeC>
    struct make_unique<type_list<TypeA, TypeB, TypeC>> final {
      using type = type_list<TypeA, TypeB, TypeC>;
    };

    /**
     * Remove duplicate types from the given type_list.
     *
     * Specialization for lists with 4 or more elements.
     *
     * @tparam TypeList The type_list to make unique.
     */
    template<typename HeadA, typename HeadB, typename HeadC, typename HeadD, typename... Tail>
    struct make_unique<type_list<HeadA, HeadB, HeadC, HeadD, Tail...>> final {
    private:
      template<typename Needle, typename HayStack>
      struct contains_type;

      template<typename Needle, typename... HayStack>
      struct contains_type<Needle, type_list<HayStack...>> final {
        static bool constexpr value = generic::contains_type_v<Needle, HayStack...>;
      };

      template<typename Needle, typename HayStack>
      static bool constexpr contains_type_v = contains_type<Needle, HayStack>::value;

      using tail = make_unique_t<type_list<Tail...>>;
      using maybe_with_d = decltype(
      std::conditional_t<contains_type_v<HeadD, tail>, type_list<>, type_list<HeadD>>{} + tail{});
      using maybe_with_c = decltype(
      std::conditional_t<contains_type_v<HeadC, maybe_with_d>, type_list<>, type_list<HeadC>>{} + maybe_with_d{});
      using maybe_with_b = decltype(
      std::conditional_t<contains_type_v<HeadB, maybe_with_c>, type_list<>, type_list<HeadB>>{} + maybe_with_c{});
      using maybe_with_a = decltype(
      std::conditional_t<contains_type_v<HeadA, maybe_with_b>, type_list<>, type_list<HeadA>>{} + maybe_with_b{});

    public:
      using type = maybe_with_a;
    };
  }
}
