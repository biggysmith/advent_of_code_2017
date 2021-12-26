import itertools

input = open("day02_input.txt")
print("part1:",sum(max(map(int,line.split())) - min(map(int,line.split())) for line in input.readlines()))

input = open("day02_input.txt")
print("part2:",sum(a//b for line in input.readlines() for a,b in itertools.product(list(map(int,line.split())),list(map(int,line.split()))) if a!=b and a%b==0))
