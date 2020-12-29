subdir('include')

libqtwaylandshellhelpers_src = [
  'qwaylandshellapplication.cc',
]

libqtwaylandshellhelpers = library('qtwaylandshellhelpers',
  libqtwaylandshellhelpers_src,
  version: '0.0.0',
  include_directories: [libqtwaylandshellhelpers_inc],
  dependencies: [qt, wayland_client, client_protos],
  install: true)

libqtwaylandshellhelpers_dep = declare_dependency(
  link_with: libqtwaylandshellhelpers,
  include_directories: [libqtwaylandshellhelpers_inc],
  dependencies: [qt, wayland_client, client_protos],
)
