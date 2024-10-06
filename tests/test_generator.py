import random
import argparse

parser = argparse.ArgumentParser(description='Генерация файла с случайными числами.')
parser.add_argument('filename', type=str, help='Имя выходного файла')

args = parser.parse_args()

with open(args.filename, "w") as f:
    cap = random.randint(1, 1000)
    num = random.randint(1, 10000000)

    f.write(str(cap) + " " + str(num) + " ")

    for i in range(num):
        f.write(str(random.randint(1, 100)) + " ")