/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/core/operators.hpp>


namespace boost { namespace hana { namespace operators {
    template <typename T, typename U>
    void operator+(T&&, U&&) { }
}}}

template <typename = boost::hana::operators::adl>
struct template_param { };

struct inheritance : boost::hana::operators::adl { };

struct nothing { };


int main() {
    (void)(template_param<>{} + nothing{});
    (void)(nothing{} + template_param<>{});

    (void)(inheritance{} + nothing{});
    (void)(nothing{} + inheritance{});
}
