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
#include <QWidget>
#include <QLabel>

int
main(int argc, char **argv)
{
	QtWaylandShellHelpers::QWaylandShellApplication app(argc, argv);

	QWidget *root = new QWidget;
	QWidget *hello = new QLabel("Hello world!", root);

	root->show();

	return app.exec();
}