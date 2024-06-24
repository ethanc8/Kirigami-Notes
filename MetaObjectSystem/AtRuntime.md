# Doing things at runtime

Qt's Meta Object System adds dynamism to the C++ language for classes derived from `QObject`.

It can be compared to the Objective-C runtime, and throughout this guide, it will be compared to the Objective-C runtime.

## Creating classes at runtime

* [Newer example](https://github.com/GIPdA/DynamicMetaobject)
* [Qt 4 example](https://doc.qt.io/archives/qq/qq16-dynamicqobject.html)
* "Dynamic Meta Objects" presentation
    * [Slideshow](https://web.archive.org/web/20201202083129if_/https://www.qtdeveloperdays.com/sites/default/files/QtDevDays2014US-DIY-moc.pdf)
    * [Video](https://youtu.be/rtIBjTPE45Q)
* [`QMetaObjectBuilder`](https://invent.kde.org/qt/qt/qtbase/-/blob/kde/5.15/src/corelib/kernel/qmetaobjectbuilder_p.h#L72)

## Instantiating and destroying instances of classes

We need to use [`QMetaType`](https://doc.qt.io/qt-5/qmetatype.html#details) to get access to classes at runtime. This means the classes have to be declared with [`Q_DECLARE_METATYPE`](https://doc.qt.io/qt-5/qmetatype.html#Q_DECLARE_METATYPE). However, you can declare them like this in your code, so you can still do this if the upstream header doesn't declare the metatype.

```cpp
#include "MyClass.h"
Q_DECLARE_METATYPE(MyClass)

int MyClass_meta = QMetaType::type("MyClass");
if (MyClass_meta != QMetaType::UnknownType) {
    void* instance = QMetaType::create(MyClass_meta);
    ...
    QMetaType::destroy(MyClass_meta, instance);
    instance = 0;
}
```

## Calling methods

You can only call methods that are marked with `Q_INVOKABLE` or are slots (marked with `slots`, `Q_SLOTS`, or `Q_SLOT`).

Use the method [`QMetaObject::invokeMethod`](https://doc.qt.io/qt-5/qmetaobject.html#invokeMethod).

### Simple Example

```cpp
QThread* thread;
// Do things with the thread
thread->quit();
```

is equivalent to:

```cpp
QThread* thread;
// Do things with the thread
QMetaObject::invokeMethod(thread, "quit", Qt::DirectConnection);
```

### More complicated example

```cpp
MyObject* obj;
QString retVal = obj->compute("sqrt", 42, 9.7)
```

is equivalent to:

```cpp
MyObject* obj;
QString retVal;
QMetaObject::invokeMethod(obj, "compute", Qt::DirectConnection,
                          Q_RETURN_ARG(QString, retVal),
                          Q_ARG(QString, "sqrt"),
                          Q_ARG(int, 42),
                          Q_ARG(double, 9.7));
```

### Comparison with Objective-C

Objective-C has `objc_msgSend` to do something very similar. However, rather than using macros which wrap the argument, Objective-C requires you to type-cast the `objc_msgSend` to the correct type.

On the GCC runtime, some versions of GCC will instead invoke a function which returns a pointer to the implementation of a method.

Objective-C allows your class to implement a method at runtime when the object recieves it, so the programmer doesn't know that the method might be called, yet it will still be implemented.

Qt, rather, uses a 

### Behind the scenes

* [`QMetaObject::invokeMethod`](https://invent.kde.org/qt/qt/qtbase/-/blob/kde/5.15/src/corelib/kernel/qmetaobject.cpp#L1458)
* [`QMetaMethod::invoke`](https://invent.kde.org/qt/qt/qtbase/-/blob/kde/5.15/src/corelib/kernel/qmetaobject.cpp#L2207)
* [`QMetaObject::metacall`](https://invent.kde.org/qt/qt/qtbase/-/blob/kde/5.15/src/corelib/kernel/qmetaobject.cpp#L312)
* [Relevant blog post](https://programmer.group/qt-metaobject-system-explanation-4-metacall.html)
* [More details - focuses on slots and signals](https://woboq.com/blog/how-qt-signals-slots-work.html)

Most important part:

```cpp
// Create an array of the paramaters
void *param[] = {
    returnValue.data(),
    val0.data(),
    val1.data(),
    val2.data(),
    val3.data(),
    val4.data(),
    val5.data(),
    val6.data(),
    val7.data(),
    val8.data(),
    val9.data()
};
int idx_relative = QMetaMethodPrivate::get(this)->ownMethodIndex();
int idx_offset =  mobj->methodOffset();
Q_ASSERT(QMetaObjectPrivate::get(mobj)->revision >= 6);
// Get implementation of method
QObjectPrivate::StaticMetaCallFunction callFunction = mobj->d.static_metacall;

if (connectionType == Qt::DirectConnection) {
    // If the implementation exists
    if (callFunction) {
        // Call the implementation
        callFunction(object, QMetaObject::InvokeMetaMethod, idx_relative, param);
        // The operation was sucessful
        return true;
    } else {
        // Use the `metacall` system to try to invoke the method
        // The operation was sucessful if the return value is less than 0.
        return QMetaObject::metacall(object, QMetaObject::InvokeMetaMethod, idx_relative + idx_offset, param) < 0;
    }
} else {
    // Implementation for asynchronous calls
}

// ...
int QMetaObject::metacall(QObject *object, Call cl, int idx, void **argv)
{
    if (object->d_ptr->metaObject)
        return object->d_ptr->metaObject->metaCall(object, cl, idx, argv);
    else
        return object->qt_metacall(cl, idx, argv);
}

```