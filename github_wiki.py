import os
import sys
import subprocess

GREEN = '\033[32m'
RED = '\033[31m'
NC = '\033[0m'

# Check if the wiki of the project is cloned
if not os.path.isdir('Arduino-Pedalbox.wiki'):
    print(f"{RED}Arduino-Pedalbox.wiki is not cloned{NC}")
    sys.exit(1)
else:
    print(f"{GREEN}Arduino-Pedalbox.wiki is cloned{NC}")