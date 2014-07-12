#!/usr/bin/env python

################################################################################
# @file
# Commit Script
#
# @version @n 1.0
# @date @n 7/12/2014
#
# @author @n Kwabena W. Agyeman
# @copyright @n (c) 2014 Kwabena W. Agyeman
# @n All rights reserved - Please see the end of the file for the terms of use
#
# @par Update History:
# @n v1.0 - Original release - 7/12/2014
################################################################################

import argparse, os, sys, subprocess

########################## ORDER BY SUBMODULES FIRST ##########################

REPO = [
        "qt-creator-src/src/plugins/omniacreator",
        "qt-creator-src/share/qtcreator/cmake-board-modules/propeller-cmake",
        "qt-creator-src",
        ".."
        ]

if __name__ == "__main__":

    __folder__ = os.path.dirname(os.path.abspath(__file__))

    parser = argparse.ArgumentParser(description =
    "GIT Commit Script")

    parser.add_argument("message", help = "GIT Message")
    parser.add_argument("username", help = "GIT Username")
    parser.add_argument("password", help = "GIT Password")

    args = parser.parse_args()

    # Deploy ##################################################################

    for folder in REPO:
        os.chdir(os.path.join(__folder__, folder))

        # no check_call
        subprocess.call(["git",
                         "add",
                         "-A"])

        # no check_call
        subprocess.call(["git",
                         "commit",
                         "-m",
                         args.message])

        p = subprocess.Popen(["git",
                              "push",
                              "--all"],
                              stdin = subprocess.PIPE)

        #p.communicate(args.username + '\n' + args.password + '\n')

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
