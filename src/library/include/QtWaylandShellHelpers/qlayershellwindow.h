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

#ifndef QTWAYLANDSHELLHELPERS_QLAYERSHELLWINDOW_H
#define QTWAYLANDSHELLHELPERS_QLAYERSHELLWINDOW_H

#include <cstdint>
#include <QApplication>
#include <QWidget>

#include <wayland-client.h>

#include <QtWaylandShellHelpers/qwaylandshellapplication.h>

struct wl_output;
struct wl_surface;
struct xdg_popup;
struct zwlr_layer_shell_v1;
struct zwlr_layer_surface_v1;

namespace QtWaylandShellHelpers {

class QLayerShellWindow : public QWidget
{
public:
    enum class Layer {
        Background = 0,
        Bottom = 1,
        Top = 2,
        Overlay = 3,
    };

    enum class Anchor {
        None = 0,
        Top = 1,
        Bottom = 2,
        Left = 4,
        Right = 8,
    };

    QLayerShellWindow(QWidget *parent = nullptr);
    ~QLayerShellWindow();

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

    void setLayer(Layer layer);
    void setAnchor(Anchor anchor);
    void setExclusiveZone(int32_t zone);
    void setMargins(int32_t top, int32_t right, int32_t bottom, int32_t left);
    void setKeyboardInteractivity(bool interactivity);
    void setExpansionAxis(bool horizontal, bool vertical);

    static void wlSurfaceConfigureEvent(void *data, ::zwlr_layer_surface_v1 *layer, uint32_t serial, uint32_t width, uint32_t height);
    static void wlSurfaceCloseEvent(void *data, ::zwlr_layer_surface_v1 *layer);

private:
    void getSurfaces();
    void commit();

    QWaylandShellApplication *mApp = nullptr;

    ::wl_surface *mSurface = nullptr;
    ::zwlr_layer_surface_v1 *mLayerSurface = nullptr;
    Layer mLayer = Layer::Background;
    Anchor mAnchor = Anchor::None;
    int32_t mExclusiveZone = 0;
    int32_t mMarginTop = 0;
    int32_t mMarginRight = 0;
    int32_t mMarginBottom = 0;
    int32_t mMarginLeft = 0;
    bool mKeyboardInteractivity = false;
    bool mExpandHorizontal = true;
    bool mExpandVertical = false;
};

}

#endif