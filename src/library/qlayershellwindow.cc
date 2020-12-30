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

#include <QDebug>
#include <QtWaylandShellHelpers/qlayershellwindow.h>
#include <qpa/qplatformnativeinterface.h>
#include <wlr-layer-shell-unstable-v1-client-protocol.h>

using namespace QtWaylandShellHelpers;

QLayerShellWindow::QLayerShellWindow(QWidget *parent)
    : QWidget(parent)
{
	mApp = qobject_cast<QWaylandShellApplication *>(qApp);
	if (mApp == nullptr)
	{
		qDebug() << "Attempting to make QLayerShellWindow without QWaylandShellApplication is not supported";
		abort();
	}

	// XXX: this totally breaks when CSD is actually needed
	setWindowFlags(Qt::FramelessWindowHint);
}

QLayerShellWindow::~QLayerShellWindow()
{
}

void
QLayerShellWindow::getSurfaces()
{
	auto native = mApp->platformNativeInterface();
	auto layerShell = mApp->zwlr_layer_shell_v1();

	if (mSurface == nullptr)
		mSurface = static_cast<::wl_surface *>(native->nativeResourceForWindow("surface", windowHandle()));

	if (mLayerSurface == nullptr)
	{
		mLayerSurface = ::zwlr_layer_shell_v1_get_layer_surface(layerShell, mSurface, NULL, (uint32_t) mLayer, "qt-wayland-shell-helpers");

		static ::zwlr_layer_surface_v1_listener surface_listener = {
			.configure = QLayerShellWindow::wlSurfaceConfigureEvent,
			.closed = QLayerShellWindow::wlSurfaceCloseEvent,
		};

		::zwlr_layer_surface_v1_add_listener(mLayerSurface, &surface_listener, this);
		commit();
	}
}

void
QLayerShellWindow::wlSurfaceConfigureEvent(void *data, ::zwlr_layer_surface_v1 *surface, uint32_t serial, uint32_t width, uint32_t height)
{
	auto win = static_cast<QLayerShellWindow *>(data);

	if (!width || !height)
		return;

	win->resize(win->mExpandHorizontal ? width : win->width(), win->mExpandVertical ? height : win->height());
	::zwlr_layer_surface_v1_ack_configure(win->mLayerSurface, serial);
}

void
QLayerShellWindow::wlSurfaceCloseEvent(void *data, ::zwlr_layer_surface_v1 *surface)
{
	auto win = static_cast<QLayerShellWindow *>(data);

	win->close();
}

void
QLayerShellWindow::commit()
{
	if (mLayerSurface == nullptr)
		return;

	::zwlr_layer_surface_v1_set_layer(mLayerSurface, (uint32_t) mLayer);
	::zwlr_layer_surface_v1_set_anchor(mLayerSurface, (uint32_t) mAnchor);
	::zwlr_layer_surface_v1_set_exclusive_zone(mLayerSurface, mExclusiveZone);
	::zwlr_layer_surface_v1_set_margin(mLayerSurface, mMarginTop, mMarginRight, mMarginBottom, mMarginLeft);
	::zwlr_layer_surface_v1_set_keyboard_interactivity(mLayerSurface, (uint32_t) mKeyboardInteractivity);

	::wl_surface_commit(mSurface);
	::wl_display_roundtrip(mApp->display());
}

void
QLayerShellWindow::resizeEvent(QResizeEvent *event)
{
	getSurfaces();

	::zwlr_layer_surface_v1_set_size(mLayerSurface, width(), height());
	commit();

	QWidget::resizeEvent(event);
}

void
QLayerShellWindow::showEvent(QShowEvent *event)
{
	getSurfaces();

	QWidget::showEvent(event);
}

void
QLayerShellWindow::setLayer(Layer layer)
{
	mLayer = layer;
	commit();
}

void
QLayerShellWindow::setAnchor(Anchor anchor)
{
	mAnchor = anchor;
	commit();
}

void
QLayerShellWindow::setExclusiveZone(int32_t zone)
{
	mExclusiveZone = zone;
	commit();
}

void
QLayerShellWindow::setExpansionAxis(bool horizontal, bool vertical)
{
	mExpandHorizontal = horizontal;
	mExpandVertical = vertical;
	commit();
}

void
QLayerShellWindow::setMargins(int32_t top, int32_t right, int32_t bottom, int32_t left)
{
	mMarginTop = top;
	mMarginRight = right;
	mMarginBottom = bottom;
	mMarginLeft = left;
	commit();
}

void
QLayerShellWindow::setKeyboardInteractivity(bool interactivity)
{
	mKeyboardInteractivity = interactivity;
	commit();
}
