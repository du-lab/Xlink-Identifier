/**
 * @file    generator.hpp
 * @brief   Macros and class to create generators
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_generator_hpp_
#define apollo_generator_hpp_

/**
 * @brief A macro to define the beginning of a generator's operator() function
 */
#define $gen_start if(_line < 0) { _line = 0;} \
switch(_line) { case 0:;

/**
 * @brief A macro to define the end of a generator's operator() function
 */
#define $gen_stop  } _line = 0; return false;

/**
 * @brief A macro to yield the generator's current position and create that corrosponding return value
 */
#define $yield(R)    \
do { \
    _line = __LINE__; \
    generate(R); return true; case __LINE__:; \
} while (0);

namespace apollo {

/**
 * @class   Generator generator.hpp "generator.hpp"
 * @brief   Standard generator interface for all generators in this project.

     The macros above, coupled with this class, are used to define functions that can be jumped into and out at arbitrary positions

    Consider NumGen, a simple number generator:

    class NumGen : public Generator<int> {

    NumGen() : _i(0), Generator<int>() {}

    bool operator()(value_type &rv) {
        $gen_start;
        for(_i = 0; _i < 10; _i++) {
            $yield(rv);
        }
        $gen_stop;
    }

    void generate(value_type &rv) {
        rv = _i;
    }

    private:
        value_type _i;
    };

    NumGen is nothing more than a simple for-loop that yields numbers [0,10).
    The importance of the generator is to separate out the generator's next state calculation (_i++)
    from the return value's generator (rv = _i) from the rest of the application logic

    The more complex of a state we're working with, the more powerful this idea becomes. 

    @Note Successive calls to operator() will place execution directly after
        the last called yield statement
        - Any variable modification between $gen_start and $yield will be skipped! -
        A generator's state must be held in its member variables and care must be exercised when using 
        local variables in operator().
 */

template <typename T>
class Generator {
public:

    /**
     * The type the generator creates
     */
    typedef T value_type;

    // default ctor
    Generator(): _line(-1) {}

    // copy ctor
    Generator(Generator const &rhs) : _line(rhs._line) {}

    // move ctor
    Generator(Generator &&rhs) : _line(rhs._line) {}

    // copy = ctor
    Generator& operator=(Generator const &rhs)
    {
        if (this != &rhs) {
            _line = rhs._line;
        }
        return *this;
    }

    // move = ctor
    Generator& operator=(Generator &&rhs)
    {
        if (this != &rhs) {
            _line = rhs._line;
        }
        return *this;
    }

    /**
    * Generator calculates its next state, creates the value for that state.
    *
    * @param[in,out] rv The return value's storage location
    *
    * @return True if generator at next state and a new return value is generated. 
    *   False if there are no more valid states and return value is untouched.
    */
    virtual bool operator()(value_type &rv) = 0;

    /**
     * Using the generator's current state, create the return value
     *
     *  @param[in,out]  rv The return value's storage location
     */
    virtual void generate(value_type &rv) const = 0; 

    // == operator
    virtual bool operator==(Generator const &rhs) const {
        return _line == rhs._line;
    }

    // deconstructor
    virtual ~Generator() {}

protected:
    int _line; /**< The source code line $gen_start will use for its switch */
};

} /* namespace apollo */

#endif // apollo_generator_hpp_
