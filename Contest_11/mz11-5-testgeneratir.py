n = int(input("Num of tests: "))
filename = str(input("Finemame: "))

tests = list()

for i in range(1, n):
    tests.append(i)
with open(filename, "w") as f:
    for test in tests:
        f.write(str(test) + " ")
