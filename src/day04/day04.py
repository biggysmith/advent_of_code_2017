import itertools

def is_valid(phrase):
	l = list(map(lambda s: s.strip(), phrase.split(' ')))
	return len(l) == len(set(l))


input = open("day04_input.txt")
print("part1:", sum([is_valid(line) for line in input.readlines()]))

def is_anagram(w0,w1):
	return sorted(w0) == sorted(w1)

def is_valid2(phrase):
	if not is_valid(phrase):
		return False

	l = list(map(lambda s: s.strip(), phrase.split(' ')))
	for w0,w1 in itertools.product(l,l):
		if w0!=w1 and is_anagram(w0,w1):
			return False

	return True

input = open("day04_input.txt")
print("part2:", sum([is_valid2(line) for line in input.readlines()]))

