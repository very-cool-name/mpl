
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

#include <boost/mpl/logical.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/mpl/aux_/test_no_nm.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_float.hpp>

struct my
{
    char a[100];
};

MPL_TEST_CASE()
{
    // !(x == char) && !(x == double) || sizeof(x) > 8
    typedef boost::mpl::lambda<
        boost::mpl::or_<
              boost::mpl::and_<
                    boost::mpl::not_< boost::is_same<boost::mpl::_1, char> >
                  , boost::mpl::not_< boost::is_float<boost::mpl::_1> >
                  >
            , boost::mpl::greater< boost::mpl::sizeof_<boost::mpl::_1>, boost::mpl::size_t<8> >
            >
        >::type f;

    MPL_ASSERT_NOT(( boost::mpl::apply_wrap1<f,char> ));
    MPL_ASSERT_NOT(( boost::mpl::apply_wrap1<f,double> ));
    MPL_ASSERT(( boost::mpl::apply_wrap1<f,long> ));
    MPL_ASSERT(( boost::mpl::apply_wrap1<f,my> ));
}

MPL_TEST_CASE()
{
    // x == y || x == my || sizeof(x) == sizeof(y)
    typedef boost::mpl::lambda<
        boost::mpl::or_< 
              boost::is_same<boost::mpl::_1, boost::mpl::_2>
            , boost::is_same<boost::mpl::_2, my>
            , boost::mpl::equal_to< boost::mpl::sizeof_<boost::mpl::_1>, boost::mpl::sizeof_<boost::mpl::_2> >
            >
        >::type f;

    MPL_ASSERT_NOT(( boost::mpl::apply_wrap2<f,double,char> ));
    MPL_ASSERT_NOT(( boost::mpl::apply_wrap2<f,my,int> ));
    MPL_ASSERT_NOT(( boost::mpl::apply_wrap2<f,my,char[99]> ));
    MPL_ASSERT(( boost::mpl::apply_wrap2<f,int,int> ));
    MPL_ASSERT(( boost::mpl::apply_wrap2<f,my,my> ));
    MPL_ASSERT(( boost::mpl::apply_wrap2<f,signed long, unsigned long> ));
}

MPL_TEST_CASE()
{
    // bind <-> lambda interaction
    typedef boost::mpl::lambda< boost::mpl::less<boost::mpl::_1,boost::mpl::_2> >::type pred;
    typedef boost::mpl::bind2< pred, boost::mpl::_1, boost::mpl::int_<4> > f;
    
    MPL_ASSERT(( boost::mpl::apply_wrap1< f,boost::mpl::int_<3> > ));
}
