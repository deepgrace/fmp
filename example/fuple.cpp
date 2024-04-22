//
// Copyright (c) 2024-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/fmp
//

// g++ -I include -m64 -std=c++26 -s -Wall -O3 -o /tmp/fuple example/fuple.cpp

#include <cassert>
#include <iostream>
#include <fuple.hpp>

// fuple (flat tuple) implemented with multiple inheritance is a drop-in replacement for std::tuple

int main(int argc, char* argv[])
{
    fmp::fuple f0;
    fmp::fuple f1(std::string("C++23"));

    int i = 2024;
    double j = 11.05;

    fmp::fuple<short, char> f2;
    fmp::fuple<int&, fmp::fuple<double&>, char> f3(i, fmp::tie(j), 'X');

    static_assert(fmp::fuple_index<char>(f2) == 1);
    static_assert(fmp::fuple_index<short>(f2) == 0);

    static_assert(fmp::fuple_index<int>(f3) == 3);
    static_assert(fmp::fuple_index<int&, 0>(f3) == 0);

    static_assert(fmp::fuple_index<int, 1>(f3) == 0);
    static_assert(fmp::fuple_index<int&, 1>(f3) == 0);

    int p = 23;
    std::string s = "tmp";

    fmp::tie(p, s, fmp::ignore) = fmp::make_fuple(45, std::string("C++ TMP"), 9.8);

    assert(p == 45);
    assert(s == "C++ TMP");

    auto f4 = fmp::make_fuple(j, std::string("template"));
    auto f5 = fmp::forward_as_fuple(p, s, std::string("fmp"));

    auto f6 = fmp::fuple_cat(f0, f1, f2, f3, f4, f5);

    fmp::get<int>(f5) = 75;
    fmp::get<1>(f5) = std::string("c++ tmp");

    assert(p == 75);
    assert(s == "c++ tmp");

    using type = decltype(f6);

    static_assert(fmp::is_fuple_v<type>);
    static_assert(fmp::fuple_size_v<type> == 11);

    static_assert(std::is_same_v<fmp::fuple_element_t<0, type>, std::string>);
    static_assert(std::is_same_v<fmp::fuple_element_t<4, type>, fmp::fuple<double&>>);

    // extract the nth member by base class type

    assert((f3.fmp::element<0, int&>::value == 2024));
    assert((f3.fmp::element<1, fmp::fuple<double&>>::value.fmp::element<0, double&>::value == 11.05));

    fmp::fuple f(1, 3, 2, 'X', std::string("template"), 11.2d);
    fmp::fuple g(4, 7, 8, 'Y', std::string("C++23"), 22.4d);

    auto w = fmp::make_fuple(f, g);
    using element_t = fmp::element<4, std::string>;

    assert(f.element_t::value == "template");

    assert((w.fmp::element<0, decltype(f)>::value.element_t::value == "template"));
    assert((w.fmp::element<1, decltype(f)>::value.element_t::value == "C++23"));

    using triple = fmp::fuple<int, double, std::string>;
    triple f7(20, 11.06, "fmp");

    fmp::fuple f8(f7);
    fmp::fuple f9 = f8;

    triple f10(std::move(f9));
    triple f11(30, 22.12, "fmp");

    triple f12(40, 9.23, "tmp");
    triple f13(50, 12.77, "cpp");

    f10 = f11;

    const fmp::fuple<> cf1;
    const fmp::fuple<> cf2;

    f11.swap(f12);
    cf1.swap(cf2);

    assert(fmp::get<double>(f8) == 11.06);
    assert(fmp::get<std::string>(f9) == "");

    assert(fmp::get<int>(f10) == 30);
    assert(fmp::get<1>(f11) == 9.23);

    assert(fmp::get<2>(f12) == "fmp");

    auto print_backward = []<typename... Args>(Args&&... args)
    {
        const char* sep = " ";
        ((std::cout << args << sep, sep) = ... = " ");

        std::cout << std::endl;
    };

    fmp::for_each(print_backward, f12);
    std::cout << std::endl;

    fmp::for_each(print_backward, f11);
    std::cout << std::endl;

    fmp::for_each(print_backward, f13);
    std::cout << std::endl;

    fmp::apply(print_backward, f12);
    fmp::apply(print_backward, f11);

    fmp::apply(print_backward, f13);
    std::cout << std::endl;

    // apply a function to every nth field of std::fuples, takes the longest common fields number

    fmp::zip(print_backward, f12, f11, f13);
    std::cout << std::endl;

    std::cout << "f12 <  f13 " << (f12 <  f13) << std::endl;
    std::cout << "f12 <= f13 " << (f12 <= f13) << std::endl;

    std::cout << "f12 != f13 " << (f12 != f13) << std::endl;
    std::cout << "f12 == f13 " << (f12 == f13) << std::endl;

    std::cout << "f12 >= f13 " << (f12 >= f13) << std::endl;
    std::cout << "f12 >  f13 " << (f12 >  f13) << std::endl;

    // convert a fuple to a tuple or vice versa

    auto mf = fmp::make_fuple(9, 's');
    auto mt = std::make_tuple(9, 's');

    auto ft = fmp::fuple_to_tuple(mf);
    auto tf = fmp::tuple_to_fuple(mt);

    assert(mf == tf);
    assert(mt == ft);

    // create a fmp::fuple or std::tuple of lvalue references from another fmp::fuple or std::tuple
    // i.e
    // fmp::fuple<Args...> -> fmp::fuple<Args&...>
    // std::tuple<Args...> -> std::tuple<Args&...>

    auto x = fmp::tied_fuple(tf);
    auto y = fmp::tied_tuple(ft);

    fmp::get<0>(x) = 100;
    std::get<1>(y) = 'S';

    assert(fmp::get<0>(tf) == 100);
    assert(std::get<1>(ft) == 'S');

    return 0;
}
