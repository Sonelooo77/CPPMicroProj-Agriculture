# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-src")
  file(MAKE_DIRECTORY "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-build"
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix"
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/tmp"
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/src/freetype-populate-stamp"
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/src"
  "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/src/freetype-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/src/freetype-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/sonel/Documents/CPP/MicroProjet/CardProject/out/build/x64-Debug/_deps/freetype-subbuild/freetype-populate-prefix/src/freetype-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
