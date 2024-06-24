#include <QObject>

class MyClass: public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE int doSomething(int);
signals:
    void didSomething(int);
public slots:
    void onDidSomething(int);
};