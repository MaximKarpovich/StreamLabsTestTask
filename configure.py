import time, os, sys, re
import subprocess
import argparse
from shutil import copyfile, rmtree, copytree, copy2
from time import sleep

def copy_all_files(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            copytree(s, d, symlinks, ignore)
        else:
            copy2(s, d)
            
def build_command(args = ""):
    is_mkdir = False
    os.chdir(HOME_DIR)
    if not os.path.exists('build'):
            os.mkdir('build')
            is_mkdir = True
    os.chdir('build')
    visual_studio_proccess = None
    if (args == "") or (args != "" and is_mkdir == True):
            visual_studio_proccess = subprocess.Popen('cmake -G "Visual Studio 15 2017 Win64" ../')
            visual_studio_proccess.wait()
    if (args == "build"):
            visual_studio_proccess = subprocess.Popen('cmake --build . --config Release -- /m')
            visual_studio_proccess.wait()
    os.chdir(HOME_DIR) 
    if(visual_studio_proccess.returncode != 0):
            sys.exit(visual_studio_proccess.returncode)
            return version_next

parser = argparse.ArgumentParser()
parser.add_argument('-b','--build',action="store_true", help="Make build. Example: configure.py -b")
parser.add_argument('-s','--solution', action="store_true",help="Generate solution. Example: configure.py -s")
args = parser.parse_args()

HOME_DIR = os.getcwd()
if(len(sys.argv) == 1):
    parser.print_help()
if(args.solution):
    build_command()
if(args.build):
	build_command('build')   
sys.exit(0)
