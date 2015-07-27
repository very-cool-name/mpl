
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/static_assert.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/aux_/test_no_nm.hpp>

#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_same.hpp>

MPL_TEST_CASE()
{
    typedef boost::mpl::list<int,float,long,float,char[50],long double,char> types;
    typedef boost::mpl::list<float,float,long double> floats;

    MPL_ASSERT(( boost::mpl::equal< boost::mpl::filter_view< types,boost::is_float<boost::mpl::_> >::type,floats > ));

    typedef boost::mpl::max_element<
          boost::mpl::transform_view<
              boost::mpl::filter_view< types,boost::is_float<boost::mpl::_> >
            , boost::mpl::sizeof_<boost::mpl::_>
            >
        >::type iter;

    MPL_ASSERT((boost::is_same<boost::mpl::deref<iter::base>::type, long double>));
}
