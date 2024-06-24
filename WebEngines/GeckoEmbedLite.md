# Gecko EmbedLite

Gecko's EmbedLite API, also known as IPCLite, is an API designed to make embedding of Gecko easier for non-XUL applications. It is currently [maintained out-of-tree](https://github.com/sailfishos/gecko-dev) by Jolla.

EmbedLite uses inter-process communication and separates the UI and Content threads. The basic architecture is similar to WebKit2:

![WebKit2 architecture](https://trac.webkit.org/raw-attachment/wiki/WebKit2/webkit2-stack.png)

* [Wiki page about EmbedLite](https://wiki.mozilla.org/Embedding/IPCLiteAPI)
* [Interesting blogpost giving a high-level overview](https://www.chrislord.net/2016/03/08/state-of-embedding-in-gecko/)
    * EmbedLite isn't dead -- it's currently using Gecko 78.15.1.
    * This is still a bit outdated (they updated Gecko to 78.15.1 when it was about to be EOL)
    * However, it's still actively maintained by a commercial company
* [What's behind Sailfish browser](https://rojkov.github.io/posts/whats-behind-sailfish-browser/)
* [Picture from above post - architecture of QtMozEmbed and EmbedLite](https://web.archive.org/web/20180830101652if_/http://blog.idempotent.info/images/qtembed.png)
* [EmbedLite Initialization - followup to previous post](https://rojkov.github.io/posts/embedlite-initialization/)
* [Outdated - How to Configure Devel Environment to Work on Gecko for Sailfishos](https://rojkov.github.io/posts/how-to-configure-devel-environment-to-work-on-gecko-for-sailfishos/)

The headers are available [here](https://github.com/sailfishos/gecko-dev/tree/master/embedding/embedlite). The APIs might still be internal -- if you're using Qt, you should use [QtMozEmbed](QtMozEmbed.md) instead -- this is a higher-level wrapper around EmbedLite.

## Users

* [CuteFox - NemoMobile package](https://github.com/nemomobile-packages/cutefox)
* [QMLMozBrowser](https://github.com/tmeshkova/qmlmozbrowser)
* [Sailfish browser](https://github.com/sailfishos/sailfish-browser)
    * [Documentation](https://docs.sailfishos.org/Reference/Core_Areas_and_APIs/Browser/)

## EmbedLite vs old embedding API

From the wiki page.

* No XUL/XPCOM heavy content in UI process/Thread
    * Best memory footprint (process case)
    * fast startup
* Process/Thread communication between UI and Content(Gecko/XPCOM) Thread/Process
    * built on current Mozilla Chromium/IPDL implementation 
    * [IPDL Tutorial](http://web.archive.org/web/20170110164723if_/https://developer.mozilla.org/en-US/docs/Mozilla/IPDL/Tutorial)
* Rendering based on Shadow/Shadowable layers tree which provide MultiThread/Process responsive rendering 
    * same as content rendering in XUL Mobile FF/OMTC Android Firefox/Firefox OS
* Multi process model provide ability to load memory greedy content in child process and kill it without increasing memory usage for Main UI application process

## Prebuilt packages (for Sailfish OS)

Go to https://releases.jolla.com/releases/*Your version number*/jolla/*Your architecture*/repodata/repomd.xml, and find the `primary.xml` file's path. Download the `primary.xml`, and search for `<name>xulrunner-qt5`.

* `xulrunner-qt5` - EmbedLite Gecko - [armv7hl](https://releases.jolla.com/releases/4.4.0.68/jolla/armv7hl/oss/armv7hl/xulrunner-qt5-78.15.1+git24.3-1.32.1.jolla.armv7hl.rpm) - [aarch64](https://releases.jolla.com/releases/4.4.0.68/jolla/aarch64/oss/aarch64/xulrunner-qt5-78.15.1+git24.3-1.32.1.jolla.aarch64.rpm) - [i486](https://releases.jolla.com/releases/4.4.0.68/jolla/i486/oss/i486/xulrunner-qt5-78.15.1+git24.3-1.32.1.jolla.i486.rpm)
* There's also `xulrunner-qt5-debuginfo`, `xulrunner-qt5-debugsource`, `xulrunner-qt5-devel`, and `xulrunner-qt5-misc`
* `embedlite-components-search-engines` - Default search engines - [noarch](https://releases.jolla.com/releases/4.4.0.68/jolla/armv7hl/oss/noarch/embedlite-components-search-engines-0.0.5-1.6.1.jolla.noarch.rpm)
* `embedlite-components-qt5` - additional APIs and configuration files - [armv7hl](https://releases.jolla.com/releases/4.4.0.68/jolla/armv7hl/oss/armv7hl/embedlite-components-qt5-1.24.33-1.35.1.jolla.armv7hl.rpm) - also available for other architectures
* There's also `embedlite-components-qt5-debuginfo` and `embedlite-components-qt5-debugsource`

## Building EmbedLite

EmbedLite Gecko can currently only be built with the RPM build system, resulting in a package called `xulrunner-qt5` and `xulrunner-qt5-devel`. Neither of the packages should actually contain XULRunner.

<!-- 1. Clone EmbedLite Gecko -- replace "sailfishos/78.15.1+git31" with the [most recent tag](https://github.com/sailfishos/gecko-dev/tags). It will take a while to clone gecko, but `--depth=1` will make it go a lot faster.
```bash
git clone https://github.com/sailfishos/gecko-dev.git --branch 78.15.1+git31 --depth=1
cd gecko-dev
git submodule init
git submodule update --depth=1
``` -->

1. Download the source package. It will take a few minutes -- Gecko is a very large codebase.
```bash
wget https://releases.jolla.com/releases/4.4.0.68/jolla/armv7hl/oss/src/xulrunner-qt5-78.15.1+git24.3-1.32.1.jolla.src.rpm
```

### Build dependencies

```bash
sudo apt install rustc cargo qtdeclarative5-dev qtbase5-dev libpango1.0-dev libasound2-dev libnspr4-dev libnss3-dev libsqlite3-dev libpulse-dev libproxy-dev libavcodec-dev libavfilter-dev libavformat-dev libswresample-dev libswscale-dev qtpositioning5-dev libdconf-dev qttools5-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools autoconf2.13 automake python3 zip unzip cbindgen llvm libclang-dev clang libatomic1 libatomic-ops-dev libicu-dev libhunspell-dev bzip2 librust-bzip2-dev libbz2-dev zlib1g-dev libpng-dev libpng16-16 yasm nasm fdupes libffi-dev libpixman-1-dev libvpx-dev libwebp-dev
```
Debian only -- all supported versions
```bash
sudo apt install libjpeg62-turbo-dev 
```
Ubuntu only -- all supported versions
```bash
sudo apt install libjpeg-turbo8-dev
```

If `cbindgen` is older than `0.12.1`:
```bash
sudo apt remove cbindgen
sudo cargo install cbindgen --root /usr/local
```

If `libicu` is older than `67.1`:
```bash
# Download from Bullseye -- its dependencies are really low
# Replace `amd64` with your architecture
wget https://deb.debian.org/debian/pool/main/i/icu/libicu67_67.1-7_amd64.deb https://deb.debian.org/debian/pool/main/i/icu/libicu-dev_67.1-7_amd64.deb http://ftp.us.debian.org/debian/pool/main/i/icu/icu-devtools_67.1-7_amd64.deb
sudo apt install ./*icu*_67.1-7_amd64.deb
```

* [libcontentaction](https://github.com/sailfishos/libcontentaction)
* [gecko-camera](https://github.com/sailfishos/gecko-camera)
* nss-ckbi
* bzip2-devel

### Building RPM packages for desktop

2. Install `rpm` and `rpmbuild` -- on Ubuntu and Debian, this is:
```bash
sudo apt install rpm rpmbuild
```
3. Build the package:
```bash
rpmbuild -rb xulrunner-qt5-*.jolla.src.rpm --nodeps --define="_buildshell /bin/bash" --define="SB2_TARGET x86_64-unknown-linux-gnu"
```
### Building Debian packages

1. Download and install `debbuild` and `debbuild-macros`. On Ubuntu and Debian:
```bash
wget https://github.com/debbuild/debbuild/releases/download/22.02.1/debbuild_22.02.1-0ubuntu20.04_all.deb https://github.com/debbuild/debbuild-macros/releases/download/0.0.6/debbuild-macros_0.0.6-0ubuntu20.04_all.deb
sudo apt install ./debbuild*.deb
```

2. Extract the tarball.
3. Build the package:

```bash
rpmbuild -rb xulrunner-qt5-*.jolla.src.rpm --nodeps --define="_buildshell /bin/bash" --define="SB2_TARGET x86_64-unknown-linux-gnu"
```
## Notes

```bash
git remote add mozilla-central https://github.com/mozilla/gecko-dev
git fetch mozilla-central master --depth=1
# Keep this for reference
# For me, it's 600df6aa64
git show --format='%C(auto)%h' -s
git switch -c mozilla-central-master mozilla-central/master
# Replace 600df6aa64 with the commit you got above.
git branch sailfishos 600df6aa64
# Now that we're in mozilla-central, we can use ./mach bootstrap
./mach bootstrap
# Open a new shell
export PATH=$HOME/.mozbuild/git-cinnabar:$PATH
git checkout sailfishos
rpmbuild -ba ../rpm/xulrunner-qt5.spec --nodeps --define="_buildshell /bin/bash" --define="SB2_TARGET x86_64-unknown-linux-gnu" --build-in-place
```

is the standard way to get dependencies. Firefox uses newer dependencies than are available on most systems.

I chose "Firefox Artifact Build", "Install a modern Mercurial via pip (recommended)", create `~/.mozbuild`, install `git-cinnabar`, no telemetry, don't enter a Phabricator API Token, 

## Basic setup process

From the wiki page.

1. Start your widget toolkit's main loop.
2. Load EmbedLite
<pre><code class="code-line language-c++" dir="auto"><div><a href="#LoadEmbedLite">LoadEmbedLite</a>(argc, argv);
</a></code></pre>
3. Get the EmbedLite application object, which allows you to start Gecko in the rendering process and start rendering.
<pre><code class="code-line language-c++" dir="auto"><div><a href="#EmbedLiteApp">EmbedLiteApp</a>* embedapp = <a href="#XRE_GetEmbedLite">XRE_GetEmbedLite</a>();
</a></code></pre>
4. Set up the EmbedLite application listener, which notifies the application about the app lifecycle. `EmbedLiteAppListener[Derived]` represents a subclass of [`EmbedLiteAppListener`](#EmbedLiteAppListener). See the [example subclass](https://github.com/tmeshkova/gecko-dev/blob/embedlite/embedding/embedlite/tests/embedLiteCoreInitTest.cpp#L16) for more information.
```c++
EmbedLiteAppListener[Derived]* listener = new EmbedLiteAppListener[Derived]();
embedapp->SetListener(listener);
```
5. Startup Embedding -- it's a blocking call, and it's best to call this in a main loop event. EmbedLite will not freeze the application here, and will continue native events processing along with Chromium Messages.
```c++
embedapp->Start(EmbedLiteApp::EMBED_THREAD/PROCESS);
```
6. After `EmbedLiteAppListener[Derived]` received `Initialized` notification, new EmbedLiteView can be created with:
```c++
EmbedLiteView* view = embedapp->CreateView();
```
7. Set up the view listener:
```c++
view->SetListener(MyEmbedLiteViewListener);
```

* [Core Initialization Example](https://github.com/tmeshkova/gecko-dev/blob/embedlite/embedding/embedlite/tests/embedLiteCoreInitTest.cpp)
* [View Initialization Example](https://github.com/tmeshkova/gecko-dev/blob/embedlite/embedding/embedlite/tests/embedLiteViewInitTest.cpp)


## APIs

### Headers

* [`"mozilla/embedlite/EmbedInitGlue.h"`](https://github.com/sailfishos/gecko-dev/blob/master/rpm/0019-sailfishos-mozglue-Introduce-EmbedInitGlue-to-the-mo.patch#L140)
* [`"mozilla/embedlite/EmbedLiteApp.h"`](https://github.com/sailfishos/gecko-dev/blob/master/embedding/embedlite/EmbedLiteApp.h)
* [`"mozilla/embedLite/EmbedLiteAPI.h"`](https://github.com/sailfishos/gecko-dev/blob/master/embedding/embedlite/EmbedLiteAPI.h)

<span id="LoadEmbedLite"> </span>

### bool LoadEmbedLite(int argc = 0, char** argv = 0)

Declared in [`"mozilla/embedlite/EmbedInitGlue.h"`](https://github.com/sailfishos/gecko-dev/blob/master/rpm/0019-sailfishos-mozglue-Introduce-EmbedInitGlue-to-the-mo.patch#L154)

```c++
__attribute__((visibility("default")))
bool LoadEmbedLite(int argc = 0, char** argv = 0);
```

Pass the `argc` and `argv` of your program to this function.

As of Gecko 78.15.1, this function dynamically links to XPCOM.

<span id="EmbedLiteApp"> </span>

### class mozilla::embedlite::EmbedLiteApp

Declared in [`"mozilla/embedlite/EmbedLiteApp.h"`](https://github.com/sailfishos/gecko-dev/blob/master/embedding/embedlite/EmbedLiteApp.h#L60)

This is the class of a singleton object, which you can get by using <a href="#XRE_GetEmbedLite">XRE_GetEmbedLite</a>.

### class mozilla::embedlite::EmbedLiteAppListener

Declared in [`"mozilla/embedlite/EmbedLiteApp.h"`](https://github.com/sailfishos/gecko-dev/blob/master/embedding/embedlite/EmbedLiteApp.h#L35)

Notifies the application about the app lifecycle.

<span id="XRE_GetEmbedLite"> </span>

### [mozilla::embedlite::EmbedLiteApp](#EmbedLiteApp)* XRE_GetEmbedLite()

Declared in [`"mozilla/embedLite/EmbedLiteAPI.h"`](https://github.com/sailfishos/gecko-dev/blob/master/embedding/embedlite/EmbedLiteAPI.h#L39)

```c++
extern "C" mozilla::embedlite::EmbedLiteApp* XRE_GetEmbedLite();
```

Returns the singleton instance of <a href="#EmbedLiteApp">EmbedLiteApp</a>.