.onLoad <- function(libname, pkgname) {
  loadRcppModules();
  if (!.Call("load_library", PACKAGE="guitar")) {
    print("Could not load shared library; this is possibly not going to work.");
  }
}
