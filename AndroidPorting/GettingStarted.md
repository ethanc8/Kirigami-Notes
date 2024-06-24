# Getting started

This section will focus on setting up the KDE Android SDK, and building a KDE app using the SDK and the Craft package manager.

## Folder structure

We'll be keeping some of our stuff in different folders on our local disk. This way, we won't modify the Docker image, but we won't have to re-run the lengthy parts.

| Docker folder | Host folder                 | Purpose                            |
| ------------- | --------------------------- | ---------------------------------- |
| ~/CraftRoot   | ~/Projects/KDEAndroid/craft | Root for the Craft package manager |
| ~/keys        | ~/Projects/KDEAndroid/keys  | Keystore to sign Android APKs      |
|               |                             |                                    |

## Installing the SDK

Make sure you have Docker installed. Then run:

```bash
mkdir -p ~/Projects/KDEAndroid/craft ~/Projects/KDEAndroid/keys
sudo docker run -ti --rm -v $HOME/Projects/KDEAndroid/craft:/home/user/CraftRoot -v $HOME/Projects/KDEAndroid/keys:/home/user/keys kdeorg/android-sdk craft-bootstrap
