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

#include <QtWaylandShellHelpers/qwaylandshellapplication.h>

#include <qpa/qplatformnativeinterface.h>

using namespace QtWaylandShellHelpers;

QWaylandShellApplication::QWaylandShellApplication(int &argc, char **argv, int flags)
    : QApplication(argc, argv, flags)
{
	::setenv("QT_WAYLAND_SHELL_INTEGRATION", "qwaylandshellhelpers", 1);

	QPlatformNativeInterface *native = platformNativeInterface();
	mDisplay = (struct wl_display *) native->nativeResourceForWindow("display", NULL);
}

QWaylandShellApplication::~QWaylandShellApplication()
{
}