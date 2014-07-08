/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TEST_MONAD_MINIMAL_HPP
#define BOOST_HANA_TEST_MONAD_MINIMAL_HPP

#include <boost/hana/applicative.hpp>
#include <boost/hana/comparable.hpp>
#include <boost/hana/functor.hpp>


struct MinimalMonad;

template <typename T>
struct monad {
    T value;
    using hana_datatype = MinimalMonad;
};

namespace boost { namespace hana {
    // Required to check Monad laws.
    template <>
    struct Comparable::instance<MinimalMonad, MinimalMonad>
        : Comparable::equal_mcd
    {
        template <typename T>
        static constexpr auto equal_impl(monad<T> a, monad<T> b)
        { return equal(a.value, b.value); }
    };

    template <>
    struct Functor::instance<MinimalMonad> : Functor::fmap_mcd {
        template <typename F, typename M>
        static constexpr auto fmap_impl(F f, M m)
        { return monad<decltype(f(m.value))>{f(m.value)}; }
    };

    template <>
    struct Applicative::instance<MinimalMonad> : Applicative::mcd {
        template <typename T>
        static constexpr auto lift_impl(T t)
        { return monad<T>{t}; }

        template <typename F, typename X>
        static constexpr auto ap_impl(F f, X x)
        { return fmap(f.value, x); }
    };
}}

#endif // !BOOST_HANA_TEST_MONAD_MINIMAL_HPP