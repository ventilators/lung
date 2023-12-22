project('lung', 'cpp', version : '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++20'])

includes      = include_directories('include')
dependencies  = [dependency('ventilation')]

lung_dep = declare_dependency(
  include_directories   : includes
  , dependencies        : dependencies
  )

if not meson.is_subproject()
  # subdir('example')
  subdir('tests')
endif
