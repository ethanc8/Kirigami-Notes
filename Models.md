# Models

* [Qt documentation - Models and Views in Qt Quick](https://doc.qt.io/qt-5/qtquick-modelviewsdata-modelview.html)

## Delegate

A copy of the delegate is created for each item in the model. 

A ListView delegate can access its view by the property `ListView.view`, and its model by the property `ListView.view.model`. Similary, GridView delegates can access their view by `GridView.view`, and their model by `GridView.view.model`. Delegates of other views can access their models and views in a similar manner.

## Types of model

### ListModel

A list of key-value pairs. The values *must* be basic QML types. The keys are provided to the delegate as properties of the delegate.

[API reference](https://doc.qt.io/qt-5/qml-qtqml-models-listmodel.html)

[Discussion](https://doc.qt.io/qt-5/qtquick-modelviewsdata-modelview.html#list-model)

### XMLListModel

Represents an XML file.