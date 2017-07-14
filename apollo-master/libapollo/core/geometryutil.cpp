#include "geometryutil.hpp"


namespace apollo {

Box1D boxFrom(types::mz_store_t const a, types::mz_store_t const b) {
    return Box1D(Point1D(a), Point1D(b));
}

}
