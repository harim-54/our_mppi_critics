# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_our_mppi_critics_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED our_mppi_critics_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(our_mppi_critics_FOUND FALSE)
  elseif(NOT our_mppi_critics_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(our_mppi_critics_FOUND FALSE)
  endif()
  return()
endif()
set(_our_mppi_critics_CONFIG_INCLUDED TRUE)

# output package information
if(NOT our_mppi_critics_FIND_QUIETLY)
  message(STATUS "Found our_mppi_critics: 0.0.0 (${our_mppi_critics_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'our_mppi_critics' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${our_mppi_critics_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(our_mppi_critics_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${our_mppi_critics_DIR}/${_extra}")
endforeach()
