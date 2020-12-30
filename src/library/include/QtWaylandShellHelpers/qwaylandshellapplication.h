/*
 * Copyright (c) 2020 Ariadne Conill <ariadne@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#ifndef QTWAYLANDSHELLHELPERS_QWAYLANDSHELLAPPLICATION_H
#define QTWAYLANDSHELLHELPERS_QWAYLANDSHELLAPPLICATION_H

#include <cstdint>
#include <QApplication>

#include <wayland-client.h>

struct xdg_wm_base;
struct zxdg_decoration_manager_v1;
struct zwlr_layer_shell_v1;

namespace QtWaylandShellHelpers {

class QWaylandShellApplication : public ::QApplication
{
  Q_OBJECT

public:
  QWaylandShellApplication(int &argc, char **argv, int = ApplicationFlags);
  ~QWaylandShellApplication();

  ::wl_display *display() const { return mDisplay; }
  ::wl_registry *registry() const { return mRegistry; }
  ::xdg_wm_base *xdg_wm_base() const { return mXdgWmBase; }
  ::zxdg_decoration_manager_v1 *zxdg_decoration_manager_v1() const { return mXdgDecorationManagerV1; }
  ::zwlr_layer_shell_v1 *zwlr_layer_shell_v1() const { return mWlrLayerShellV1; }

  static void registryListener(void *data, ::wl_registry *registry, uint32_t name, const char *interface, uint32_t version);
  static void registryRemoveListener(void *data, ::wl_registry *registry, uint32_t name);

private:
  ::wl_display *mDisplay;
  ::wl_registry *mRegistry;
  ::xdg_wm_base *mXdgWmBase;
  ::zxdg_decoration_manager_v1 *mXdgDecorationManagerV1;
  ::zwlr_layer_shell_v1 *mWlrLayerShellV1;
};

}

#endif