# qmllint

qmllint is a tool shipped with Qt, that verifies the syntatic validity of QML files. It also warns about some QML anti-patterns. If you want to disable a specific warning type, you can find the appropriate flag for doing so by passing `--help` on the command line.

By default, some issues will result in warnings that will be printed and result in a non-zero exit code. Minor issues however (such as unused imports) are just informational messages by default and will not affect the exit code. qmllint is very configurable and allows for disabling warnings or changing how they are treated. Users may freely turn any issue into a warning, informational message, or disable them outright.

qmllint warns about:

* Unqualified accesses of properties.
* Usage of signal handlers without a matching signal.
* Usage of with statements in QML.
* Unused imports.
* Deprecated components and properties.
* Syntax errors.
* And many other things.

> **Note:** In order for qmllint to work properly, it requires type information. That information is provided by QML modules in the import paths. The current directory, as well as the import paths for Qt's built-in types, are used as import paths by default. To add more import paths not included in the default, add them via the `-I` flag.

To get an overview and explanation of all available command line options, run qmllint --help.

```
Usage: /usr/lib/qt5/bin/qmllint [options] files
QML syntax verifier

Options:
  -h, --help                 Displays help on commandline options.
  --help-all                 Displays help including Qt specific options.
  -v, --version              Displays version information.
  -s, --silent               Don't output syntax errors
  -U, --check-unqualified    Warn about unqualified identifiers
  -I, --qmldirs <directory>  Look for qmltypes files in specified directory
  -i, --qmltypes <qmltypes>  Include the specified qmltypes files

Arguments:
  files                      list of qml or js files to verify
```
