#!/bin/bash
CYAN='\033[36m'
NC='\033[m'
SOURCE_MODEL='wiki/src/system_design.mdj'
PACKAGE_NAME='Package1'

echo -e "${CYAN}generate diagrams form UML model${NC}"
staruml image ${SOURCE_MODEL} -f jpeg -o "wiki/src/diagrams/<%=filenamify(element.name)%>_diagram.jpeg"

echo ""

echo -e "${CYAN}generate header files from UML classes${NC}"
staruml ejs ${SOURCE_MODEL} -t ../UML_code_generator/.ejs/cpp-class.ejs -s "${PACKAGE_NAME}::@UMLClass" -o "Arduino_Pedalbox/src/<%=filenamify(element.name)%>.hpp"

echo -e "${CYAN}generate header files from UML interfaces${NC}"
staruml ejs ${SOURCE_MODEL} -t ../UML_code_generator/.ejs/cpp-class.ejs -s "${PACKAGE_NAME}::@UMLInterface" -o "Arduino_Pedalbox/src/<%=filenamify(element.name)%>.hpp"

echo -e "${CYAN}format header files with clang (google style)${NC}"
clang-format -i -style=Google Arduino_Pedalbox/src/*.hpp
clang-format -i -style=Google Arduino_Pedalbox/src/*.h