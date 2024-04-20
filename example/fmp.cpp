//
// Copyright (c) 2024-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/fmp
//

// g++ -I include -m64 -std=c++26 -s -Wall -O3 -o /tmp/fmp example/fmp.cpp

#include <cassert>
#include <iostream>
#include <fmp.hpp>

struct W
{
    int rank;
    std::string key;
    std::string val;
};

struct X
{
    float f;
    std::string s;
};

struct Y
{
    int i;
    double d;
    char c;
    X x;
};

int main(int argc, char* argv[])
{
    static_assert(fmp::member_name_v<1, W> == "key");
    static_assert(fmp::member_name<int, W>() == "rank");

    static_assert(fmp::member_index<int, W>() == 0);
    static_assert(fmp::member_index<W>("val") == 2);

    static_assert(std::is_same_v<fmp::member_t<0, W>, int>);
    static_assert(std::is_same_v<fmp::member_t<fmp::member_index<W>("val"), W>, std::string>);

    X x { 15.32f, "template" };
    Y y { 2048, 12.14, '+', { 27.85f, "fmp" } };

    x.*fmp::get<0, X>() = 30.18f;
    fmp::get<1>(fmp::get<X>(y)) = "Stateful";

    auto ns = fmp::member_names_v<W>;
    assert(fmp::get<0>(ns) == "rank");

    assert(fmp::member_name_v<1, W> == "key");
    assert(fmp::member_name_v<2, W> == "val");

    assert(x.f == 30.18f);
    assert(y.x.s == "Stateful");

    assert(fmp::index(&X::s) == 1);
    assert(fmp::index(&Y::x) == 3);

    static_assert(fmp::tuple_size_v<X> == 2);
    static_assert(fmp::tuple_size_v<Y> == 4);

    static_assert(std::is_same_v<fmp::tuple_element_t<0, X>, float>);
    static_assert(std::is_same_v<fmp::tuple_element_t<1, Y>, double>);

    auto f = fmp::tie_fuple(x);
    auto t = fmp::tie_tuple(y);

    fmp::get<std::string&>(f) = "Dark Army";
    std::get<X&>(t) = { 72.68f, "Programs" };

    assert(x.s == "Dark Army");

    assert(y.x.f == 72.68f);
    assert(y.x.s == "Programs");

    x.*fmp::get<0, X>() = 48.65f;
    x.*fmp::get<1, X>() = "transformer";

    assert(fmp::get<1>(f) == "transformer");
    assert(fmp::get<float>(f) == 48.65f);

    y.*fmp::get<3, Y>() = { 25.65f, "Template" };

    assert(std::get<3>(t).f == 25.65f);
    assert(std::get<X&>(t).s == "Template");

    W w1;
    W w2;

    std::stringstream ss1;
    std::stringstream ss2;

    std::string str1 = "100, \"Modern C++ Template\", \"MetaProgramming Library\"";
    std::string str2 = "101, \"Modern C++ Stateful\", \"MetaProgramming Framework\"";

    ss1 << str1;
    ss1 >> fmp::io(w1);

    ss2 << str2;
    ss2 >> fmp::io(w2);

    std::cout << fmp::io(w1) << std::endl;
    std::cout << fmp::io(w2) << std::endl;

    /* outputs
    100, "Modern C++ Template", "MetaProgramming Library"
    101, "Modern C++ Stateful", "MetaProgramming Framework"
    */

    assert(w1.rank == 100);
    assert(w2.rank == 101);

    assert(w1.key == "Modern C++ Template");
    assert(w2.key == "Modern C++ Stateful");

    assert(w1.val == "MetaProgramming Library");
    assert(w2.val == "MetaProgramming Framework");

    std::cout << "fmp::lt " << fmp::lt(w1, w2) << std::endl;
    std::cout << "fmp::le " << fmp::le(w1, w2) << std::endl;

    std::cout << "fmp::ne " << fmp::ne(w1, w2) << std::endl;
    std::cout << "fmp::eq " << fmp::eq(w1, w2) << std::endl;

    std::cout << "fmp::ge " << fmp::ge(w1, w2) << std::endl;
    std::cout << "fmp::gt " << fmp::gt(w1, w2) << std::endl;

    auto f1 = fmp::tie_fuple(w1);
    auto f2 = fmp::tie_fuple(w2);

    auto t1 = fmp::tie_tuple(w1);
    auto t2 = fmp::tie_tuple(w2);

    std::cout << "f1 <  f2 " << (f1 <  f2) << std::endl;
    std::cout << "f1 <= f2 " << (f1 <= f2) << std::endl;

    std::cout << "f1 != f2 " << (f1 != f2) << std::endl;
    std::cout << "f1 == f2 " << (f1 == f2) << std::endl;

    std::cout << "f1 >= f2 " << (f1 >= f2) << std::endl;
    std::cout << "f1 >  f2 " << (f1 >  f2) << std::endl;

    std::cout << "t1 <  t2 " << (t1 <  t2) << std::endl;
    std::cout << "t1 <= t2 " << (t1 <= t2) << std::endl;

    std::cout << "t1 != t2 " << (t1 != t2) << std::endl;
    std::cout << "t1 == t2 " << (t1 == t2) << std::endl;

    std::cout << "t1 >= t2 " << (t1 >= t2) << std::endl;
    std::cout << "t1 >  t2 " << (t1 >  t2) << std::endl;

    int fr = 0;
    int tr = 0;

    std::string fk;
    std::string tk;

    std::string fv;
    std::string tv;

    fmp::ref_fuple(fr, fk, fv) = w1;
    fmp::ref_tuple(tr, tk, tv) = w2;

    assert(fr == 100);
    assert(tr == 101);

    assert(fk == "Modern C++ Template");
    assert(tk == "Modern C++ Stateful");

    assert(fv == "MetaProgramming Library");
    assert(tv == "MetaProgramming Framework");

    auto print_backward = []<typename... Args>(Args&&... args)
    {
        const char* sep = " ";

        ((std::cout << args << sep, sep) = ... = " ");
        std::cout << std::endl;
    };

    fmp::for_each(print_backward, w1);
    std::cout << std::endl;

    fmp::for_each(print_backward, w2);
    std::cout << std::endl;

    auto mptrs_backward = []<typename T>(T&& t)
    {
        return [&]<typename... Args>(Args&&... args)
        {
            const char* sep = " ";

            ((std::cout << t.*args << sep, sep) = ... = " ");
            std::cout << std::endl;
        };
    };

    fmp::for_mptr(mptrs_backward(w1), w1);
    std::cout << std::endl;

    fmp::for_mptr(mptrs_backward(w2), w2);
    std::cout << std::endl;

    fmp::apply(print_backward, w1);
    fmp::apply(print_backward, w2);

    std::cout << std::endl;
    fmp::zip(print_backward, w1, w2, x, y);

    // marshal and unmarshal a structure

    std::string xs = fmp::marshal(x);
    std::string ys = fmp::marshal(y);

    X x0 = fmp::unmarshal<X>(xs);
    Y y0 = fmp::unmarshal<Y>(ys);

    assert(fmp::eq(x, x0));

    assert(y.i == y0.i);
    assert(y.d == y0.d);

    assert(y.c == y0.c);
    assert(fmp::eq(y.x, y0.x));

    // marshal and unmarshal with allocated structure

    X x1;
    std::string s0;

    fmp::marshal(s0, x);
    fmp::unmarshal(s0, x1);

    assert(fmp::eq(x1, x));

    Y y1;
    std::string s1 = "prefix";

    size_t prelen = s1.length();
    size_t length = s1.length();

    fmp::marshal(s1, y);
    fmp::unmarshal(length, s1, y1);

    assert(y.i == y1.i);
    assert(y.d == y1.d);

    assert(y.c == y1.c);
    assert(fmp::eq(y.x, y1.x));

    assert(length == s1.length());
    assert(fmp::marshal(y).length() == length - prelen);

    auto y2 = fmp::unmarshal<Y>(s1.substr(prelen));

    assert(y.i == y2.i);
    assert(y.d == y2.d);

    assert(y.c == y2.c);
    assert(fmp::eq(y.x, y2.x));

    // marshal and unmarshal a fmp::fuple or std::tuple

    std::string ws1 = fmp::marshal(f1);
    std::string ws2 = fmp::marshal(t2);

    auto w3 = fmp::unmarshal<W>(ws1);
    auto w4 = fmp::unmarshal<W>(ws2);

    assert(fmp::eq(w1, w3));
    assert(fmp::eq(w2, w4));

    auto f0 = fmp::make_fuple(1, 2.0f, std::string("marshal"), 'X', std::make_tuple(100.3, std::string("Unmarshal")));
    auto t0 = std::make_tuple(2, 3.0f, std::string("Marshal"), 'Y', fmp::make_fuple(200.3, std::string("unmarshal")));

    std::string fs0 = fmp::marshal(f0);
    std::string ts0 = fmp::marshal(t0);

    auto f3 = fmp::unmarshal<decltype(f0)>(fs0);
    auto t3 = fmp::unmarshal<decltype(t0)>(ts0);

    assert(f3 == f0);
    assert(t3 == t0);

    assert(std::get<std::string>(fmp::get<4>(f3)) == std::get<1>(fmp::get<4>(f0)));
    assert(fmp::get<1>(std::get<4>(t3)) == fmp::get<std::string>(std::get<4>(t0)));

    return 0;
}
