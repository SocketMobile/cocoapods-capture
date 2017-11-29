import sys
import re
import os
import glob
import time
import subprocess

def updateVersionFiles(files, newVersion):
    year = time.strftime('%Y')
    regexVersion = '\d*\.\d*\.\d*'
    regexYear = 'Copyright \d\w all'
    for file in files:
        print 'updating the version in the ' + file + ' to ' + newVersion
        with open(file, 'r') as src:
            trg = open(file + '-new', 'w')
            lines = src.readlines()
            for line in lines:
                line = re.sub(regexVersion, newVersion, line)
                line = re.sub(regexYear, 'Copyright ' + year + ' all', line)
                trg.write(line)
            trg.close()
        os.remove(file)
        os.rename(file + '-new', file)

def updateFiles(targetDirectory, newVersion):
    files = glob.glob(targetDirectory + '/*.txt')
    updateVersionFiles(files, newVersion)
    files = glob.glob(targetDirectory + '/*.podspec')
    updateVersionFiles(files, newVersion)

def getCurrentDir():
    nbParam = len(sys.argv)
    cwd = sys.argv[0]
    path = ''
    if not cwd.startswith('/'):
        path = os.getcwd()
    cwd = cwd.split('/')
    cwd = cwd[:len(cwd)-1]
    for p in cwd:
        if len(p)>0:
            path += '/'
            path += p
    return path

# return the actual version that is the tag
# with the number of commit
# but limit the version to 3 number 10.2.123
def getFullVersion(directory):
    currentDir = os.getcwd()
    os.chdir(directory)
    version = subprocess.check_output(['git','describe', '--long'])
    version = version.splitlines()[0]
    version = version.split('-')
    subversion = version[0].split('.')
    version = subversion[0] + '.' + subversion[1] + '.' + str(int(version[1]) + 1)
    version = version.split('.');
    finalVersion = ''
    for n in range(3):
        finalVersion += version[n]
        if n < 2 :
            finalVersion += '.'

    os.chdir(currentDir)
    print 'full version: ' + finalVersion +' '+directory
    return finalVersion

def commitModifications(version):
    comment = 'update to version ' + version
    print 'git commit -am ' + comment
    output = subprocess.check_output(['git','commit', '-am', comment])

def tagSourceControl(version):
    print 'git tag -a ' + version
    output = subprocess.check_output(['git','tag', '-a', version, '-m', 'update version'])

def main():
    target = getCurrentDir()
    newVersion = getFullVersion(target)
    updateFiles(target + '/..', newVersion)
    commitModifications(newVersion)
    tagSourceControl(newVersion)

if __name__ == '__main__':
    result = main()
    sys.exit(result)
