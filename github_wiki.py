import os
import sys
import subprocess
import click

wiki_directory = 'Arduino-Pedalbox.wiki'
wiki_url = 'https://github.com/Krizsi96/Arduino-Pedalbox.wiki.git'

@click.group()
def git_commands():
    pass

@click.command(help="Checks out the same branch as the project")
def checkout():
    click.echo("Doing checkout...")
    if not os.path.isdir(wiki_directory):
        click.echo(click.style(f"{wiki_directory} is not cloned", fg="red"))
        clone_wiki()

    branch = getProjectBranch()

    click.echo(f"Checking out {branch}...")
    os.chdir(wiki_directory)
    result = subprocess.run(['git', 'checkout', branch])
    if result.returncode != 0:
        click.echo(f"{branch} does not exist in {wiki_directory}, let's create it...")
        result = subprocess.run(['git', 'checkout', '-b', branch])
        if result.returncode != 0:
            click.echo(click.style(f"Could not checkout branch {branch}", fg="red"))
            sys.exit(1)
    os.chdir('..')
    click.echo(click.style(f"Checked out branch {branch}", fg="green"))

@click.command(help="Merge the project branch into the master branch")
def merge():
    branch = getProjectBranch()
    
    os.chdir(wiki_directory)
    checkoutMaster()

    result = subprocess.run(['git', 'merge', branch])
    if result.returncode != 0:
        click.echo(click.style(f"Could not merge branch {branch} into master", fg="red"))
        sys.exit(1)
    click.echo(click.style(f"Merged branch {branch} into master", fg="green"))

    result = subprocess.run(['git', 'branch', '-d', branch])
    if result.returncode != 0:
        click.echo(click.style(f"Could not delete branch {branch}", fg="red"))
        sys.exit(1)
    click.echo(click.style(f"Deleted branch {branch}", fg="green"))

def clone_wiki():
    click.echo(f"Cloning {wiki_directory}...")
    result = subprocess.run(['git', 'clone', wiki_url])
    if result.returncode != 0:
        click.echo(click.style(f"{wiki_directory} could not be cloned", fg="red"))
        sys.exit(1)
    click.echo(click.style(f"{wiki_directory} is cloned", fg="green"))

def checkoutMaster():
    result = subprocess.run(['git', 'checkout', 'master'])
    if result.returncode != 0:
        click.echo(click.style(f"Could not checkout 'master', let's try 'main'", fg="red"))
        result = subprocess.run(['git', 'checkout', 'main'])
        if result.returncode != 0:
            click.echo(click.style(f"Could not checkout main", fg="red"))
            sys.exit(1)
    click.echo(click.style(f"Checked out master", fg="green"))

def checkForUpdates():
    click.echo("Checking for updates...")
    os.chdir(wiki_directory)
    checkoutMaster()
    result = subprocess.run(['git', 'pull'])
    if result.returncode != 0:
        click.echo(click.style(f"{wiki_directory} could not be pulled", fg="red"))
        sys.exit(1)
    os.chdir('..')
    click.echo(click.style(f"{wiki_directory} is up to date", fg="green"))

def getProjectBranch():
    click.echo("Geting project branch...")
    result = subprocess.run(['git', 'branch', '--show-current'], stdout=subprocess.PIPE)
    if result.returncode != 0:
        click.echo(click.style(f"Could not get current branch", fg="red"))
        sys.exit(1)
    branch = result.stdout.decode('utf-8').strip()
    return branch

git_commands.add_command(checkout)
git_commands.add_command(merge)

if __name__ == '__main__':
    git_commands()