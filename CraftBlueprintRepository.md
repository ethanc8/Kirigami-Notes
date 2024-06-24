# Craft blueprint repositories

## Creating Craft blueprint repositories

First, create a Craft blueprint repository.

```
mkdir -p ~/Projects/CraftBlueprints/craft-blueprints-${USER}
```

Add an `info.ini` file:

```ini
[General]
displayName = <Your name>
description = Software by <Your name>
webpage = <Your website>
```

Add a `craft/craft-blueprints-${USER}/craft-blueprints-${USER}.py` file:

```python
import info


class subinfo(info.infoclass):
    def setTargets(self):
        for ver in ["master"]:
            # Change this depending on where your Craft repository is located
            # You can also use an online git repository
            # This example assumes you're using this in a KDE docker container.
            self.svnTargets[ver] = f"[git]/home/user/usersrc/craft-blueprints-<YOUR REPOSITORY NAME>|{ver}|"
        self.defaultTarget = "master"

    def setDependencies(self):
        self.buildDependencies["craft/craft-core"] = "default"


from Package.BlueprintRepositoryPackageBase import *


class Package(BlueprintRepositoryPackageBase):
    def __init__(self):
        BlueprintRepositoryPackageBase.__init__(self)
```

Initialize the repository:

```bash
git init
git add *
git commit -a
```

Now, you can add this repository with:

```bash
# In the docker container
# If not, replace `/home/user/usersource` with `$HOME/Projects/CraftBlueprints`
# Replace <YOUR REPOSITORY NAME> with the name of your repository
craft --add-blueprint-repository /home/user/usersource/craft-blueprints-<YOUR REPOSITORY NAME>
```

## Adding blueprints to the repository

Create folders with descriptive names for the types of apps that will be in your repository. It should be unique across repositories. For this example, we'll go with `${USER}-apps` and `${USER}-libs`.

For each app or library you want to package, create a blueprint. 

* [Explanation of what goes into a blueprint](https://community.kde.org/Craft/Blueprints)

Examples:

* [Kirigami Gallery](https://invent.kde.org/packaging/craft-blueprints-kde/-/blob/master/kde/applications/kirigami-gallery/kirigami-gallery.py)
* [KDE Itinerary](https://invent.kde.org/packaging/craft-blueprints-kde/-/blob/master/kde/applications/itinerary/itinerary.py)

## Example Craft blueprint repositories

* [Craft's default blueprint repository](https://invent.kde.org/packaging/craft/-/tree/master/blueprints)
* [Preinstalled - KDE repository](https://invent.kde.org/packaging/craft-blueprints-kde/-/tree/master/)
* [BearKidsTeam repository (multimedia)](https://github.com/BearKidsTeam/craft-shmooprint-bkt)
* [Owncloud](https://github.com/owncloud/craft-blueprints-owncloud)
* [Cuperino - QPrompt and Clipboard Inspector](https://github.com/Cuperino/craft-blueprints-cuperino)
* [Quassel](https://github.com/quassel/craft-blueprints-quassel)