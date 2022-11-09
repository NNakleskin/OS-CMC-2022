import os


for i in range(100):
    for j in range(100):
        if os.system("./solution res.o {} {}".format(str(i), str(j))) != 0:
                print("{} {}".format(str(i), str(j)))
