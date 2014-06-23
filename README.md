Omnia Creator
=============

A cross platform C/C++ IDE for Makers

[Windows Guide](#windows-guide)  
[Linux Guide](#linux-guide)  
[Mac Guide](#mac-guide)

Windows Guide
-------------

### Install

* Install [Git 1.9.4 for Windows](http://git-scm.com/download/win) (or better)
 * Please select **Use Git from the Windows Command Prompt** when prompted
 * Please select **Checkout as-is, commit Unix-style line endings** when prompted
* Install [GitHub for Windows 2.0](https://windows.github.com) (or better)
* Install [Qt 5.3.0 for Windows 32-bit (MinGW 4.8.2, OpenGL)](http://qt-project.org/downloads) (or better)
 * Add *${installdir}/Tools/QtCreator/bin/jom.exe* to your path
* Install [BitRock InstallBuilder 9 Multiplatform (Professional) for Windows](http://installbuilder.bitrock.com/download-installbuilder-for-qt-step-2.html) (or better)
 * Add *${installdir}/bin/builder-cli.exe* to your path
* Install [ActivePython 2.7.6 for Windows (x86)](http://www.activestate.com/activepython/downloads) (or better)
* Install [ActivePerl 5.16.3 for Windows (x86)](http://www.activestate.com/activeperl/downloads) (or better)
* **(Optional)** Install [ActiveTcl 8.6.1 for Windows (x86)](http://www.activestate.com/activetcl/downloads) (or better)
* **(Optional)** Install [GIMP 2.8.10 for Windows](http://www.gimp.org/downloads/) (or better)

### Configure

1. Clone [Omnia Creator](github-windows://openRepo/https://github.com/omniacreator/omniacreator) with GitHub for Windows
2. Open *${clonedir}/ide/qt-creator-src/qtcreator.pro* with QtCreator
 1. Set the debug output directory to *${clonedir}/ide/qt-creator-build*
 2. Set the release output directory to *${clonedir}/ide/qt-creator-build*
4. Using the Mode Selector (the left side bar) open *projects->build steps*
 1. ...

Linux Guide
-----------

Omnia Creator has not been ported to Linux yet.

Mac Guide
---------

Omnia Creator has not been ported to Mac yet.
