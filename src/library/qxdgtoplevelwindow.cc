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
#include <QtWaylandShellHelpers/qxdgtoplevelwindow.h>
#include <qpa/qplatformnativeinterface.h>
#include <xdg-shell-client-protocol.h>
#include <xdg-decoration-unstable-v1-client-protocol.h>

using namespace QtWaylandShellHelpers;

QXdgToplevelWindow::QXdgToplevelWindow(QWidget *parent)
    : QWidget(parent)
{
	mApp = qobject_cast<QWaylandShellApplication *>(qApp);
	if (mApp == nullptr)
	{
		qDebug() << "Attempting to make QXdgToplevelWindow without QWaylandShellApplication is not supported";
		abort();
	}

	// XXX: this totally breaks when CSD is actually needed
	setWindowFlags(Qt::FramelessWindowHint);
}

QXdgToplevelWindow::~QXdgToplevelWindow()
{
}

void
QXdgToplevelWindow::windowTitleChanged(const QString &title)
{
	updateWindowTitle();
}

void
QXdgToplevelWindow::wlSurfaceConfigureEvent(void *data, ::xdg_surface *xdg_surface, uint32_t serial)
{
	::xdg_surface_ack_configure(xdg_surface, serial);
}

void
QXdgToplevelWindow::wlToplevelConfigureEvent(void *data, ::xdg_toplevel *xdg_toplevel, int32_t width, int32_t height, ::wl_array *states)
{
	auto win = static_cast<QXdgToplevelWindow *>(data);

	if (!width || !height)
		return;

	win->resize(width, height);
}

void
QXdgToplevelWindow::wlToplevelCloseEvent(void *data, ::xdg_toplevel *xdg_toplevel)
{
	auto win = static_cast<QXdgToplevelWindow *>(data);

	win->close();
}

void
QXdgToplevelWindow::getSurfaces()
{
	auto native = mApp->platformNativeInterface();
	auto xdg = mApp->xdg_wm_base();

	if (mSurface == nullptr)
		mSurface = static_cast<::wl_surface *>(native->nativeResourceForWindow("surface", windowHandle()));

	if (mXdgSurface == nullptr)
	{
		mXdgSurface = ::xdg_wm_base_get_xdg_surface(xdg, mSurface);

		static ::xdg_surface_listener surface_listener = {
			.configure = QXdgToplevelWindow::wlSurfaceConfigureEvent,
		};

		::xdg_surface_add_listener(mXdgSurface, &surface_listener, this);
	}

	if (mXdgSurface != nullptr && mXdgToplevel == nullptr)
	{
		mXdgToplevel = ::xdg_surface_get_toplevel(mXdgSurface);

		static ::xdg_toplevel_listener toplevel_listener = {
			.configure = QXdgToplevelWindow::wlToplevelConfigureEvent,
			.close = QXdgToplevelWindow::wlToplevelCloseEvent,
		};

		::xdg_toplevel_add_listener(mXdgToplevel, &toplevel_listener, this);
		::wl_surface_commit(mSurface);
	}
}

void
QXdgToplevelWindow::resizeEvent(QResizeEvent *event)
{
	getSurfaces();

	::xdg_toplevel_set_min_size(mXdgToplevel, 2, 1);
	::xdg_surface_set_window_geometry(mXdgSurface, 0, 0, width(), height());
	::wl_surface_commit(mSurface);
	::wl_display_roundtrip(mApp->display());

	QWidget::resizeEvent(event);
}

void
QXdgToplevelWindow::setClientSideWindowDecoration(bool csd)
{
	auto decomgr = mApp->zxdg_decoration_manager_v1();

	if (mXdgToplevelDecoration == nullptr)
		mXdgToplevelDecoration = ::zxdg_decoration_manager_v1_get_toplevel_decoration(decomgr, mXdgToplevel);

	auto mode = csd == true ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE;

	::zxdg_toplevel_decoration_v1_unset_mode(mXdgToplevelDecoration);
	::zxdg_toplevel_decoration_v1_set_mode(mXdgToplevelDecoration, mode);
	::wl_surface_commit(mSurface);
	::wl_display_roundtrip(mApp->display());
}

void
QXdgToplevelWindow::showEvent(QShowEvent *event)
{
	getSurfaces();

	setClientSideWindowDecoration(false);
	updateWindowTitle();

	QWidget::showEvent(event);
}

void
QXdgToplevelWindow::updateWindowTitle()
{
	getSurfaces();

	auto title = windowTitle().toLocal8Bit();

	::xdg_toplevel_set_title(mXdgToplevel, title);
}