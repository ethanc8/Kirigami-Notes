# Creator Object

This is a nonstandard way to simplify the creation of objects.

```qml
// Creates a `Task`
Component {
    id: taskCreator
    Task {
        property var creatingComponent: TaskCreator
    }

    function simpleCopyWithParent(self, parent) {
        return taskCreator.createObject(
            parent,
            {
                name: self.name.valueOf(),
                description: self.description.valueOf(),
                dueDate: new Date(self.dueDate),
                completionTime: self.completionTime.simpleCopyWithParent(parent)
            }
        )
    }

    function newWithParent(parent) {
        return taskCreator.createObject(parent)
    }
}
```

Remember, if you create an object dynamically, you must destroy it with `destroy()`!