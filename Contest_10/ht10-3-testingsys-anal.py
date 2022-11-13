with open("test_outp2.txt", "r") as f:
    tests = f.readlines()

for test in tests:
    values = test.split(" ")
    if(int(values[0]) < int(values[1])):
        print(values)
