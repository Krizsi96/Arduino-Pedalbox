#!/usr/bin/python3
import os
import subprocess
import sys
sys.path.append("StarUML-code-generator")
from code_postprocessing import file
import click

SOURCE_MODEL = 'system_design.mdj'
PACKAGE_NAME = 'Package1'
CODE_OUTPUT_DIR = 'Arduino_Pedalbox/include/'
DIAGRAM_OUTPUT_DIR = 'wiki/src/diagrams/'

@click.group()
def cli():
    pass

@click.command(help="build source code from UML models")
@click.argument('package', default=PACKAGE_NAME, required=False)
@click.option('--with-diagrams', '-d', is_flag=True, help="Export diagrams also")
def build_uml(package, with_diagrams):
    checkDependecies()
    if with_diagrams:
        generateDiagrams()
    generateHeaderFiles(package)
    generateInterfaceDefinitions(package)
    formatHeaderFiles()
    postProcessCode()

@click.command(help="export diagrams from UML models")
def export_diagrams():
    checkDependecies()
    generateDiagrams()

def generateDiagrams():
    click.echo(click.style("generate diagrams form UML model", fg='cyan'))
    subprocess.run(['staruml', 'image', SOURCE_MODEL, '-f', 'svg', '-o', f'{DIAGRAM_OUTPUT_DIR}<%=filenamify(element.name)%>_diagram.svg'])
    current_directory = os.getcwd()
    subprocess.run(['python3', 'StarUML-code-generator/svg_postprocess.py', f'{current_directory}/{DIAGRAM_OUTPUT_DIR}'])
    click.echo()

def generateHeaderFiles(package):
    click.echo(click.style("generate header files from UML classes", fg='cyan'))
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', 'StarUML-code-generator/.ejs/cpp-class.ejs', '-s', f'{package}::@UMLClass', '-o', 'Arduino_Pedalbox/include/<%=filenamify(element.name)%>.hpp'])
    click.echo()

def generateInterfaceDefinitions(package):
    click.echo(click.style("generate header files from UML interfaces", fg='cyan'))
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', 'StarUML-code-generator/.ejs/cpp-class.ejs', '-s', f'{package}::@UMLInterface', '-o', 'Arduino_Pedalbox/include/<%=filenamify(element.name)%>.hpp'])

def formatHeaderFiles():
    click.echo(click.style("format header files with clang (google style)", fg='cyan'))
    os.system('clang-format -i -style=Google Arduino_Pedalbox/include/*.hpp')

def postProcessCode():
    click.echo(click.style("postprocess code", fg='cyan'))
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

def checkDependecies():
    click.echo(click.style("check dependencies", fg='cyan'))
    if not os.path.exists('StarUML-code-generator'):
        click.echo(click.style("clone StarUML-code-generator", fg='cyan'))
        result = subprocess.run(['git', 'clone', 'https://github.com/Krizsi96/StarUML-code-generator.git'])
        if result.returncode != 0:
            click.echo(click.style(f"StarUML-code-generator could not be cloned", fg="red"))
            sys.exit(1)
        click.echo(click.style(f"StarUML-code-generator is cloned", fg="green"))
    result = subprocess.run(['git', 'checkout', 'main'], cwd='StarUML-code-generator')
    if result.returncode != 0:
        click.echo(click.style(f"Could not checkout 'main'", fg="red"))
        sys.exit(1)
    result = subprocess.run(['git', 'pull'], cwd='StarUML-code-generator')
    if result.returncode != 0:
        click.echo(click.style(f"Could not pull", fg="red"))
        sys.exit(1)
    click.echo(click.style(f"StarUML-code-generator is up to date", fg="green")) 

cli.add_command(build_uml)
cli.add_command(export_diagrams)

if __name__ == '__main__':
    cli()