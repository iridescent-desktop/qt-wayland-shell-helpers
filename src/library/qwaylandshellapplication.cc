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
#include <QtWaylandShellHelpers/qwaylandshellapplication.h>

#include <qpa/qplatformnativeinterface.h>

#include <xdg-shell-client-protocol.h>
#include <wlr-layer-shell-unstable-v1-client-protocol.h>
#include <xdg-decoration-unstable-v1-client-protocol.h>

using namespace QtWaylandShellHelpers;

void
QWaylandShellApplication::registryListener(void *data, ::wl_registry *registry, uint32_t name, const char *interface, uint32_t version)
{
	QWaylandShellApplication *app = static_cast<QWaylandShellApplication *>(data);

	if (!::strcmp(interface, ::xdg_wm_base_interface.name))
		app->mXdgWmBase = (::xdg_wm_base *) ::wl_registry_bind(registry, name, &::xdg_wm_base_interface, 1);
	else if (!::strcmp(interface, ::zxdg_decoration_manager_v1_interface.name))
		app->mXdgDecorationManagerV1 = (::zxdg_decoration_manager_v1 *) ::wl_registry_bind(registry, name, &::zxdg_decoration_manager_v1_interface, 1);
	else if (!::strcmp(interface, ::zwlr_layer_shell_v1_interface.name))
		app->mWlrLayerShellV1 = (::zwlr_layer_shell_v1 *) ::wl_registry_bind(registry, name, &::zwlr_layer_shell_v1_interface, 2);
}

void
QWaylandShellApplication::registryRemoveListener(void *data, ::wl_registry *registry, uint32_t name)
{
}

QWaylandShellApplication::QWaylandShellApplication(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
{
	::setenv("QT_WAYLAND_SHELL_INTEGRATION", "qwaylandshellhelpers", 1);

	QPlatformNativeInterface *native = platformNativeInterface();

	mDisplay = (struct ::wl_display *) native->nativeResourceForWindow("display", NULL);
	if (mDisplay == nullptr)
	{
		qDebug() << "Failed to get display handle!  Is this compositor working?";
		return;
	}

	mRegistry = (struct ::wl_registry *) ::wl_display_get_registry(mDisplay);
	if (mRegistry == nullptr)
	{
		qDebug() << "Failed to get mRegistry handle!  Is this compositor working?";
		return;
	}

	static const struct ::wl_registry_listener registry_listener = {
		.global = QWaylandShellApplication::registryListener,
		.global_remove = QWaylandShellApplication::registryRemoveListener,
	};
	::wl_registry_add_listener(mRegistry, &registry_listener, this);
	::wl_display_roundtrip(mDisplay);
}

QWaylandShellApplication::~QWaylandShellApplication()
{
}

#include "qwaylandshellapplication.moc"