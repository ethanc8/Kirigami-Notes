# Embedding Native Views

## How-to

Qt for Android allows you to create a 

## Example: QtWebView

This is expressed as commented code.

Related classes:
* [`QJNIObjectPrivate`](https://invent.kde.org/qt/qt/qtbase/-/blob/kde/5.15/src/corelib/kernel/qjni_p.h#L94)
* [`org.qtproject.qt5.android.view.QtAndroidWebViewController`](https://invent.kde.org/qt/qt/qtwebview/-/blob/kde/5.15/src/jar/src/org/qtproject/qt5/android/view/QtAndroidWebViewController.java)
* [`android.webkit.WebView`](https://developer.android.com/reference/android/webkit/WebView) ([Source code](https://android.googlesource.com/platform/frameworks/base/+/refs/tags/android-13.0.0_r3/core/java/android/webkit/WebView.java))

```{note}
In Qt6, this no longer uses `QJNIObjectPrivate`, instead it uses the public API `QJNIObject`. Its API is almost the same as the Qt5 `QAndroidJNIObject`.
```

```c++
#include "qandroidwebview_p.h"
#include <private/qwebview_p.h>
#include <private/qwebviewloadrequest_p.h>
#include <QtCore/private/qjnihelpers_p.h>
#include <QtCore/private/qjni_p.h>

#include <QtCore/qmap.h>
#include <android/bitmap.h>
#include <QtGui/qguiapplication.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qurl.h>
#include <QtCore/qdebug.h>

static const char qtAndroidWebViewControllerClass[] = "org/qtproject/qt5/android/view/QtAndroidWebViewController";

typedef QMap<quintptr, QAndroidWebViewPrivate *> WebViews;
Q_GLOBAL_STATIC(WebViews, g_webViews)

QAndroidWebViewPrivate::QAndroidWebViewPrivate(QObject *p)
    : QAbstractWebView(p)
    , m_id(reinterpret_cast<quintptr>(this))
    , m_callbackId(0)
    , m_window(0)
{
    // org.qtproject.qt5.android.view.QtAndroidWebViewController(android.app.Activity, jlong) -> void
    // m_viewController = org.qtproject.qt5.android.view.QtAndroidWebViewController(QtAndroidPrivate::activity(), m_id)
    m_viewController = QJNIObjectPrivate(qtAndroidWebViewControllerClass,
                                         "(Landroid/app/Activity;J)V",
                                         QtAndroidPrivate::activity(),
                                         m_id);
    // .getWebView() -> android.webkit.WebView
    // m_webView = m_viewController.getWebView()
    m_webView = m_viewController.callObjectMethod("getWebView",
                                                  "()Landroid/webkit/WebView;");
    // Get QWindow from the m_webView.
    m_window = QWindow::fromWinId(reinterpret_cast<WId>(m_webView.object()));
    g_webViews->insert(m_id, this);
    connect(qApp, &QGuiApplication::applicationStateChanged,
            this, &QAndroidWebViewPrivate::onApplicationStateChanged);
}
```

## Libraries

* [Felgo Native Code Components (proprietary)](https://felgo.com/doc/felgo-native-code-components/)
* [2GIS QtOffscreenViews (BSD-3-Clause)](https://github.com/2gis/qtandroidextensions/tree/master/QtOffscreenViews)

You can also fork QtWebKit -- this is especially useful if you want to use different native views on other platforms, or want to create a web view implementation using a different rendering engine.