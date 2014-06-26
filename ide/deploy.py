#!/usr/bin/env python

################################################################################
# @file
# Deploy Script
#
# @version @n 1.0
# @date @n 6/24/2014
#
# @author @n Kwabena W. Agyeman
# @copyright @n (c) 2014 Kwabena W. Agyeman
# @n All rights reserved - Please see the end of the file for the terms of use
#
# @par Update History:
# @n v1.0 - Original release - 6/24/2014
################################################################################

import argparse, os, sys, shutil, subprocess, glob, fnmatch, ftplib, urllib

INSTALL_PREFIX = "../installer"
INSTALL_FOLDER = "install"
INSTALLER_FOLDER = "installer"
BUILD_FOLDER = ""

INSTALLER_CONFIGURATION = "../installer/installer.xml"
INSTALLER_LICENSE = "../installer/private-license.xml"

SIGNCMD_PATH = "../tools/ksign/kSignCMD.exe"
CERTIFICATE_PATH = "../installer/private-signature.pfx"

FTP_SITE = "ftp.omniacreator.com"
FTP_USER = "deploy.py"
FTP_SIZE = 65536

class UploadInfo:

    file_name = ""
    file_size = 0

    bytes_written = 0
    upload_progress = -1

    def __init__(self, name):

        self.file_name = name
        self.file_size = os.path.getsize(name)

    def callback(self, unused):

        self.bytes_written += FTP_SIZE
        progress = ((self.bytes_written * 100) / self.file_size)

        if self.upload_progress != progress:
            self.upload_progress = progress

            print "Uploading \"%s\" [%03d%%]..." % (self.file_name, progress)
            sys.stdout.flush()

