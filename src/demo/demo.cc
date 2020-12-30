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
#include <QtWaylandShellHelpers/qxdgtoplevelwindow.h>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

QWidget *
make_example_xdg_toplevel_window()
{
	QtWaylandShellHelpers::QXdgToplevelWindow *root = new QtWaylandShellHelpers::QXdgToplevelWindow;
	root->setWindowTitle("Demo");

	QVBoxLayout *vbox = new QVBoxLayout(root);

	QWidget *hello = new QLabel("This is an XDG Toplevel Window.");
	vbox->addWidget(hello);

	return root;
}

int
main(int argc, char **argv)
{
	QtWaylandShellHelpers::QWaylandShellApplication app(argc, argv);

	QtWaylandShellHelpers::QXdgToplevelWindow *root = new QtWaylandShellHelpers::QXdgToplevelWindow;
	root->setWindowTitle("Demo Main Menu");

	QVBoxLayout *vbox = new QVBoxLayout(root);

	QWidget *welcomeLabel = new QLabel("Welcome to the QtWaylandShellHelpers demo program!");
	vbox->addWidget(welcomeLabel);

	auto newXdgWindow = new QPushButton("Open new XDG Toplevel window");
	QWidget::connect(newXdgWindow, &QAbstractButton::clicked, [=] (bool checked) {
		auto win = make_example_xdg_toplevel_window();
		win->show();
	});
	vbox->addWidget(newXdgWindow);

	auto newLayerShellWindow = new QPushButton("Open new wlr-layer-shell panel");
	vbox->addWidget(newLayerShellWindow);

	root->show();

	return app.exec();
}