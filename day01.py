input = open("day01_input.txt").read()

print("part1:", sum(int(a) for a,b in zip(input,input[1:]+input[:1]) if a==b))

print("part2:", sum(int(a) for a,b in zip(input,input[len(input)//2:]+input[:len(input)//2]) if a==b))
