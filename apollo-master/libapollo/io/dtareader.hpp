/**
 * @file    dtareader.cpp
 * @brief   Dta file parsing using boost spirit
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/31
 * @copyright 2012
 */

#ifndef apollo_dtareader_hpp_
#define apollo_dtareader_hpp_

#include <utility>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "units.hpp"
#include "types.hpp"

namespace apollo {
namespace detail {
    
    typedef std::pair<types::mz_t, types::intensity_t> dta_read;
    
    struct dta_header {
        types::mz_t mh;
        types::charge_t z;
    };

    struct dta_file {
        dta_header header;
        std::vector<dta_read> reads;
    };
} /* namespace detail */
} /* namespace apollo */

BOOST_FUSION_ADAPT_STRUCT(
    apollo::detail::dta_header,
    (apollo::types::mz_t, mh)
    (apollo::types::charge_t, z)
)

BOOST_FUSION_ADAPT_STRUCT(
    apollo::detail::dta_read,
    (apollo::types::mz_t, first)
    (apollo::types::intensity_t, second)
)

BOOST_FUSION_ADAPT_STRUCT(
    apollo::detail::dta_file,
    (apollo::detail::dta_header, header)
    (std::vector<apollo::detail::dta_read>, reads)
)

namespace apollo {

struct compose_unit {

    template<typename U, typename T>
    struct result { typedef typename boost::units::multiply_typeof_helper<U, T>::type type; };

    template<typename U, typename T>
    typename result<U,T>::type operator()(U unit, T t) const {
        return t * unit;
    }
};

boost::phoenix::function<compose_unit> const compose = compose_unit();

template <typename Iterator>
struct dta_reader : boost::spirit::qi::grammar<
    Iterator, 
    apollo::detail::dta_file(), 
    boost::spirit::ascii::space_type> {

    dta_reader() : dta_reader::base_type(dta) {
        namespace qi = boost::spirit::qi;
        namespace phoenix = boost::phoenix;
        using qi::float_;
        using qi::short_;
        using qi::labels::_val;
        using qi::labels::_1;
        using phoenix::at_c;
        using phoenix::push_back;

        using units::charge;
        using units::mass_charge;
        using units::intensity;

        header = 
            float_ [at_c<0>(_val) = compose(_1, mass_charge)]
            >> short_ [at_c<1>(_val) = compose(_1, charge)]
            ;

        read =
            float_ [at_c<0>(_val) = compose(_1, mass_charge)]
            >> float_ [at_c<1>(_val) = compose(_1, intensity)]
            ;

        dta = 
            header [at_c<0>(_val) = _1]
            >> *read   [push_back(at_c<1>(_val), _1)]

        ;

    }
    boost::spirit::qi::rule<Iterator, apollo::detail::dta_file(), boost::spirit::ascii::space_type> dta;
    boost::spirit::qi::rule<Iterator, apollo::detail::dta_header(), boost::spirit::ascii::space_type> header;
    boost::spirit::qi::rule<Iterator, apollo::detail::dta_read(), boost::spirit::ascii::space_type> read;
};

} /* namespace apollo */


#endif /* apollo_dtareader_hpp_ */
