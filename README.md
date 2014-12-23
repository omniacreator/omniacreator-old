Omnia Creator
=============

A cross platform C/C++ IDE for Makers

[Windows Guide](#windows-guide)  
[Linux Guide](#linux-guide)  
[Mac Guide](#mac-guide)

Windows Guide
-------------

### Install

* Install [Git 1.9.4 for Windows](http://git-scm.com/download/win/) *(or better)*
  1. Please select **Use Git from the Windows Command Prompt** when prompted
  2. Please select **Checkout as-is, commit Unix-style line endings** when prompted
* Install [Windows Credential Store 1.2.0 for Git](http://gitcredentialstore.codeplex.com/) *(or better)*
* Install [Qt 5.3.1 Online Installer for Windows](http://qt-project.org/downloads/) *(or better)*
  1. Please deselect **Qt** when prompted
  2. Please select **Qt -> Qt 5.3 -> MinGW 4.8.2 (32 bit)** when prompted
  3. Please select **Qt -> Qt 5.3 -> Source Components** when prompted
  4. Please select **Qt -> Tools -> MinGW 4.8.2** when prompted
  5. Please select **Qt -> Qt Cloud Services** when prompted
* Install [CMake 3.0.0 for Windows](http://www.cmake.org/cmake/resources/software.html) *(or better)*
  1. Please select **Add CMake to the system PATH for all users** when prompted
* Install [BitRock InstallBuilder 9.5.0 Multiplatform (Professional) for Windows](http://installbuilder.bitrock.com/download-installbuilder-for-qt-step-2.html) *(or better)*
  1. Add **${installbuilder-installdir}\bin** to your path
  2. Add **${installbuilder-installdir}\autoupdate\bin** to your path
* Install [ActivePython 2.7.8 for Windows (x86)](http://www.activestate.com/activepython/downloads/) *(or better)*
  1. Please select **ActivePython -> Entire feature will be installed on local hard drive** when prompted
* Install [ActivePerl 5.16.3 for Windows (x86)](http://www.activestate.com/activeperl/downloads/) *(or better)*
  1. Please select **ActivePython -> Entire feature will be installed on local hard drive** when prompted
* Install [ActiveTcl 8.6.1 for Windows (x86)](http://www.activestate.com/activetcl/downloads/) *(or better)*
* Install [Doxygen 1.8.8 for Windows](http://www.stack.nl/~dimitri/doxygen/download.html) *(or better)*
  1. Add **${doxygen-installdir}\bin** to your path
* Install [Graphviz 2.38.0 for Windows](http://www.graphviz.org/Download_windows.php) *(or better)*
  1. Add **${graphviz-installdir}\bin** to your path
* ***(TRUSTED DEVELOPERS)*** Install [kSign 2.0.0 for Windows](http://codesigning.ksoftware.net) *(or better)*
  1. Add **${ksign-installdir}** to your path
* ***(TRUSTED DEVELOPERS)*** Install [WinSCP 5.5.4 for Windows](http://winscp.net/eng/download.php#download2) *(or better)*
  1. Add **${winscp-installdir}** to your path

*Please replace ${xxx} variables with the appropriate path*

### Configure

1. Clone **https://github.com/omniacreator/omniacreator.git** with Git
  1. `cd ${clonedir}`
  2. `git clone --recursive https://github.com/omniacreator/omniacreator.git`
2. Open **${clonedir}\\ide\qt-creator-src\qtcreator.pro** with QtCreator
  1. Set the debug build directory to **${clonedir}\\ide\qt-creator-build** (click **details** to show)
  2. Set the release build directory to **${clonedir}\\ide\qt-creator-build** (click **details** to show)
3. Using the **Mode Selector** (the left side bar) click **Projects**
4. Select **Desktop Qt x.x.x MinGW ... Build**
  1. Set **Edit build configuration** to **Debug**
    1. Under **Build Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}\\Tools\QtCreator\bin\jom.exe**
      * Leave **Make arguments** blank
    2. Under **Build Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe debug**
      3. Set **Working directory** to **%{buildDir}**
    3. Under **Clean Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}\\Tools\QtCreator\bin\jom.exe**
      * Leave **Make arguments** blank
    4. Under **Clean Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe clean**
      3. Set **Working directory** to **%{buildDir}**
  2. Set **Edit build configuration** to **Release**
    1. Under **Build Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}\\Tools\QtCreator\bin\jom.exe**
      * Leave **Make arguments** blank
    2. Under **Build Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe release**
      3. Set **Working directory** to **%{buildDir}**
    3. Under **Clean Steps** edit the **Make** step by **overriding mingw32-make.exe** with  
    **${qt-installdir}\\Tools\QtCreator\bin\jom.exe**
      * Leave **Make arguments** blank
    4. Under **Clean Steps** click **Add Build Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe clean**
      3. Set **Working directory** to **%{buildDir}**
5. Select **Desktop Qt x.x.x MinGW ... Run**
  1. Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe release -I**
      3. Set **Working directory** to **%{buildDir}**
  2. Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe release -I -B**
      3. Set **Working directory** to **%{buildDir}**
  3. ***(TRUSTED DEVELOPERS)***  
  Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build-Sign**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe release -I -B**  
      **-S ${sign-password}**
      3. Set **Working directory** to **%{buildDir}**
  4. ***(TRUSTED DEVELOPERS)***  
  Under **Deployment** click **Add** and select **Deploy Configuration**
    1. Rename the new **Deployment configuration** to **Install-Build-Sign-Upload**
    2. Click **Add Deploy Step** and select **Custom Process Step**
      1. Set **Command** to **python**
      2. Set **Arguments** to **%{sourceDir}\\..\deploy.py**  
      **${qt-installdir}\\Tools\QtCreator\bin\jom.exe release -I -B**  
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

### Install

* Install [Git 2.0.1 for Mac](http://git-scm.com/download/mac/) *(or better)*
* Install [Qt 5.4.0 Online Installer for Mac](http://qt-project.org/downloads/) *(or better)*
  1. Please deselect **Qt** when prompted
  2. Please select **Qt -> Qt 5.4 -> clang 64-bit** when prompted
  3. Please select **Qt -> Qt 5.4 -> Source Components** when prompted
  4. Please select **Qt -> Qt 5.4 -> Qt WebEngine** when prompted
  5. Please select **Qt -> Tools** when prompted
  6. Please select **Qt -> Qt Cloud Services** when prompted
  7. Please select **Qt -> Qt Extras** when prompted

### Configure

1. Clone **https://github.com/omniacreator/omniacreator.git** with Git
  1. `cd ${clonedir}`
  2. `git clone --recursive https://github.com/omniacreator/omniacreator.git`
