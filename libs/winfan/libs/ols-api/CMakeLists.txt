cmake_minimum_required(VERSION 3.17)
project(ols_api)

set(CMAKE_CXX_STANDARD 14)
add_compile_definitions(_UNICODE)
add_compile_definitions(UNICODE)
add_library(WinRing0x64 SHARED include/ols-api/OlsApiInit.h OlsApiInitDef.h OlsApiInitExt.h OlsDef.h OlsApi.cpp include/ols-api/OlsApi.h OlsDll.h OlsIoctl.h OlsDll.cpp Driver.h Driver.cpp OlsApi.def)