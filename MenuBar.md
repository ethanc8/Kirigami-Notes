# Menu Bar

Unfortunately, Qt Quick 2 contains two types of menubars -- a global one (like on Mac and Unity7, as well as customized KDE, MATE, Xfce, GNOME, and Vala-panel) and a local one, that always shows in the window, even if the desktop environment uses a global menu.

Also, the two menu bars use very similar, but slightly different APIs.

For a local menubar, you use [`QtQuick.Controls.MenuBar`](https://doc.qt.io/qt-5/qml-qtquick-controls2-menubar.html). You add [`QtQuick.Controls.Menu`](https://doc.qt.io/qt-5/qml-qtquick-controls2-menu.html)s, which contains either Actions (Qt Quick 2 or Kirigami) or [`QtQuick.Controls.MenuItem`](https://doc.qt.io/qt-5/qml-qtquick-controls2-menuitem.html)s.

For a global menubar, you use [`Qt.labs.platform.MenuBar`](https://doc.qt.io/qt-5/qml-qt-labs-platform-menubar.html). You add
