import sys
import os
import random
import shutil
import stat

YELLOW='\x1b[33m'
RESET='\x1b[0m'
GREEN='\x1b[32m'

def file_len(name):

    count = 0
    with open(name, "rb") as f:
        byte = f.read(1) 
        while byte:
            byte = f.read(1)
            if byte == b"\n":
                count += 1
    return count

def file_sizel(name):

    lsfull = []
    with open(files, "rb") as f:
       ranlines = -1
       size = -1
       byte = f.read(1)
       size += 1 
       while byte:
           byte = f.read(1)
           size += 1
           if byte == b"\n":
               ranlines += 1 
               if ranlines in ls:
                   lsfull.append((ranlines, size)) 
               size = -1
    return lsfull

def file_corruptl(f, x):

    i = random.randint(0, x[1])
    size = random.randint(0, 20)
    r = os.urandom(size)
    f.seek(i)
    f.write(r)
    print("Line {} at {}, is now infected by {} random chars".format(x[0], i, size))

if __name__ == '__main__' :
    
    newdir = "./corrupted/"
    try:
        shutil.rmtree(newdir)
    except:
        pass
    os.mkdir(newdir)

    for files in os.listdir(sys.argv[1]):
        try:
            shutil.copyfile(sys.argv[1] + files, newdir + files)
            st = os.stat(newdir + files)
            os.chmod(newdir + files, st.st_mode | stat.S_IEXEC)
        except:
            pass

    os.chdir(newdir)
    for files in os.listdir("."):
        
        lines = file_len(files)
        randlines = random.randint(0, lines) % 10
        ls = []
        i = 0
        while i < randlines:
            ls.append(random.randint(0, lines))
            i += 1 

        lsfull = file_sizel(files) 

        print(YELLOW + "[File {} is targeted]".format(files) + RESET)
        if randlines == 0:
            print("The randomness has had mercy of {} !".format(files))
        with open(files, "r+b") as f:
            count = -1
            line = f.readline()
            count += 1
            while line:
                count += 1
                for x in lsfull:
                    if count == x[0]:
                        file_corruptl(f, x)
                line = f.readline()
        print("")

    print(GREEN + "All binaries inside dir {} have been successfully infected ! Enjoy !".format(sys.argv[1]) + RESET)
    exit(0)
