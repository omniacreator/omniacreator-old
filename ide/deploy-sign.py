#!/usr/bin/env python

################################################################################
# @file
# Deploy Sign Script
#
# @version @n 1.0
# @date @n 7/3/2014
#
# @author @n Kwabena W. Agyeman
# @copyright @n (c) 2014 Kwabena W. Agyeman
# @n All rights reserved - Please see the end of the file for the terms of use
#
# @par Update History:
# @n v1.0 - Original release - 7/3/2014
################################################################################

import argparse, os, sys, subprocess

if __name__ == "__main__":

    __folder__ = os.path.dirname(os.path.abspath(__file__))

    parser = argparse.ArgumentParser(description =
    "Deploy Sign Script")

    parser.add_argument("-D", "--description", nargs = '?',
    help = "Description String")

    parser.add_argument("-U", "--url", nargs = '?',
    help = "URL String")

    parser.add_argument("pfx_file", help = "PFX File")
    parser.add_argument("pfx_password", help = "PFX Password")
    parser.add_argument("file_to_sign", help = "File to Sign")

    args = parser.parse_args()

    pfx_file = os.path.abspath(args.pfx_file)
    file_to_sign = os.path.abspath(args.file_to_sign)

    if not os.path.exists(pfx_file):
        sys.exit("PFX File \"%s\" does not exist!" % pfx_file)

    if not os.path.exists(file_to_sign):
        sys.exit("File to Sign \"%s\" does not exist!" % file_to_sign)

    # Deploy ##################################################################

    print "Signing %s..." % os.path.basename(file_to_sign)
    sys.stdout.flush()

    if sys.platform.startswith("win"): # windows

        command = []

        command.append("kSignCMD.exe")

        if(args.description):
            command.extend(["/d", args.description])

        if(args.url):
            command.extend(["/du", args.url])

        command.extend(["/f", pfx_file])
        command.extend(["/p", args.pfx_password])
        command.append(file_to_sign)

        if subprocess.call(command):

            print "Trying again..."
            print "Signing %s..." % os.path.basename(file_to_sign)
            sys.stdout.flush()

            if subprocess.call(command):

                print "Signing Failed!"
                sys.stdout.flush()

    # elif sys.platform == "darwin": # mac
    # else: # linux

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
