/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017-2020 Michele Caini
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copy of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copy or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _TAG_HPP
#define _TAG_HPP


#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>

#include "hashed_string.hpp"

namespace sp
{


/**
 * @brief Wraps a static constant.
 * @tparam Value A static constant.
 */
template<auto Value>
using integral_constant = std::integral_constant<decltype(Value), Value>;


/**
 * @brief Alias template to ease the creation of named values.
 * @tparam Value A constant value at least convertible to `std::uint32_t`.
 */
template<std::uint32_t Value>
using tag = integral_constant<Value>;


}

#endif // _TYPE_TRAITS_HPP
