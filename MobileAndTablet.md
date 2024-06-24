# Mobile and Tablet

If you're not ready to deploy to mobile and tablet devices, but still want to test their UIs, you can set environment variables that make Kirigami act like Plasma Mobile or Plasma on a foldable laptop.

To make your app behave like it's on a mobile phone, set [`QT_QUICK_CONTROLS_MOBILE`](https://userbase.kde.org/KDE_System_Administration/Environment_Variables#QT_QUICK_CONTROLS_MOBILE) to `true`.

To make your app behave like it's on a tablet, set [`KDE_KIRIGAMI_TABLET_MODE`] to `true`. Alternatively, if you're on Plasma, you can make your whole desktop show tablet mode by going to System Settings &rarr; Workspace Behavior &rarr; General Behavior &rarr; Touch Mode.

If you are developing on a foldable or detachable laptop, fold or detach the laptop so that only the touchscreen is showing. If you're on Plasma, it should automatically change to tablet mode -- but this doesn't work on some laptop models. If not, just change it in System Settings &rarr; Workspace Behavior &rarr; General Behavior &rarr; Touch Mode.