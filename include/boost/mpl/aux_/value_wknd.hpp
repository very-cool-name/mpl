//-----------------------------------------------------------------------------
// boost mpl/aux_/value_wknd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG))

namespace boost { namespace mpl { namespace aux {

template< typename C >
struct value_wknd
    : C
{
};

}}} // namespace boost::mpl::aux

#   define BOOST_MPL_AUX_VALUE_WKND(C) ::boost::mpl::aux::value_wknd< C >

#else

#   define BOOST_MPL_AUX_VALUE_WKND(C) C

#endif // __BORLANDC__

#endif // BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
