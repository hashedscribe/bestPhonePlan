import random
count = 0
x = int(input("How many people to generate?"))

while(count < x):
    print(str(random.randint(0, 10)) + "." + str(random.randint(1,10)) + " " + str(random.randint(30, 100)) + "." + str(random.randint(1,10)) + " " + str(random.randint(0, 20)) + "." + str(random.randint(1,10)))
    count = count+1