
## How to Build

- You need to install Emscripten from https://emscripten.org/docs/getting_started/downloads.html, and have the environment variables set, as described in https://emscripten.org/docs/getting_started/downloads.html#installation-instructions
- You may also refer to our [Continuous Integration setup](https://github.com/ocornut/imgui/tree/master/.github/workflows) for Emscripten setup.
- Depending on your configuration, in Windows you may need to run `emsdk/emsdk_env.bat` in your console to access the Emscripten command-line tools.
- Then build using `make` while in the `example_emscripten/` directory.

## How to Run

To run on a local machine:
- Generally you may need a local webserver. Quoting [https://emscripten.org/docs/getting_started](https://emscripten.org/docs/getting_started/Tutorial.html#generating-html):<br>
_"Unfortunately several browsers (including Chrome, Safari, and Internet Explorer) do not support file:// [XHR](https://emscripten.org/docs/site/glossary.html#term-xhr) requests, and can’t load extra files needed by the HTML (like a .wasm file, or packaged file data as mentioned lower down). For these browsers you’ll need to serve the files using a [local webserver](https://emscripten.org/docs/getting_started/FAQ.html#faq-local-webserver) and then open http://localhost:8000/hello.html."_
- Emscripten SDK has a handy `emrun` command: `emrun example_emscripten.html` which will spawn a temporary local webserver. See https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html for details.
- Otherwise you may use Python builtin webserver: `python -m http.server` in Python 3 or `python -m SimpleHTTPServer` in Python 2. After doing that, you can visit http://localhost:8000/.

## Obsolete features:

- Emscripten 2.0 (August 2020) obsoleted the fastcomp backend, only llvm is supported.
- Emscripten 1.39.0 (October 2019) obsoleted the `BINARYEN_TRAP_MODE=clamp` compilation flag which was required with version older than 1.39.0 to avoid rendering artefacts. See [#2877](https://github.com/ocornut/imgui/issues/2877) for details. If you use an older version, uncomment this line in the Makefile: `#EMS += -s BINARYEN_TRAP_MODE=clamp`

## Compatibility

- Webgl2 is supported by almost all devices, but iOS is an exception. Currently, iOS can be turned on through Settings -> Safari -> Advanced -> Experimental Features -> WebGL 2.0, and the Demo can be successfully run.
- After testing on multiple devices, it is found that *glUniformMatrix4fv* has a **bug** in **iOS 14**. Currently, *glUniform4fv(loc, 4, ptr)* is used instead to ensure compatibility with iOS.

## Speed up

Quoting emscripten.org
>Even if your application does not need any WebGL 2/OpenGL ES 3 features, consider porting the application to run on WebGL 2, because JavaScript side performance in WebGL 2 has been optimized to generate no temporary garbage, which has been observed to give a solid 3-7% speed improvement, as well as reducing potential stuttering at render time. To enable these optimizations, build with the linker flag -s MAX_WEBGL_VERSION=2 and make sure to create a WebGL 2 context at GL startup time (OpenGL ES 3 context if using EGL). [https://emscripten.org/docs/optimizing/Optimizing-WebGL.html](https://emscripten.org/docs/optimizing/Optimizing-WebGL.html#which-gl-mode-to-target)