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
#include <QtWaylandShellHelpers/qlayershellwindow.h>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

QWidget *
make_example_panel()
{
	QtWaylandShellHelpers::QLayerShellWindow *panel = new QtWaylandShellHelpers::QLayerShellWindow;
	QHBoxLayout *hbox = new QHBoxLayout(panel);

	panel->setExpansionAxis(true, false);
	panel->setLayer(QtWaylandShellHelpers::QLayerShellWindow::Layer::Top);
	panel->setAnchor(static_cast<QtWaylandShellHelpers::QLayerShellWindow::Anchor>
			 ((int32_t) QtWaylandShellHelpers::QLayerShellWindow::Anchor::Top |
			 (int32_t) QtWaylandShellHelpers::QLayerShellWindow::Anchor::Left |
			 (int32_t) QtWaylandShellHelpers::QLayerShellWindow::Anchor::Right));

	QWidget *hello = new QLabel("This is a wlr-layer-shell panel.");
	hbox->addWidget(hello);

	return panel;
}

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
	QWidget::connect(newLayerShellWindow, &QAbstractButton::clicked, [=] (bool checked) {
		auto win = make_example_panel();
		win->show();
	});
	vbox->addWidget(newLayerShellWindow);

	root->show();

	return app.exec();
}