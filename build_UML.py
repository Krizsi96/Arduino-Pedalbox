#!/usr/bin/python3
import os
import subprocess
import sys
sys.path.append("../UML_code_generator")
from code_postprocessing import file
import click

SOURCE_MODEL = 'system_design.mdj'
PACKAGE_NAME = 'Package1'

@click.command(help="build source code from UML models")
@click.argument('package', default=PACKAGE_NAME, required=False)
@click.option('--with-diagrams', '-d', type=bool, help="Export diagrams also")
def build_uml(package, with_diagrams):
    if with_diagrams:
        generateDiagrams()
    generateHeaderFiles(package)
    generateInterfaceDefinitions(package)
    formatHeaderFiles()
    postProcessCode()

def generateDiagrams():
    click.echo(click.style("generate diagrams form UML model", fg='cyan'))
    subprocess.run(['staruml', 'image', SOURCE_MODEL, '-f', 'svg', '-o', 'wiki/src/diagrams/<%=filenamify(element.name)%>_diagram.svg'])
    subprocess.run(['python3', '../UML_code_generator/svg_postprocess.py', '/home/krizsi90/Documents/Projects/Arduino_Pedalbox/wiki/src/diagrams/'])
    click.echo()

def generateHeaderFiles(package):
    click.echo(click.style("generate header files from UML classes", fg='cyan'))
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', '../UML_code_generator/.ejs/cpp-class.ejs', '-s', f'{package}::@UMLClass', '-o', 'Arduino_Pedalbox/include/<%=filenamify(element.name)%>.hpp'])
    click.echo()

def generateInterfaceDefinitions(package):
    click.echo(click.style("generate header files from UML interfaces", fg='cyan'))
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', '../UML_code_generator/.ejs/cpp-class.ejs', '-s', f'{package}::@UMLInterface', '-o', 'Arduino_Pedalbox/include/<%=filenamify(element.name)%>.hpp'])

def formatHeaderFiles():
    click.echo(click.style("format header files with clang (google style)", fg='cyan'))
    os.system('clang-format -i -style=Google Arduino_Pedalbox/include/*.hpp')

def postProcessCode():
    click.echo(click.style("post process code", fg='cyan'))
    TimeInterfaceHPP = file("Arduino_Pedalbox/include/TimeInterface.hpp")
    TimeInterfaceHPP.replacePart("~TimeInterface() = 0;", "~TimeInterface() {}")

    SerialInterfaceHPP = file("Arduino_Pedalbox/include/SerialInterface.hpp")
    SerialInterfaceHPP.replacePart("~SerialInterface() = 0;", "~SerialInterface() {}")
    insertLine = "\n\n#ifdef HOST\n#include <cstddef>\n#endif"
    SerialInterfaceHPP.insertAfter("#include <stdint.h>", insertLine)

    SensorInterfaceHPP = file("Arduino_Pedalbox/include/SensorInterface.hpp")
    SensorInterfaceHPP.replacePart("virtual ~SensorInterface() = 0;", "virtual ~SensorInterface() {}")

    PedalboxHPP = file("Arduino_Pedalbox/include/Pedalbox.hpp")
    PedalboxHPP.replacePart("\"Joystick.hpp\"", "<Joystick.h>")
    click.echo()

if __name__ == '__main__':
    build_uml()