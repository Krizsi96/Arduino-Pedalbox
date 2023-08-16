import sys
sys.path.append("../UML_code_generator")
from code_postprocessing import file

TimeInterfaceHPP = file("Arduino_Pedalbox/src/TimeInterface.hpp")
TimeInterfaceHPP.replacePart("~TimeInterface() = 0", "~TimeInterface(){}")

SerialInterfaceHPP = file("Arduino_Pedalbox/src/SerialInterface.hpp")
SerialInterfaceHPP.replacePart("~SerialInterface() = 0", "~SerialInterface(){}")

insertLine = "\n\n#ifdef HOST\n#include <cstddef>\n#endif"
SerialInterfaceHPP.insertAfter("#include <stdint.h>", insertLine)