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

# Check if the wiki of the project is up to date and pull it if not
os.chdir('Arduino-Pedalbox.wiki')
result = subprocess.run(['git', 'pull'])
if result.returncode != 0:
    print(f"{RED}Arduino-Pedalbox.wiki could not be pulled{NC}")
    sys.exit(1)

print(f"{GREEN}Arduino-Pedalbox.wiki is up to date{NC}")

# Check out the same branch as the project
os.chdir('../')
result = subprocess.run(['git', 'branch', '--show-current'], stdout=subprocess.PIPE)
if result.returncode != 0:
    print(f"{RED}Could not get current branch{NC}")
    sys.exit(1)

branch = result.stdout.decode('utf-8').strip()
os.chdir('Arduino-Pedalbox.wiki')
result = subprocess.run(['git', 'checkout', branch])
if result.returncode != 0:
    result = subprocess.run(['git', 'checkout', '-b', branch])
    if result.returncode != 0:
        print(f"{RED}Could not checkout branch {branch}{NC}")
        sys.exit(1)

print(f"{GREEN}Checked out branch {branch}{NC}")