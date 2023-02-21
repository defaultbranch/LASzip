#include "../src/laszip.hpp"

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(laszip) {
  class_<LASzip>("LASzip")
    .constructor<>()
    .function("check_coder", &LASzip::check_coder)
    ;
}
