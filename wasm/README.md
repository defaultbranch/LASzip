# LASzip WASM target

This folder contains definitions to compile the LASzip source code
to Web Assembly and to use it in a JavaScript or TypeScript project.


## Emscripten/emsdk

[Emscripten](https://emscripten.org/) provides an SDK for compiling C/C++ and others to webassembly.

The emsdk is available as container image on [Docker Hub](https://hub.docker.com/r/emscripten/emsdk/tags).

### Howto run with WSL and Podman

Example for starting with WSL + podman on a Windows bash:
```
cd LASzip
wsl podman run --rm -it --mount=type=bind,source=./,destination=/LASzip docker.io/emscripten/emsdk:latest
```

### Howto map a native class

The official documentation starts [here](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#classes).

For LASzip, try a file `wasm.cpp`:

```
#include "../src/laszip.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(laszip) {
  class_<LASzip>("LASzip")
    .constructor<>()
    .function("check_coder", &LASzip::check_coder)
    ;
}
```

and

```
emcc -lembind -o laszip.js wasm.cpp ../src/laszip.cpp
```

- here the `wasm.cpp` defines the module and its entry points to be compiled (entry points are in this case the class constructors)
- public C++ classes need to be declared here (sometimes importing the respective `*.hpp` header file is sufficient)
- the first argument of the `EMSCRIPTEN_BINDINGS` macro defines the name of the `*.wasm` and `*.js` files generated
- the `emcc` compiler also needs the C++ implementation code of all classes involved (sometimes adding the respective `*.cpp` source files is sufficient)



## Differences to native LASzip

1. Only one constructor: JavaScript classes have only one constructor.
   More generally, JavaScript does not have adhoc overloads, it has
   dynamic types instead.
2. No destructors: JavaScript uses garbage collection instead. There is
   no language support for deterministic disposal like in C++.
