project('qt-wayland-shell-helpers', 'c', 'cpp', version: '0.1', meson_version: '>=0.50')

qt5 = import('qt5')

qt             = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'WaylandClient', 'XkbCommonSupport'])
wayland_client = dependency('wayland-client')
wayland_cursor = dependency('wayland-cursor')
wayland_protos = dependency('wayland-protocols', version: '>=1.14')

subdir('src')