if __name__ == "__main__":

    __folder__ = os.path.dirname(os.path.abspath(__file__))

    parser = argparse.ArgumentParser(description =
    "Deploy Script")

    parser.add_argument("make_path", help = "jom path")
    parser.add_argument("make_mode", help = "debug, release, or clean")

    parser.add_argument("install_folder", nargs = '?',
    default = os.path.abspath(os.path.join(__folder__, INSTALL_PREFIX)))

    parser.add_argument("build_folder", nargs = '?',
    default = os.getcwd())

    parser.add_argument("-I", "--install_files", action = "store_true")
    parser.add_argument("-B", "--build_installer", action = "store_true")
    parser.add_argument("-S", "--sign", nargs = '?', help = "Password")
    parser.add_argument("-U", "--upload", nargs = '?', help = "Password")

    args = parser.parse_args()

    install_folder = os.path.abspath(os.path.join(args.install_folder,
    INSTALL_FOLDER))

    installer_folder = os.path.abspath(os.path.join(args.install_folder,
    INSTALLER_FOLDER))

    build_folder = os.path.abspath(os.path.join(args.build_folder,
    BUILD_FOLDER))

    installer_configuration = os.path.abspath(os.path.join(__folder__,
    INSTALLER_CONFIGURATION))

    installer_license = os.path.abspath(os.path.join(__folder__,
    INSTALLER_LICENSE))

    signcmd = os.path.abspath(os.path.join(__folder__,
    SIGNCMD_PATH))

    certificate = os.path.abspath(os.path.join(__folder__,
    CERTIFICATE_PATH))

    if not os.path.exists(args.make_path):
        sys.exit("JOM Binary \"%s\" does not exist!" % args.make_path)

    if not os.path.exists(build_folder):
        sys.exit("Build Folder \"%s\" does not exist!" % build_folder)

    if args.make_mode == "release" and args.install_files:

        if not os.path.exists(install_folder):
            os.makedirs(install_folder)

        if not os.path.exists(installer_folder):
            os.makedirs(installer_folder)

    if args.build_installer:

        if not os.path.exists(installer_configuration):
            sys.exit("Installer Configuration File \"%s\" "
                     "does not exist!" % installer_configuration)

        if not os.path.exists(installer_license):
            sys.exit("Installer License File \"%s\" "
                     "does not exist!" % installer_license)

    if args.sign:

        if sys.platform.startswith("win") and not os.path.exists(signcmd):
            sys.exit("Sign CMD \"%s\" does not exist!" % signcmd)

        if sys.platform.startswith("win") and not os.path.exists(certificate):
            sys.exit("PFX File \"%s\" does not exist!" % certificate)

    # Deploy ##################################################################

    if args.make_mode == "debug" or args.make_mode == "release":

        print "Deploying CMake Files to build dir..."
        sys.stdout.flush()

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/share/qtcreator/"
        "cmake-board-modules/deploy_cmake_board_modules.py"),
        build_folder])

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/share/qtcreator/"
        "cmake-board-types/deploy_cmake_board_types.py"),
        build_folder])

        print "Deploying FFTW to build dir..."
        sys.stdout.flush()

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/src/plugins/"
        "omniacreator/deploy_fftw.py"),
        build_folder])

        if args.install_files:

            print "Deploying Omnia Creator Library to build dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy_omniacreatorlibrary.py"),
            build_folder])

    if args.make_mode == "release":

        if args.install_files:

            print "Deploying CMake Files to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/share/qtcreator/"
            "cmake-board-modules/deploy_cmake_board_modules.py"),
            install_folder])

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/share/qtcreator/"
            "cmake-board-types/deploy_cmake_board_types.py"),
            install_folder])

            print "Deploying FFTW to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy_fftw.py"),
            install_folder])

            print "Deploying Omnia Creator Library to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy_omniacreatorlibrary.py"),
            install_folder])

            if sys.platform != "darwin":

                print "Executing Make Install..."
                sys.stdout.flush()

                subprocess.call([args.make_path, "-f",
                os.path.join(build_folder, "Makefile"),
                "install", "INSTALL_ROOT=\""+install_folder+'\"'])

            print "Executing Make Deploy Qt..."
            sys.stdout.flush()

            subprocess.call([args.make_path, "-f",
            os.path.join(build_folder, "Makefile"),
            "deployqt", "INSTALL_ROOT=\""+install_folder+'\"'])

            print "Executing Make Deploy Artifacts..."
            sys.stdout.flush()

            subprocess.call([args.make_path, "-f",
            os.path.join(build_folder, "Makefile"),
            "deployartifacts", "INSTALL_ROOT=\""+install_folder+'\"'])

            print "Executing Make Cleanup..."
            sys.stdout.flush()

            # PHONY COMMAND subprocess.call([args.make_path, "-f",
            # PHONY COMMAND os.path.join(build_folder, "Makefile"),
            # PHONY COMMAND "cleanup", "INSTALL_ROOT=\""+install_folder+'\"'])

            # Cleanup Begin ###################################################

            for bp in os.listdir(os.path.join(install_folder, "bin/plugins")):
                shutil.rmtree(os.path.join(install_folder, "bin", bp), True)
                shutil.move(os.path.join(install_folder, "bin/plugins", bp),
                            os.path.join(install_folder, "bin", bp))

            shutil.rmtree(os.path.join(install_folder,
            "bin/imports"), True)

            shutil.rmtree(os.path.join(install_folder,
            "bin/plugins"), True)

            shutil.rmtree(os.path.join(install_folder,
            "bin/qml"), True)

            shutil.rmtree(os.path.join(install_folder,
            "lib/qtcreatorcdbext64"), True)

            shutil.rmtree(os.path.join(install_folder,
            "lib/vcredist_msvc2010"), True)

            try:
                os.remove(os.path.join(install_folder,
                "bin/win64interrupt.exe"))
            except OSError:
                pass

            try:
                os.remove(os.path.join(install_folder,
                "bin/changelog.jom.txt"))
            except OSError:
                pass

            try:
                os.remove(os.path.join(install_folder,
                "bin/ibjom.cmd"))
            except OSError:
                pass

            try:
                os.remove(os.path.join(install_folder,
                "bin/profile.xml"))
            except OSError:
                pass

            try:
                os.remove(os.path.join(install_folder,
                "bin/qt.conf"))
            except OSError:
                pass

            unused = glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/assistant_*.qm"))

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/designer_*.qm")))

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/linguist_*.qm")))

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/qmlviewer_*.qm")))

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/qt_help_*.qm")))

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/qtconfig_*.qm")))

            for file in unused:
                os.remove(file)

            # Cleanup End #####################################################

            if sys.platform.startswith("win") and args.sign:

                print "Signing Executables..."
                sys.stdout.flush()

                binaries = []

                for dirpath, xxx, filenames in os.walk(install_folder):

                    for filename in fnmatch.filter(filenames, "*.dll"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.exe"):
                        binaries.append(os.path.join(dirpath, filename))

                for binary in binaries:

                    result = 1

                    while result != 0:

                        print "Signing %s..." % os.path.basename(binary)
                        sys.stdout.flush()

                        result = subprocess.call([signcmd,
                        "/d", "Omnia Creator",
                        "/du", "www.omniacreator.org",
                        "/f", certificate,
                        "/p", args.sign,
                        binary])

            if args.build_installer:

                print "Building Installer..."
                sys.stdout.flush()

                subprocess.call(["builder-cli",
                "build", installer_configuration,
                "--license", installer_license,
                "--verbose", "--downloadable-components"])

                if sys.platform.startswith("win") and args.sign:

                    print "Signing Executables..."
                    sys.stdout.flush()

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.dll"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.exe"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:

                        result = 1

                        while result != 0:

                            print "Signing %s..." % os.path.basename(binary)
                            sys.stdout.flush()

                            result = subprocess.call([signcmd,
                            "/d", "Omnia Creator",
                            "/du", "www.omniacreator.org",
                            "/f", certificate,
                            "/p", args.sign,
                            binary])

                if args.upload:

                    print "Logging onto FTP Server..." + '\n'
                    sys.stdout.flush()

                    server = ftplib.FTP(FTP_SITE, FTP_USER, args.upload)

                    print server.getwelcome() + '\n'

                    print "Uploading to FTP Server..."
                    sys.stdout.flush()

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.exe"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.run"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.app"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:
                        if os.path.getsize(binary):
                            info = UploadInfo(binary)
                            server.storbinary("STOR "+os.path.basename(binary),
                            open(binary, "rb"), FTP_SIZE, info.callback)

                    server.cwd("components")

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.pak"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:
                        if os.path.getsize(binary):
                            info = UploadInfo(binary)
                            server.storbinary("STOR "+os.path.basename(binary),
                            open(binary, "rb"), FTP_SIZE, info.callback)

                    server.quit()

    elif args.make_mode == "clean":

        if os.path.exists(install_folder):

            print "Cleaning Install Folder contents..."
            sys.stdout.flush()

            for file_object in os.listdir(install_folder):
                file_object_path = os.path.join(install_folder, file_object)

                if os.path.isfile(file_object_path):
                    os.remove(file_object_path)
                else:
                    shutil.rmtree(file_object_path, True)

        if os.path.exists(installer_folder):

            print "Cleaning Installer Folder contents..."
            sys.stdout.flush()

            for file_object in os.listdir(installer_folder):
                file_object_path = os.path.join(installer_folder, file_object)

                if os.path.isfile(file_object_path):
                    os.remove(file_object_path)
                else:
                    shutil.rmtree(file_object_path, True)

        print "Cleaning Build Folder contents..."
        sys.stdout.flush()

        for file_object in os.listdir(build_folder):
            file_object_path = os.path.join(build_folder, file_object)

            if os.path.isfile(file_object_path):
                os.remove(file_object_path)
            else:
                shutil.rmtree(file_object_path, True)

    else:

        sys.exit("Make Mode \"%s\" does not exist!" % args.make_mode)

################################################################################
# @file
# @par MIT License - TERMS OF USE:
# @n Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# @n
# @n The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# @n
# @n THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
################################################################################
