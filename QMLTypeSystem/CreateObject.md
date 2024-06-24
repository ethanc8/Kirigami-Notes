# Creating an object

## As value of property

```qml
QtObject {
    id: myObject
    // Properties here
}
```

## Elsewhere in QML

Given a `QtQml.Component`:

```qml
Component {
    id: rectangleMaker
}
```

You can use the following code to construct an object:

```js
rectangleMaker.constructObject()
```

To destroy the object, call `destroy()` on the object.

## In JavaScript

Use `Qt.createQmlObject`.

The first argument is a string containing QML code. You must import all modules. Additionally, you should import using `import 'qrc:/'` any directories your type needs to import, even if the function is called in the directory that the type's superclasses are located in.

The second argument is the parent of the object. If the parent is destroyed, your object may or may not be destroyed.

The third argument is a fake file name, which QML will use as the file name when reporting errors. Example: `MotherHen::createChicks()::objectDefinition`.

### Example

```qml
// qrc:/Chicken/Chick.qml

import Animals 1.0 as Animals

Animals.Chicken {
    isYoung: true
}

// qrc:/Chicken/MotherHen.qml

import Animals 1.0 as Animals

Animals.Chicken {
    id: motherHen
    property list chicks: []

    function createChicks(numberOfChicks) {
        var currentChick
        while(currentChick <= numberOfChicks) {
            chicks.push(
                Qt.createQmlObject(
                    "import 'qrc:/Chicken'; Chick{}",
                    motherHen,
                    "MotherHen::createChicks()::chicks[" + currentChick + "]"
                )
            )
        }
    }
}
```