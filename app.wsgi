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
        template,\
        static_file,\
        error,\
        abort,\
        debug

# Remember to use trailing slash
STATIC_FILES = "/srv/simplelife/static/"
MATRIX_FILE = '/srv/simplelife/Matrice.JDV'
SAUVEGARDE_FILE = '/srv/simplelife/Sauvegarde.JDV'

os.chdir(os.path.dirname(__file__))

application = Bottle()

@application.route('/static/:filename')
def server_static(filename):
    """ Serve Static files """
    return static_file(filename, root='/srv/simplelife/static/')

@application.route('/current')
@application.route('/')
def echo_file():
    """ print file to html output """
    file = open(MATRIX_FILE, 'r')
    lines = [line.rstrip() for line in file.readlines()]
    file.close()
    output = template('matrice.tpl', lines=lines)
    return output

@application.route('/current.txt')
def echo_txt():
    """ print file to txt output """
    return open(MATRIX_FILE, 'r').readlines()


@application.route('/previous')
def echo_prev_file():
    """ print saved file to html output """
    file = open(SAUVEGARDE_FILE, 'r')
    lines = [line.rstrip() for line in file.readlines()]
    file.close()
    output = template('previous.tpl', lines=lines)
    return output

@application.route('/previous.txt')
def echo_prev_txt():
    """ print file to txt output """
    return open(SAUVEGARDE_FILE, 'r').readlines()

@application.route("/readme")
def about():
    #    readme_file = codecs.open("README.mkd", 'r', encoding='utf8')
    #    text = markdown(readme_file.read())
    #    return template('readme.tpl', text=text)
    readme_file = codecs.open("README.mkd", 'r', encoding='utf8')
    text = markdown(readme_file.read())
    template = open("readme.tpl",'r')
    return str(template.read()).format(text)


@application.error(404)
def mistake_404(code):
    """ serve all 404 errors """
    return template("404.tpl")

@application.route('/change_state/:x#[0-9]+#/:y#[0-9]+#')
def change_state(x,y):
    """ Change state of a given cell"""
    file = open(MATRIX_FILE, 'r')
    lines = [[char for char in line.rstrip()] for line in file.readlines()]
    file.close()
    x=int(x)
    y=int(y)
    cell = lines[y][x]
    if cell=='0':
        lines[y][x]='1'
    else:
        lines[y][x]='0'
    file = open(MATRIX_FILE,'w')
    for i in lines:
        for j in i:
            file.write(str(j))
        file.write('\n')
    file.close()
    return "OK"

def main():
    run(application, host='localhost', port=8080)
    return 0

if __name__ == '__main__': main()

