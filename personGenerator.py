import random
count = 0
x = int(input("How many people to generate?"))

while(count < x):
    print(str(random.randint(0, 15)) + "." + str(random.randint(1,10)) + " " + str(random.randint(10, 100)) + "." + str(random.randint(1,10)) + " " + str(random.randint(0, 30)) + "." + str(random.randint(1,10)))
    count = count+1