private_module_includes = '/usr/include/@0@/@1@/@0@'.format('QtGui', qt.version())

qt_private = include_directories(private_module_includes)

subdir('include')

libqtwaylandshellhelpers_src = [
  'qwaylandshellapplication.cc',
  'qxdgtoplevelwindow.cc',
  'qlayershellwindow.cc',
]

libqtwaylandshellhelpers_moc_src = [
  'include/QtWaylandShellHelpers/qwaylandshellapplication.h',
]

libqtwaylandshellhelpers_moc = qt5.preprocess(moc_sources: libqtwaylandshellhelpers_moc_src)

libqtwaylandshellhelpers = library('qtwaylandshellhelpers', [
    libqtwaylandshellhelpers_src,
    libqtwaylandshellhelpers_moc,
  ],
  version: '0.0.0',
  include_directories: [libqtwaylandshellhelpers_inc, qt_private],
  dependencies: [qt, wayland_client, client_protos],
  install: true)

libqtwaylandshellhelpers_dep = declare_dependency(
  link_with: libqtwaylandshellhelpers,
  include_directories: [libqtwaylandshellhelpers_inc],
  dependencies: [qt, wayland_client, client_protos],
)

pkg = import('pkgconfig')
pkg.generate(libqtwaylandshellhelpers,
  name: 'QtWaylandShellHelpers',
  description: 'a library for using arbitrary Wayland surfaces with Qt',
  url: 'http://github.com/iridescent-desktop/qt-wayland-shell-helpers',
  requires: ['Qt5Core', 'Qt5Gui', 'Qt5Widgets', 'Qt5WaylandClient', wayland_client],
)