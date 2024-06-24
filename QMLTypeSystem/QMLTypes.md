# QML Types

## Type object

You can use a typename as an object. Its behavior is very weird, and you probably shouldn't use it.

```
QJS > Multi = Qt.createQmlObject("import QtQml 2.15; QtObject { component Inner: QtObject { property int aNumber; function doSomething() {aNumber += 1; } } property Inner anInner: Inner {} property var innerClass: Inner}", Qt.application, "CreatedObject")
value: CreatedOb_QMLTYPE_6(0x556336101260)
QJS > Multi.innerClass
value: [object Object]
QJS > Multi.innerClass.objectName
value: undefined
QJS > Multi.objectName
value: 
QJS > Multi.innerClass.objectName = "Inner"
value: Inner
QJS > Multi.innerClass.objectName
value: undefined
QJS > Multi.innerClass.class
value: undefined
QJS > Multi.innerClass.staticMetaObject
value: undefined
QJS > Multi.innerClass.metaObject
value: undefined
QJS > Multi.innerClass.isPrototypeOf(Multi.anInner)
value: false
QJS > Object.keys(Multi.innerClass)
value: 
QJS > Multi.innerClass == null
value: false
QJS > for (key in Multi.innerClass) { console.log(key) }
value: undefined
QJS > Multi.anInner instanceof Multi.innerClass
Segmentation fault
```

However, if called from a QML file, and not `QQmlEngine::evaluate`, `Object.keys(`*a typename*`)` will result in:

```
TypeError: Value is null and could not be converted to an object
```