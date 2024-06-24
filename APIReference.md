# API Reference

## Classes
By module:

* [Built-in Basic Types](https://doc.qt.io/qt-5/qtqml-typesystem-basictypes.html#supported-basic-types)
* [`QtQml 2.15`](https://doc.qt.io/qt-5/qtqml-qmlmodule.html)
* [`QtQuick 2.15`](https://doc.qt.io/qt-5/qtquick-qmlmodule.html)
    * Its submodules are available at the above link.
* [`QtQuick.Controls 2.15`](https://doc.qt.io/qt-5/qtquick-controls2-qmlmodule.html)
* [`org.kde.kirigami 2.20`](https://api.kde.org/frameworks/kirigami/html/annotated.html)
    * [`PageRow` class](http://web.archive.org/web/20210621190613if_/https://api.kde.org/frameworks/kirigami/html/classorg_1_1kde_1_1kirigami_1_1PageRow.html)
        * This class is missing because of a bug.
* [`org.kde.kirigamiaddons 0.2`](https://api.kde.org/frameworks/kirigami-addons/html/annotated.html)
    * Introduced recently, so might not be available in your distribution.
* [`Qt.labs.calendar 1.0`](https://doc.qt.io/qt-5/qt-labs-calendar-qmlmodule.html)
* [`Qt.labs.platform 1.1`](https://doc.qt.io/qt-5/qt-labs-platform-qmlmodule.html)

## Constants

* [`StandardKey`](https://doc.qt.io/qt-6/qkeysequence.html#StandardKey-enum)
    * [See values](https://doc.qt.io/qt-6/qkeysequence.html#standard-shortcuts)

## Functions

* Most standard JavaScript functions ([list](https://doc.qt.io/qt-5/qtqml-javascript-functionlist.html#the-global-object))
* [`qsTr`](https://doc.qt.io/qt-5/qml-qtqml-qt.html#qsTr-method)
* [`qsTrId`](https://doc.qt.io/qt-6/qml-qtqml-qt.html#qsTrId-method)
* [`qsTrIdNoOp`](https://doc.qt.io/qt-5/qml-qtqml-qt.html#qsTrIdNoOp-method)
* [`qsTrNoOp`](https://doc.qt.io/qt-5/qml-qtqml-qt.html#qsTrNoOp-method)
* [`qsTranslate`](https://doc.qt.io/qt-5/qml-qtqml-qt.html#qsTranslate-method)
* [`qsTranslateNoOp`](https://doc.qt.io/qt-5/qml-qtqml-qt.html#qsTranslateNoOp-method)
* [`QT_TR_NOOP`](https://doc.qt.io/qt-5/qtglobal.html#QT_TR_NOOP)
* [`QT_TRANSLATE_NOOP`](https://doc.qt.io/qt-5/qtglobal.html#QT_TR_NOOP)
* [`QT_TRID_NOOP`](https://doc.qt.io/qt-5/qtglobal.html#QT_TR_NOOP)
* [`gc`](https://doc.qt.io/qt-5/qjsengine.html#collectGarbage)
* [`print`](https://developer.mozilla.org/en-US/docs/Web/API/console/debug) -- equivalent to `console.debug`

K18n (included with Kirigami and Plasma):
* [`i18n`](https://develop.kde.org/docs/extend/plasma/widget/translations-i18n/#i18n)
    * [C++ function](https://api.kde.org/frameworks/ki18n/html/klocalizedstring_8h.html#ade82e1747da8e802b9273e6ae1f18ab2)
* 

## Objects with functions

* [`console`](https://doc.qt.io/qt-5/qtquick-debugging.html#console-api)
    * [MDN Reference](https://developer.mozilla.org/en-US/docs/Web/API/console)
    * Not all functions are available.

## JavaScript classes

* [`QtQml 2.15`](https://doc.qt.io/qt-5/qtqml-javascript-functionlist.html)

Selected classes with differences:
* `String`
    * [Standard - ECMAScript 13](https://262.ecma-international.org/13.0/#sec-string-objects)
    * [Standard - ECMAScript with finished proposals](https://tc39.es/ecma262/#sec-string-objects)
    * [MDN reference](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String)
    * [method `.arg(value)`](https://doc.qt.io/qt-5/qml-qtqml-string.html#arg-method)
* `Date`
    * [MDN reference](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date)
    * [Qt extensions](https://doc.qt.io/qt-5/qml-qtqml-date.html)
* `Number`
    * [Qt extensions](https://doc.qt.io/qt-5/qml-qtqml-number.html)
* `XMLHTTPRequest`
    * [Qt limitations](https://doc.qt.io/qt-5/qtqml-javascript-qmlglobalobject.html#xmlhttprequest)
    * [Standard](https://xhr.spec.whatwg.org/)

All QML types are also JavaScript types.
