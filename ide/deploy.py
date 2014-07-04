#!/usr/bin/env python

################################################################################
# @file
# Deploy Script
#
# @version @n 1.0
# @date @n 7/4/2014
#
# @author @n Kwabena W. Agyeman
# @copyright @n (c) 2014 Kwabena W. Agyeman
# @n All rights reserved - Please see the end of the file for the terms of use
#
# @par Update History:
# @n v1.0 - Original release - 7/4/2014
################################################################################

import argparse, os, sys, re, shutil, subprocess, glob, fnmatch

INSTALL_PREFIX = "../installer"
INSTALL_FOLDER = "install"
INSTALLER_FOLDER = "installer"
BUILD_FOLDER = ""

PRO_FILE = "../ide/qt-creator-src/src/plugins/omniacreator/omniacreator.pro"

LIBRARY_DIRECTORY = "share/qtcreator/libraries"

INSTALLER_PROJECT = "../installer/installer.xml"
INSTALLER_LICENSE = "../installer/private-license.xml"

DIGITAL_CERTIFICATE = "../installer/private-signature.pfx"

SFTP_USERNAME = "omni2127468419"

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

    pro_file = os.path.abspath(os.path.join(__folder__,
    PRO_FILE))

    library_directory = os.path.abspath(os.path.join(installer_folder,
    LIBRARY_DIRECTORY))

    installer_project = os.path.abspath(os.path.join(__folder__,
    INSTALLER_PROJECT))

    installer_license = os.path.abspath(os.path.join(__folder__,
    INSTALLER_LICENSE))

    digital_certificate = os.path.abspath(os.path.join(__folder__,
    DIGITAL_CERTIFICATE))

    if not os.path.exists(args.make_path):
        sys.exit("JOM Binary \"%s\" "
                 "does not exist!" % args.make_path)

    if args.make_mode not in ["debug", "release", "clean"]:
        sys.exit("Make Mode \"%s\" "
                 "does not exist!" % args.make_mode)

    if not os.path.exists(build_folder):
        sys.exit("Build Folder \"%s\" "
                 "does not exist!" % build_folder)

    if not os.path.exists(pro_file):
        sys.exit("PRO File \"%s\" "
                 "does not exist!" % pro_file)

    if args.build_installer:

        if not os.path.exists(installer_project):
            sys.exit("Installer Project \"%s\" "
                     "does not exist!" % installer_project)

        if not os.path.exists(installer_license):
            sys.exit("Installer License \"%s\" "
                     "does not exist!" % installer_license)

    if args.sign:

        if not os.path.exists(digital_certificate):
            sys.exit("Digital Certificate \"%s\" "
                     "does not exist!" % digital_certificate)

    # Import Pro Settings Begin ###############################################

    dict = {}
    regex = re.compile(r"(.+?)\s+=\s+\"(.+?)\"")

    with open(pro_file) as file:
        for line in file:
            match = regex.search(line)

            if match:
                dict[match.group(1)] = match.group(2)

    pro_full_name = dict["PROJECT_FULL_NAME"]
    pro_full_name_wo_spaces = re.sub(r"[ _]", "", pro_full_name)
    pro_short_name = pro_full_name_wo_spaces.lower()
    pro_version = dict["PROJECT_VERSION"]
    pro_vendor = pro_full_name
    pro_copyright = dict["PROJECT_COPYRIGHT"]
    pro_category = dict["PROJECT_CATEGORY"]
    pro_description = dict["PROJECT_DESCRIPTION"]
    pro_url = "www." + pro_short_name + ".com"
    pro_email = pro_short_name + "@" + pro_short_name + ".com"
    pro_domain = pro_short_name + ".com"

    # Import Pro Settings End #################################################

    if args.make_mode != "clean":

        if args.install_files:

            shutil.rmtree(install_folder, True)
            os.makedirs(install_folder)

        if args.build_installer:

            shutil.rmtree(installer_folder, True)
            os.makedirs(installer_folder)

    # Deploy ##################################################################

    if args.make_mode == "clean":

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

        print "Deploying CMake Files to build dir..."
        sys.stdout.flush()

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/share/qtcreator/"
        "cmake-board-modules/deploy-cmake-board-modules.py"),
        build_folder])

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/share/qtcreator/"
        "cmake-board-types/deploy-cmake-board-types.py"),
        build_folder])

        print "Deploying FFTW to build dir..."
        sys.stdout.flush()

        subprocess.call(["python", os.path.join(__folder__,
        "qt-creator-src/src/plugins/"
        "omniacreator/deploy-fftw3.py"),
        build_folder])

        if args.install_files:

            print "Deploying The Interface Library to build dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy-interfacelibrary.py"),
            build_folder])

            print "Deploying CMake Files to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/share/qtcreator/"
            "cmake-board-modules/deploy-cmake-board-modules.py"),
            install_folder])

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/share/qtcreator/"
            "cmake-board-types/deploy-cmake-board-types.py"),
            install_folder])

            print "Deploying FFTW to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy-fftw3.py"),
            install_folder])

            print "Deploying The Interface Library to install dir..."
            sys.stdout.flush()

            subprocess.call(["python", os.path.join(__folder__,
            "qt-creator-src/src/plugins/"
            "omniacreator/deploy-interfacelibrary.py"),
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

            unused = []

            unused.extend(glob.glob(os.path.join(install_folder,
            "share/qtcreator/translations/assistant_*.qm")))

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

            if args.sign:

                print "Signing Executables..."
                sys.stdout.flush()

                binaries = []

                for dirpath, xxx, filenames in os.walk(install_folder):

                    for filename in fnmatch.filter(filenames, "*.dll"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.exe"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.dylib"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.app"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.so"):
                        binaries.append(os.path.join(dirpath, filename))

                    for filename in fnmatch.filter(filenames, "*.run"):
                        binaries.append(os.path.join(dirpath, filename))

                for binary in binaries:

                    subprocess.call(["python",
                    os.path.join(__folder__, "deploy-sign.py"),
                    "-D", pro_description, "-U", pro_url,
                    digital_certificate, args.sign, binary])

            if args.build_installer:

                print "Building Installer..."
                sys.stdout.flush()

                subprocess.call(" ".join(["builder-cli",
                "build", '\"' + installer_project + '\"',
                "--verbose",
                "--license", '\"' + installer_license + '\"',
                "--setvars",
                "project.shortName=" + '\"' + pro_short_name + '\"',
                "project.fullName=" + '\"' + pro_full_name + '\"',
                "project.version=" '\"' + pro_version + '\"',
                "--downloadable-components"]))

                if args.sign:

                    print "Signing Executables..."
                    sys.stdout.flush()

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.dll"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.exe"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.dylib"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.app"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.so"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.run"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:

                        subprocess.call(["python",
                        os.path.join(__folder__, "deploy-sign.py"),
                        "-D", pro_description, "-U", pro_url,
                        digital_certificate, args.sign, binary])

                if args.upload:

                    print "Uploading Installer..."
                    sys.stdout.flush()

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.exe"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.app"):
                            binaries.append(os.path.join(dirpath, filename))

                        for filename in fnmatch.filter(filenames, "*.run"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:

                        subprocess.call(["python",
                        os.path.join(__folder__, "deploy-upload.py"),
                        SFTP_USERNAME, args.upload, pro_domain,
                        "wp-download/installer", binary])

                    print "Uploading Components..."
                    sys.stdout.flush()

                    binaries = []

                    for dirpath, xxx, filenames in os.walk(installer_folder):

                        for filename in fnmatch.filter(filenames, "*.pak"):
                            binaries.append(os.path.join(dirpath, filename))

                    for binary in binaries:

                        subprocess.call(["python",
                        os.path.join(__folder__, "deploy-upload.py"),
                        SFTP_USERNAME, args.upload, pro_domain,
                        "wp-download/installer/components", binary])

                    print "Uploading Libraries..."
                    sys.stdout.flush()

                    subprocess.call(["python",
                    os.path.join(__folder__, "deploy-upload.py"),
                    SFTP_USERNAME, args.upload, pro_domain,
                    "wp-download", library_directory])

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
