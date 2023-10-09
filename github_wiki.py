import os
import sys
import subprocess

GREEN = '\033[32m'
RED = '\033[31m'
NC = '\033[0m'

# Check if the wiki of the project is cloned and clone it if not
if not os.path.isdir('Arduino-Pedalbox.wiki'):
    print(f"{RED}Arduino-Pedalbox.wiki is not cloned{NC}")
    print("Cloning Arduino-Pedalbox.wiki...")
    result = subprocess.run(['git', 'clone', 'https://github.com/Krizsi96/Arduino-Pedalbox.wiki.git'])
    if result.returncode != 0:
        print(f"{RED}Arduino-Pedalbox.wiki could not be cloned{NC}")
        sys.exit(1)

print(f"{GREEN}Arduino-Pedalbox.wiki is cloned{NC}")