if(NOT __CPPLIBCOMPILATIONFLAGSCMAKE_LOADED)
    set(__CPPLIBCOMPILATIONFLAGSCMAKE_LOADED 1)
else()
    return()
endif()

# Use latest standard available but at least C++-14
if    (DEFINED CMAKE_CXX20_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX20_EXTENSION_COMPILE_OPTION)
    set(LatestCXXStandard 20)
elseif(DEFINED CMAKE_CXX17_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX17_EXTENSION_COMPILE_OPTION)
    set(LatestCXXStandard 17)
else()
    set(LatestCXXStandard 14)
endif()

add_library(CppLibCompileFlags INTERFACE)
add_library(CppLibPublicFlags INTERFACE)

# Targe alias
add_library(CppLib::CompileFlags ALIAS CppLibCompileFlags)
add_library(CppLib::PublicFlags ALIAS CppLibPublicFlags)

# CMake version before 3.13 do not provide 'target_link_options' <https://cmake.org/cmake/help/latest/command/target_link_options.html>
if (CMAKE_VERSION VERSION_LESS "3.13")
    macro(target_link_options)
        target_link_libraries(${ARGV0} ${ARGV1} ${ARGV2})
    endmacro(target_link_options)
endif()

# MSVC settings
if(MSVC)
    # Warning flags
    target_compile_options(CppLibCompileFlags INTERFACE "/Wall")

    if(MSVC_VERSION GREATER_EQUAL "1912")
        target_compile_options(CppLibCompileFlags INTERFACE "/permissive-") # disable MSVC extensions
    endif()

    # Disable undesirable warnings
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4514") # 'x': unreferenced inline function has been removed
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4571") # SEH related
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4623") # 'x': default constructor was implicitly defined as deleted
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4625") # 'x': copy constructor was implicitly defined as deleted
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4626") # 'x': assignment operator was implicitly defined as deleted
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4643") # Forward declaring 'x' in namespace std is not permitted by the C++ Standard.
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4710") # 'x': function not inlined
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4711") # function 'x' selected for automatic inline expansion
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4774") # 'x' : format string expected in argument y is not a string literal
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4820") # 'bytes' bytes padding added after construct 'member_name' - https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
    target_compile_options(CppLibCompileFlags INTERFACE "/wd5026") # 'x': move constructor was implicitly defined as deleted
    target_compile_options(CppLibCompileFlags INTERFACE "/wd5027") # 'x': move assignment operator was implicitly defined as deleted
    target_compile_options(CppLibCompileFlags INTERFACE "/wd4548") # expression before comma has no effect; expected expression with side-effect
    target_compile_options(CppLibCompileFlags INTERFACE "/wd5045") # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified

    # Treat warnings as errors when using msvc.
    target_compile_options(CppLibCompileFlags INTERFACE "/WX")

# Clang settings
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
    # Warning flags
    target_compile_options(CppLibCompileFlags INTERFACE "-Weverything")
    target_compile_options(CppLibCompileFlags INTERFACE "-Werror")

    # Disable undesirable warnings
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-covered-switch-default")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-c++1z-extensions")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-c++98-compat")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-c++98-compat-pedantic")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-c++98-c++11-compat-pedantic")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-documentation-unknown-command")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-double-promotion")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-missing-prototypes")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-missing-variable-declarations")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-padded")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-unused-parameter")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-unused-template")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-unused-variable")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-weak-vtables")

    # Optimization flags
    target_compile_options(CppLibCompileFlags INTERFACE "$<$<CONFIG:DEBUG>:-O0>")
    target_compile_options(CppLibCompileFlags INTERFACE "$<$<CONFIG:RELEASE>:-O3>")

    # processor architecture
    if(ARCH STREQUAL "x86")
        target_compile_options(CppLibPublicFlags INTERFACE "-m32")
        target_link_options(CppLibPublicFlags INTERFACE "-m32")
    elseif(ARCH STREQUAL "x64")
        target_compile_options(CppLibPublicFlags INTERFACE "-m64")
        target_link_options(CppLibPublicFlags INTERFACE "-m64")
    endif()

# GCC settings
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Warning flags
    target_compile_options(CppLibCompileFlags INTERFACE "-pedantic")
    target_compile_options(CppLibCompileFlags INTERFACE "-pedantic-errors")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wall")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wcast-align")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wcast-qual")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wconversion")
    target_compile_options(CppLibCompileFlags INTERFACE "-Weffc++")
    target_compile_options(CppLibCompileFlags INTERFACE "-Werror")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wextra")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wfloat-equal")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wformat=2")
    target_compile_options(CppLibCompileFlags INTERFACE "-Winline")
    target_compile_options(CppLibCompileFlags INTERFACE "-Winvalid-pch")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wlogical-op")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wmissing-declarations")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wmissing-field-initializers")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wmissing-include-dirs")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wmissing-noreturn")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wold-style-cast")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wpointer-arith")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wredundant-decls")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wshadow")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wstack-protector")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wstrict-aliasing=2")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wstrict-overflow=5")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wundef")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wunreachable-code")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wunused")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wunused-parameter")

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.6)
        target_compile_options(CppLibCompileFlags INTERFACE "-Wnoexcept")
    endif()

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0)
        target_compile_options(CppLibCompileFlags INTERFACE "-Wdouble-promotion")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wtrampolines")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wuseless-cast")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wvector-operation-performance")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wzero-as-null-pointer-constant")
    endif()

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
        target_compile_options(CppLibCompileFlags INTERFACE "-Wduplicated-cond")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wnull-dereference")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wshift-overflow=2")
    endif()

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        target_compile_options(CppLibCompileFlags INTERFACE "-Walloc-zero")
        target_compile_options(CppLibCompileFlags INTERFACE "-Walloca")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wduplicated-branches")
        target_compile_options(CppLibCompileFlags INTERFACE "-Wrestrict")
    endif()

    # Disable undesirable warnings
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-unused-function")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-missing-declarations")
    target_compile_options(CppLibCompileFlags INTERFACE "-Wno-inline")

    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.5)
        target_compile_options(CppLibCompileFlags INTERFACE "-Wno-error=suggest-attribute=noreturn")
    endif()

    # Optimization flags
    target_compile_options(CppLibCompileFlags INTERFACE "$<$<CONFIG:DEBUG>:-O0>")
    target_compile_options(CppLibCompileFlags INTERFACE "$<$<CONFIG:RELEASE>:-O3>")

    # processor architecture
    if(ARCH STREQUAL "x86")
        target_compile_options(CppLibPublicFlags INTERFACE "-m32")
        target_link_options(CppLibPublicFlags INTERFACE "-m32")
    elseif(ARCH STREQUAL "x64")
        target_compile_options(CppLibPublicFlags INTERFACE "-m64")
        target_link_options(CppLibPublicFlags INTERFACE "-m64")
    endif()
endif()
