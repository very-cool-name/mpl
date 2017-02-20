#ifndef BOOST_MPL_VECTOR_VARIADIC_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VARIADIC_HPP_INCLUDED

// Copyright Mikhail Maximov 2017
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/vector/aux_/iterator.hpp>

#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/front.hpp>
#include <boost/mpl/vector/aux_/push_front.hpp>
#include <boost/mpl/vector/aux_/pop_front.hpp>
#include <boost/mpl/vector/aux_/push_back.hpp>
#include <boost/mpl/vector/aux_/pop_back.hpp>
#include <boost/mpl/vector/aux_/back.hpp>
#include <boost/mpl/vector/aux_/clear.hpp>
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/size.hpp>
#include <boost/mpl/vector/aux_/empty.hpp>
#include <boost/mpl/vector/aux_/item.hpp>
#include <boost/mpl/vector/aux_/iterator.hpp>
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/begin_end.hpp>

namespace boost {
namespace mpl {
namespace detail {
    template<typename T, typename... Types>
    struct types_unroll {
        typedef T type;
    };
    
    template<long item, typename T, typename... Types>
    class v_item : v_item<item + 1, Types...> {
        typedef long_<item> index_;
       public:
        static aux::type_wrapper<T> item_(index_);
        
        using v_item<item + 1, Types...>::item_;
    };  
    
    template<long item, typename T>
    class v_item<item, T> {
        typedef long_<item> index_;
       public:
        static aux::type_wrapper<T> item_(index_);
    };
}


template<typename... Types>
struct vector_variadic_tag{};


template<typename... Types>
struct vector: detail::v_item<0, Types...> {
    typedef vector<Types...> type;
    typedef v_iter<type, 0> begin;
    typedef v_iter<type, sizeof ... (Types)> end;
    typedef vector_variadic_tag<Types...> tag;
    typedef long_<0> lower_bound_;
    typedef lower_bound_ upper_bound_;
    typedef long_<sizeof ... (Types)> size;
    
    using detail::v_item<0, Types...>::item_;
};

template<>
struct vector<> {
    typedef vector<> type;
    typedef v_iter<type, 0> begin;
    typedef v_iter<type, 0> end;
    typedef vector_variadic_tag<> tag;
    typedef long_<0> lower_bound_;
    typedef lower_bound_ upper_bound_;
    typedef long_<0> size;
};


template<typename... Types>
struct push_back_impl<vector_variadic_tag<Types...> >
{
    template< typename Sequence, typename T > struct apply
    {
        typedef vector<Types..., T> type;
    };
};


template<typename... Types>
struct push_front_impl<vector_variadic_tag<Types...> >
{
    template< typename Sequence, typename T > struct apply
    {
        typedef vector<T, Types...> type;
    };
};


template<typename... Types>
struct clear_impl<vector_variadic_tag<Types...> >
{
    template< typename Sequence > struct apply
    {
      typedef vector<> type;
    };
};

} // namespace mpl
} // namespace boost

#endif //BOOST_MPL_VECTOR_VARIADIC_HPP_INCLUDED