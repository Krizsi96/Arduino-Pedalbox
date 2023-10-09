import os
import sys
import subprocess
import click

GREEN = '\033[32m'
RED = '\033[31m'
NC = '\033[0m'

wiki_directory = 'TripleX_tutorial'
wiki_url = 'https://github.com/Krizsi96/TripleX_tutorial.git'

@click.group()
def git_commands():
    pass

@click.command(help="Checks out the same branch as the project")
def checkout():
    if not os.path.isdir(wiki_directory):
        print(f"{RED}{wiki_directory} is not cloned{NC}")
        clone_wiki()

    branch = getProjectBranch()

    os.chdir(wiki_directory)
    result = subprocess.run(['git', 'checkout', branch])
    if result.returncode != 0:
        result = subprocess.run(['git', 'checkout', '-b', branch])
        if result.returncode != 0:
            print(f"{RED}Could not checkout branch {branch}{NC}")
            sys.exit(1)
    os.chdir('..')
    print(f"{GREEN}Checked out branch {branch}{NC}")

@click.command(help="Merge the project branch into the master branch")
def merge():
    branch = getProjectBranch()
    
    os.chdir(wiki_directory)
    checkoutMaster()

    result = subprocess.run(['git', 'merge', branch])
    if result.returncode != 0:
        print(f"{RED}Could not merge branch {branch} into master{NC}")
        sys.exit(1)
    print(f"{GREEN}Merged branch {branch} into master{NC}")

    result = subprocess.run(['git', 'branch', '-d', branch])
    if result.returncode != 0:
        print(f"{RED}Could not delete branch {branch}{NC}")
        sys.exit(1)
    print(f"{GREEN}Deleted branch {branch}{NC}")

def clone_wiki():
    print(f"Cloning {wiki_directory}...")
    result = subprocess.run(['git', 'clone', wiki_url])
    if result.returncode != 0:
        print(f"{RED}{wiki_directory} could not be cloned{NC}")
        sys.exit(1)
    print(f"{GREEN}{wiki_directory} is cloned{NC}")

def checkoutMaster():
    result = subprocess.run(['git', 'checkout', 'master'])
    if result.returncode != 0:
        print(f"{RED}Could not checkout 'master', let's try 'main'{NC}")
        result = subprocess.run(['git', 'checkout', 'main'])
        if result.returncode != 0:
            print(f"{RED}Could not checkout main{NC}")
            sys.exit(1)
    print(f"{GREEN}Checked out master{NC}")

def checkForUpdates():
    os.chdir(wiki_directory)
    checkoutMaster()
    result = subprocess.run(['git', 'pull'])
    if result.returncode != 0:
        print(f"{RED}{wiki_directory} could not be pulled{NC}")
        sys.exit(1)
    os.chdir('..')
    print(f"{GREEN}{wiki_directory} is up to date{NC}")

def getProjectBranch():
    result = subprocess.run(['git', 'branch', '--show-current'], stdout=subprocess.PIPE)
    if result.returncode != 0:
        print(f"{RED}Could not get current branch{NC}")
        sys.exit(1)
    branch = result.stdout.decode('utf-8').strip()
    return branch

git_commands.add_command(checkout)
git_commands.add_command(merge)

if __name__ == '__main__':
    git_commands()