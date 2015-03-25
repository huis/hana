/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#define FUSION_MAX_VECTOR_SIZE 20
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/transform.hpp>

#include "benchmark.hpp"
#include <cstdlib>


int main () {
    boost::hana::benchmark::measure([] {
        long long result = 0;
        for (int iteration = 0; iteration < 1 << 10; ++iteration) {
            auto values = boost::fusion::make_vector(
                <%= input_size.times.map { 'std::rand()' }.join(', ') %>
            );

            boost::fusion::as_vector(
                boost::fusion::transform(values, [&](auto t) {
                    return result += t;
                })
            );
        }
    });
}