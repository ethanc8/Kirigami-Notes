# Clazy

Unfortunately, when you install Clazy, `libLLVM-8` is not installed, which is a dependency of Clazy.. Additionally, Clazy's documentation also includes important metadata about Clazy that are used by KDevelop.

```bash
sudo apt install libllvm8 clazy-doc
```