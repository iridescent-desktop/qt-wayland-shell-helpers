# Qt Wayland Shell Helpers

Use different types of Wayland shell protocols in the same application.

## Screenshot

![Demo program](screenshots/example.png)

## Caveats

* Some Qt widgets (built in menus) won't work properly due to the way they
  interact with QPA.
  You probably want to use custom widgets in those scenarios anyway though.

* CSD is probably completely broken.  This is probably fixable.

## Usage

Instead of using `QApplication`, use `QtWaylandShellHelpers::QWaylandShellApplication`,
then you can use `QtWaylandShellHelpers::QXdgToplevelWindow` or
`QtWaylandShellHelpers::QLayerShellWindow` depending on what you want to create.  If
you need something else, you can create your own subclasses of `QWidget`.