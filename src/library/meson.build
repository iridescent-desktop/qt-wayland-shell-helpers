private_module_includes = '/usr/include/@0@/@1@/@0@'.format('QtGui', qt.version())

qt_private = include_directories(private_module_includes)

subdir('include')

libqtwaylandshellhelpers_src = [
  'qwaylandshellapplication.cc',
]

libqtwaylandshellhelpers = library('qtwaylandshellhelpers',
  libqtwaylandshellhelpers_src,
  version: '0.0.0',
  include_directories: [libqtwaylandshellhelpers_inc, qt_private],
  dependencies: [qt, wayland_client, client_protos],
  install: true)

libqtwaylandshellhelpers_dep = declare_dependency(
  link_with: libqtwaylandshellhelpers,
  include_directories: [libqtwaylandshellhelpers_inc, qt_private],
  dependencies: [qt, wayland_client, client_protos],
)
