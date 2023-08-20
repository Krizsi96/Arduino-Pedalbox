import os
import subprocess
import sys
sys.path.append("../UML_code_generator")
from code_postprocessing import file

CYAN = '\033[36m'
NC = '\033[m'
SOURCE_MODEL = 'wiki/src/system_design.mdj'
PACKAGE_NAME = 'Package1'

def main():
    print(f"{CYAN}generate diagrams form UML model{NC}")
    subprocess.run(['staruml', 'image', SOURCE_MODEL, '-f', 'svg', '-o', 'wiki/src/diagrams/<%=filenamify(element.name)%>_diagram.svg'])
    subprocess.run(['python3', '../UML_code_generator/svg_postprocess.py', '/home/krizsi90/Documents/Projects/Arduino_Pedalbox/wiki/src/diagrams/'])
    print()

    print(f"{CYAN}generate header files from UML classes{NC}")
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', '../UML_code_generator/.ejs/cpp-class.ejs', '-s', f'{PACKAGE_NAME}::@UMLClass', '-o', 'Arduino_Pedalbox/src/<%=filenamify(element.name)%>.hpp'])
    print(f"{CYAN}generate header files from UML interfaces{NC}")
    subprocess.run(['staruml', 'ejs', SOURCE_MODEL, '-t', '../UML_code_generator/.ejs/cpp-class.ejs', '-s', f'{PACKAGE_NAME}::@UMLInterface', '-o', 'Arduino_Pedalbox/src/<%=filenamify(element.name)%>.hpp'])
    
    print(f"{CYAN}format header files with clang (google style){NC}")
    os.system('clang-format -i -style=Google Arduino_Pedalbox/src/*.hpp')
    os.system('clang-format -i -style=Google Arduino_Pedalbox/src/*.h')

    print(f"{CYAN}post process code{NC}")
    TimeInterfaceHPP = file("Arduino_Pedalbox/src/TimeInterface.hpp")
    TimeInterfaceHPP.replacePart("~TimeInterface() = 0", "~TimeInterface(){}")
    SerialInterfaceHPP = file("Arduino_Pedalbox/src/SerialInterface.hpp")
    SerialInterfaceHPP.replacePart("~SerialInterface() = 0", "~SerialInterface(){}")
    insertLine = "\n\n#ifdef HOST\n#include <cstddef>\n#endif"
    SerialInterfaceHPP.insertAfter("#include <stdint.h>", insertLine)

if __name__ == '__main__':
    main()