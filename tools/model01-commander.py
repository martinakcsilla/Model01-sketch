#! /usr/bin/env python
## model01-commander.py -- Model01 helper tool
## Copyright (C) 2017  Gergely Nagy
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

import serial
import sys
import sh
import time

class AppSel (object):
    _appmap = {"music": ["rhythmbox", "spotify", "banshee", "kodi", "plex"],
               "chat": ["slack", "Mstdn"],
               "emacs": "emacs",
               "term": "gnome-terminal",
               "web": ["chrom", "Chrome"],
               "pwmgr": "keepass",
               "social": {"apps": ["mstdn", "tweetdeck"]}}

    def select (self, apps, with_escape = True):
        if isinstance (apps, list):
            for app in apps:
                if self.select (app):
                    break

        if isinstance (apps, dict):
            for app in apps["apps"]:
                self.select(app, with_escape = False)
            sh.xdotool ("key", "Escape")
            return True

        success = True
        try:
            sh.wmctrl ("-x", "-a", apps)
        except sh.ErrorReturnCode:
            success = False

        if with_escape:
            sh.xdotool ("key", "Escape")
        return success

    def switchTo (self, app):
        if app in self._appmap:
            self.select (self._appmap[app])

class Commander (object):
    _appSel = AppSel ()

    def run (self):
        with serial.Serial ("/dev/ttyACM0", 9600, timeout = 1) as ser:
            while True:
                cmd = ser.readline ().strip ()
                if cmd.startswith ("appsel:"):
                    app = cmd[7:]
                    print "appsel: %s" % app
                    self._appSel.switchTo (app)

commander = Commander ()

while True:
    try:
        commander.run ()
    except Exception:
        print "WARNING: Connection to serial lost, sleeping 10s..."
        time.sleep (10)
        print "WARNING: Sleep over, resuming!"
        pass
