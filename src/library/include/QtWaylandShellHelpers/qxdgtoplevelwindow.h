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

#ifndef QTWAYLANDSHELLHELPERS_QXDGTOPLEVELWINDOW_H
#define QTWAYLANDSHELLHELPERS_QXDGTOPLEVELWINDOW_H

#include <QApplication>
#include <QWidget>

#include <wayland-client.h>

#include <QtWaylandShellHelpers/qwaylandshellapplication.h>

struct wl_output;
struct wl_seat;
struct wl_surface;
struct xdg_popup;
struct xdg_positioner;
struct xdg_surface;
struct xdg_toplevel;
struct xdg_wm_base;

namespace QtWaylandShellHelpers {

class QXdgToplevelWindow : public QWidget
{
public:
    QXdgToplevelWindow(QWidget *parent = nullptr);
    ~QXdgToplevelWindow();

private:
    QWaylandShellApplication *mApp = nullptr;
};

}

#endif