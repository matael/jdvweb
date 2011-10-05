#!/usr/bin/env python
#-*- encoding: utf-8 -*-
#
#       app.wsgi
#
#       Copyright 2011 Mathieu Gaborit <mat.gaborit@gmail.com>
#
#       This program is free software; you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation; either version 2 of the License, or
#       (at your option) any later version.
#
#       This program is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with this program; if not, write to the Free Software
#       Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#       MA 02110-1301, USA.
import sys
import os
import codecs
from markdown import markdown
from bottle import\
        Bottle,\
        run,\
        route,\
        template

os.chdir(os.path.dirname(__file__))

application = Bottle()

@application.route('/')
def echo_file():
    """ print file to html output """
    file = open("matrice.jdv", 'r')
    lines = [line.rstrip() for line in file.readlines()]
    file.close()
    output = template('matrice.tpl', lines=lines)
    return output

@application.route("/readme")
def about():
    readme_file = codecs.open("README.mkd", 'r', encoding='utf8')
    text = markdown(readme_file.read())
    return text


#def main():
#    run(application, host='localhost', port=8080)
#    return 0
#
#if __name__ == '__main__': main()

