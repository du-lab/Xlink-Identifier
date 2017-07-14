/**
 * @file    generatoriterator.hpp
 * @brief   A class to create iterators out of generators
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_generatoriterator_hpp_
#define apollo_generatoriterator_hpp_

#include <utility>
#include <iterator>
#include <boost/iterator/iterator_facade.hpp>

namespace apollo {

template <typename G>
class GeneratorIterator : public boost::iterator_facade <
    GeneratorIterator<G>,
    const typename G::value_type,
    boost::forward_traversal_tag> {
public:
    typedef G generator_t;

    GeneratorIterator() : _finished(true) {}
    
    explicit GeneratorIterator(generator_t const &gen) :
        _gen(gen),
        _finished(false) {
            this->operator++();
    }

    explicit GeneratorIterator(generator_t &&gen) :
        _gen(std::forward<generator_t>(gen)),
        _finished(false) {
            this->operator++();
    }

    GeneratorIterator(GeneratorIterator const &rhs) :
        _gen(rhs._gen),
        _finished(rhs._finished) {
            if (!_finished) {
                _gen.generate(_rv);
            }
        }

    GeneratorIterator(GeneratorIterator &&rhs) :
        _gen(std::move(rhs._gen)),
        _rv(std::move(rhs._rv)),
        _finished(rhs._finished) {}

    GeneratorIterator& operator=(GeneratorIterator const &rhs) {
        if (this != &rhs) {
            _gen = rhs._gen;
            _finished = rhs._finished;
            if (!_finished) {
                _gen.generate(_rv);
            }
        }
        return *this;
    }

    GeneratorIterator& operator=(GeneratorIterator &&rhs) {
        if (this != &rhs) {
            _gen = std::move(rhs._gen);
            _rv = std::move(rhs._rv);
            _finished = rhs._finished;
        }
        return *this;
    }

    generator_t const& gen() const {
        return _gen;
    }

    ~GeneratorIterator() {}

private:
    friend class boost::iterator_core_access;
    generator_t _gen;
    typename generator_t::value_type _rv;
    bool _finished;

    bool equal(GeneratorIterator const &rhs) const {
        if (_finished || rhs._finished) {
            if (_finished && rhs._finished) {
                return true;
            } else {
                return false;
            }
        }  else if ((_rv == rhs._rv) &&
            (_gen == rhs._gen)) {
            return true;
        }
        return false;
    }

    void increment() { advance(); }

    void advance(std::ptrdiff_t dist = 1) {
        while (!_finished && (dist > 0)) {
            if( _gen(_rv) == false) {
                _finished = true;
            }
            dist -= 1;
        }
    }

    std::ptrdiff_t distance_to(GeneratorIterator const &rhs) const {
        using std::distance;
        if (_finished && rhs._finished) {
            return 0;
        }
        if (!_finished) {
            return distance(*this, rhs);
        } else {
            return distance(rhs, *this) * -1;
        }
    }

    const typename generator_t::value_type& dereference() const { return _rv; }

};

template<class G, typename... Args>
GeneratorIterator<G> make_geniter(Args && ...args) {
    return GeneratorIterator<G>(G(std::forward<Args>(args)...));
}

} /* namespace apollo */

#endif /* apollo_generatoriterator_hpp_ */
