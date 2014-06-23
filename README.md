Omnia Creator
=============

A cross platform C/C++ IDE for Makers

[Windows Guide](#windows-guide)  
[Linux Guide](#linux-guide)  
[Mac Guide](#mac-guide)

Windows Guide
-------------

### Install

* Install [Git 1.9.4 for Windows](http://git-scm.com/download/win) *(or better)*
  * Please select **Use Git from the Windows Command Prompt** when prompted
  * Please select **Checkout as-is, commit Unix-style line endings** when prompted
* Install [GitHub for Windows 2.0.6](https://windows.github.com) *(or better)*
* Install [Qt 5.3.0 for Windows 32-bit (MinGW 4.8.2, OpenGL)](http://qt-project.org/downloads) *(or better)*
  * Add **${qt-installdir}/Tools/QtCreator/bin/jom.exe** to your path
* Install [BitRock InstallBuilder 9.0.1 Multiplatform (Professional) for Windows](http://installbuilder.bitrock.com/download-installbuilder-for-qt-step-2.html) *(or better)*
  * Add **${bitrock-installdir}/bin/builder-cli.exe** to your path
* Install [ActivePython 2.7.6 for Windows (x86)](http://www.activestate.com/activepython/downloads) *(or better)*
* Install [ActivePerl 5.16.3 for Windows (x86)](http://www.activestate.com/activeperl/downloads) *(or better)*
* **(Optional)** Install [ActiveTcl 8.6.1 for Windows (x86)](http://www.activestate.com/activetcl/downloads) *(or better)*
* **(Optional)** Install [GIMP 2.8.10 for Windows](http://www.gimp.org/downloads/) *(or better)*

*Please replace ${xxx} variables with the appropriate path*

### Configure

1. Clone **[Omnia Creator](github-windows://openRepo/https://github.com/omniacreator/omniacreator)** with GitHub for Windows
2. Open **${clonedir}/ide/qt-creator-src/qtcreator.pro** with QtCreator
  1. Set the debug build directory to **${clonedir}/ide/qt-creator-build**
  2. Set the release build directory to **${clonedir}/ide/qt-creator-build**
3. Using the **Mode Selector** (the left side bar) click **Projects**
4. Select **Desktop Qt x.x.x MinGW ... Build**
  1. Set **Edit build configuration** to **Debug**
    1. Under **Build Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}/Tools/QtCreator/bin/jom.exe**
      * Leave **Make arguments** blank
    2. Under **Build Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe debug**
      3. Set **Working directory** to **%{buildDir}**
    3. Under **Clean Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}/Tools/QtCreator/bin/jom.exe**
      * Leave **Make arguments** blank
    4. Under **Clean Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe clean**
      3. Set **Working directory** to **%{buildDir}**
  2. Set **Edit build configuration** to **Release**
    1. Under **Build Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}/Tools/QtCreator/bin/jom.exe**
      * Leave **Make arguments** blank
    2. Under **Build Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe release**
      3. Set **Working directory** to **%{buildDir}**
    3. Under **Clean Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}/Tools/QtCreator/bin/jom.exe**
      * Leave **Make arguments** blank
    4. Under **Clean Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe clean**
      3. Set **Working directory** to **%{buildDir}**
5. Select **Desktop Qt x.x.x MinGW ... Run**
  1. Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe release -I**
      3. Set **Working directory** to **%{buildDir}**
  2. Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe release -I -B**
      3. Set **Working directory** to **%{buildDir}**
  3. ***(FOR TRUSTED DEVELOPERS ONLY)***  
  Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build-Sign**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe release -I -B**  
      **-S ${sign-password}**
      3. Set **Working directory** to **%{buildDir}**
  4. ***(FOR TRUSTED DEVELOPERS ONLY)***  
  Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build-Sign-Upload**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}/../deploy.py**  
      **${qt-installdir}/Tools/QtCreator/bin/jom.exe release -I -B**  
      **-S ${sign-password} -U ${upload-password}**
      3. Set **Working directory** to **%{buildDir}**
  5. Under **Deployment** set **Method** to **Deploy locally**
  6. Under **Run** set **Run configuration** to **app**
6. Using the **Mode Selector** (the left side bar) click **Run**

*Please replace ${xxx} variables with the appropriate path*

Linux Guide
-----------

Omnia Creator has not been ported to Linux yet.

Mac Guide
---------

Omnia Creator has not been ported to Mac yet.
