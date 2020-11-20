import sys
import re
import os
import glob
import time
import subprocess

def updateVersionFiles(files, newVersion, versionPrefix):
    year = time.strftime('%Y')
    regexVersion = versionPrefix + '\d*\.\d*\.\d*'
    regexYear = ' \d+ Socket Mobile, Inc.'
    for file in files:
        print('updating the version in the ' + file + ' to ' + newVersion)
        with open(file, 'r') as src:
            trg = open(file + '-new', 'w')
            lines = src.readlines()
            for line in lines:
                line = re.sub(regexVersion, versionPrefix + newVersion, line)
                line = re.sub(regexYear, ' ' + year + ' Socket Mobile, Inc.', line)
                trg.write(line)
            trg.close()
        os.remove(file)
        os.rename(file + '-new', file)

def updateLinkFiles(files):
    regexLink = re.compile(r'(.*git => ")(ssh:\/\/[A-Za-z@\.-]*\/scanning)(\/.*)')
    for file in files:
        print('updating the link to the repo for ' + file)
        with open(file, 'r') as src:
            trg = open(file + '-new', 'w')
            lines = src.readlines()
            for line in lines:
                line = regexLink.sub(r"\1https://github.com/SocketMobile\3", line)
                trg.write(line)
            trg.close()
        os.remove(file)
        os.rename(file + '-new', file)
        
        
def updateFiles(targetDirectory, newVersion):
    files = glob.glob(targetDirectory + '/README.md')
    updateVersionFiles(files, newVersion, 'Version ')
    files = glob.glob(targetDirectory + '/*.podspec')
    updateVersionFiles(files, newVersion, '')
    updateLinkFiles(files)

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
    version = subprocess.check_output(['git','describe', '--long'], encoding='utf8')
    version = version.splitlines()[0]
    version = version.split('-')
    subversion = version[0].split('.')
    version = subversion[0] + '.' + subversion[1] + '.' + str(int(version[1]) + 1)
    version = version.split('.')
    finalVersion = ''
    for n in range(3):
        finalVersion += version[n]
        if n < 2 :
            finalVersion += '.'

    os.chdir(currentDir)
    print('full version: ' + finalVersion +' '+directory)
    return finalVersion

def commitModifications(version):
    comment = 'update to version ' + version
    print('git commit -am ' + comment)
    output = subprocess.check_output(['git','commit', '-am', comment], encoding='utf8')

def tagSourceControl(version):
    print('git tag -a ' + version)
    output = subprocess.check_output(['git','tag', '-a', version, '-m', 'update version'], encoding='utf8')

def main():
    if (len(sys.argv) != 2):
        print('should have the new version as argument:')
        print('example: python updateVersion.py 1.0.28')
        return
    newVersion = sys.argv[1]
    target = getCurrentDir()
    # newVersion = getFullVersion(target)
    updateFiles(target + '/..', newVersion)
    commitModifications(newVersion)
    tagSourceControl(newVersion)

if __name__ == '__main__':
    result = main()
    sys.exit(result)
