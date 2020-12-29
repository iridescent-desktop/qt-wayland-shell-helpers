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

#include <QApplication>

#include <wayland-client.h>

namespace QtWaylandShellHelpers {

class QWaylandShellApplication : public ::QApplication
{
public:
  QWaylandShellApplication(int &argc, char **argv, int = ApplicationFlags);
  ~QWaylandShellApplication();

  struct ::wl_display *display() const { return mDisplay; }

private:
  struct ::wl_display *mDisplay;
};

}

#endif