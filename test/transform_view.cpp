
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform_view.hpp>

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/aux_/test_no_nm.hpp>

MPL_TEST_CASE()
{
    typedef boost::mpl::list<int,long,char,char[50],double> types;
    typedef boost::mpl::list<
        boost::mpl::sizeof_<int>::type,
        boost::mpl::sizeof_<long>::type,
        boost::mpl::sizeof_<char>::type,
        boost::mpl::sizeof_<char[50]>::type,
        boost::mpl::sizeof_<double>::type
    > sizes;

    MPL_ASSERT(( boost::mpl::equal< boost::mpl::transform_view< types, boost::mpl::sizeof_<boost::mpl::_> >::type,sizes > ));

    typedef boost::mpl::max_element<
          boost::mpl::transform_view< types, boost::mpl::sizeof_<boost::mpl::_> >
        >::type iter;

    MPL_ASSERT_RELATION( boost::mpl::deref<iter>::type::value, ==, 50 );
}
