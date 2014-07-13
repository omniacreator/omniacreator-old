#!/usr/bin/env python

################################################################################
# @file
# Deploy Upload Script
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

import argparse, os, sys, subprocess, urllib

if __name__ == "__main__":

    __folder__ = os.path.dirname(os.path.abspath(__file__))

    parser = argparse.ArgumentParser(description =
    "Deploy Upload Script")

    parser.add_argument("sftp_username", help = "SFTP Username")
    parser.add_argument("sftp_password", help = "SFTP Password")
    parser.add_argument("sftp_domainname", help = "SFTP Domainname")
    parser.add_argument("sftp_path", help = "SFTP Path")
    parser.add_argument("file_to_upload", help = "File to Upload")

    args = parser.parse_args()

    sftp_username = urllib.quote(args.sftp_username, "")
    sftp_password = urllib.quote(args.sftp_password, "")
    sftp_domainname = urllib.quote(args.sftp_domainname)
    sftp_path = urllib.quote(args.sftp_path)
    file_to_upload = os.path.abspath(args.file_to_upload)

    if not os.path.exists(file_to_upload):
        sys.exit("File to Upload \"%s\" does not exist!" % file_to_upload)

    # Deploy ##################################################################

    print "Uploading %s..." % os.path.basename(file_to_upload)
    sys.stdout.flush()

    if sys.platform.startswith("win"): # windows

        command = []

        command.append("WinSCP.com")

        command.append("/command")

        command.append("\"option batch abort\"")
        command.append("\"option confirm off\"")

        command.append("\"open -hostkey sftp://" +
        sftp_username + ":" + sftp_password + "@" + sftp_domainname + ":22\"")

        command.append("\"put " +
        "\"" + file_to_upload + "\"" + " " +
        "\"" + sftp_path.strip("/") + "/" +
        os.path.basename(file_to_upload) + "\"" + "\"")

        if os.path.isdir(file_to_upload):

            command.append("\"synchronize -delete remote " +
            "\"" + file_to_upload + "\"" + " " +
            "\"" + sftp_path.strip("/") + "/" +
            os.path.basename(file_to_upload) + "\"" + "\"")

        command.append("\"exit\"")

        # no check_call
        if subprocess.call(' '.join(command)):

            print "Trying again..."
            print "Uploading %s..." % os.path.basename(file_to_upload)
            sys.stdout.flush()

            # no check_call
            if subprocess.call(' '.join(command)):

                print "Uploading Failed!"
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
