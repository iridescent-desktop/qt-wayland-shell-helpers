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

#include <cstdio>
#include <QtWaylandShellHelpers/qxdgtoplevelwindow.h>

using namespace QtWaylandShellHelpers;

QXdgToplevelWindow::QXdgToplevelWindow(QWidget *parent)
    : QWidget(parent)
{
	mApp = qobject_cast<QWaylandShellApplication *>(qApp);
	if (mApp == nullptr)
	{
		fprintf(stderr, "Attempting to make QXdgToplevelWindow without QWaylandShellApplication.\n");
		abort();
	}
}

QXdgToplevelWindow::~QXdgToplevelWindow()
{
}