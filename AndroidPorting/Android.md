# Android

## Craft

### Setup
```bash
mkdir -p ~/Projects/KDEAndroid/craft ~/Projects/KDEAndroid/keys
sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk craft-bootstrap
```

This will ask you for which architecture you want to build and then set up Craft accordingly.

### Tips

You can create an alias for `craft`:

```bash
alias android-craft="sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk craft"
alias android-craft-cs="sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk cs"
alias android-craft-cb="sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk cb"
alias android-sdk-bash="sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk bash"
```

### Building KDE apps

```bash
android-sdk-bash
# In the docker image
craft ktrip
craft --package ktrip
```

Craft will tell you where the file is located. If you used the recommended commands above, you can replace `/home/user/CraftRoot` with `~/Projects/KDEAndroid/craft` to open it in your local filesystem.

### Signing the APK

First, you need a key or a keystore.

```bash
# In the docker image
cd ~/keys
keytool -genkey -v -keystore release_keystore.keystore -alias release_keystore -keyalg RSA -keysize 2048 -validity 10000
```

Save your keystore password!

Alternatively, you can use the test key.
* [`testkey.x5089.pem`](https://github.com/aosp-mirror/platform_build/raw/master/target/product/security/testkey.x509.pem)
* [`testkey.pk8`](https://github.com/aosp-mirror/platform_build/raw/master/target/product/security/testkey.pk8)

Download the keys to `~/Projects/KDEAndroid/keys`. They'll appear in the Docker image in `~/keys`.

Next, use `apksigner` to sign your apk: (Replace `<APK file>` with the path to the APK).

```bash
# In the docker image
# Using the keystore you generated above.
/opt/android-sdk/build-tools/*/apksigner sign --ks $HOME/keys/release_keystore.keystore --in <APK file> --out <Output APK file>
# Using the test keys
/opt/android-sdk/build-tools/*/apksigner sign --key $HOME/keys/testkey.pk8 --cert testkey.x5089.pem --in <APK file> --out <Output APK file>
```

If you want it signed by KDE's keys, you'll need to get it integrated into KDE's "Binary Factory" build system.

### Adding your own app

If your app is not a KDE app, or you want to experiment with Craft before making your app officialy available for Android via Craft, then you should follow this section.

First, [create a craft blueprint repository](CraftBlueprintRepository.md).

Next, here's an example blueprint for my app Koresight in `ethan-apps/koresight/koresight.py`.
```python
# SPDX-License-Identifier: BSD-2-Clause
# SPDX-FileCopyrightText: 2021 Nicolas Fella <nicolas.fella@gmx.de>

import info

class subinfo(info.infoclass):
    def setTargets(self):
        # self.versionInfo.setDefaultValues()
        self.displayName = "Koresight"
        self.description = "Simple to-do list"

        for ver in ["master"]:
            # Change this depending on where your Craft repository is located
            # You can also use an online GitHub repository
            # This example assumes you're using this in a KDE docker container.
            self.svnTargets[ver] = f"[git]/home/user/usersrc/koresight|{ver}|"
        self.defaultTarget = "master"

    def setDependencies(self):
        self.buildDependencies["virtual/base"] = None
        self.buildDependencies["kde/frameworks/extra-cmake-modules"] = None
        self.runtimeDependencies["libs/qt5/qtbase"] = None
        self.runtimeDependencies["libs/qt5/qtdeclarative"] = None
        self.runtimeDependencies["libs/qt5/qtquickcontrols2"] = None
        self.runtimeDependencies["kde/frameworks/tier1/kirigami"] = None

        if CraftCore.compiler.isAndroid:
            self.runtimeDependencies["libs/qt5/qtandroidextras"] = None

from Package.CMakePackageBase import *

class Package(CMakePackageBase):
    def __init__(self):
        CMakePackageBase.__init__(self)
        # Avoid building tests
        CMakePackageBase.buildTests = False
```

Remember to commit these changes to your blueprint repository!

Now, we can start the docker container, mounting your app's code at `~/usersource/`*Your app name*, and your blueprint repository at `~/usersource/`*Your repository name*:

```bash
sudo docker run -ti --rm \
    -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot \
    -v $HOME/Projects/KDEAndroid/keys:/home/user/keys \
    -v $HOME/Projects/CraftBlueprints/craft-blueprints-${USER}:/home/user/usersource/craft-blueprints-${USER} \
    -v <Path to your app>:/home/user/usersource/koresight \
    kdeorg/android-sdk bash
```

```bash
craft --add-blueprint-repository /home/user/usersource/craft-blueprints-<Repository name>
craft <Name of your app>
craft --package <Name of your app>
cd /home/user/usersource/<Name of your app>
mkdir build-output; cd build-output
/opt/android-sdk/build-tools/*/apksigner sign --ks $HOME/keys/release_keystore.keystore --in <APK file> --out ./latest.apk
exit
```

You can add `--buildtype MinSizeRel` to your `craft` invocations to reduce the size of the resulting binary.

## Other ways

* [Krita](https://docs.krita.org/en/untranslatable_pages/building_krita.html#building-on-android)
* KTrip uses the docker `android-sdk`, just like this guide.
* KDE Itinerary uses the docker `android-sdk`, and can also be built separately.
    * [Link](https://invent.kde.org/pim/itinerary#building-for-android-using-docker)
* [GCompris](https://gcompris.net/wiki/Qt_Quick_development_process#Compiling_GCompris_for_Android)
* [Kirigami Gallery](https://invent.kde.org/sdk/kirigami-gallery#build-on-android)



