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

#include <cstdint>
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
struct zxdg_toplevel_decoration_v1;

namespace QtWaylandShellHelpers {

class QXdgToplevelWindow : public QWidget
{
public:
    QXdgToplevelWindow(QWidget *parent = nullptr);
    ~QXdgToplevelWindow();

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void windowTitleChanged(const QString &title);

    void updateWindowTitle();

    void setClientSideWindowDecoration(bool csd);

    static void wlSurfaceConfigureEvent(void *data, ::xdg_surface *xdg_surface, uint32_t serial);

    static void wlToplevelConfigureEvent(void *data, ::xdg_toplevel *xdg_toplevel, int32_t width, int32_t height, ::wl_array *states);
    static void wlToplevelCloseEvent(void *data, ::xdg_toplevel *xdg_toplevel);

private:
    void getSurfaces();

    QWaylandShellApplication *mApp = nullptr;

    ::wl_surface *mSurface;
    ::xdg_surface *mXdgSurface;
    ::xdg_toplevel *mXdgToplevel;
    ::zxdg_toplevel_decoration_v1 *mXdgToplevelDecoration;
};

}

#endif