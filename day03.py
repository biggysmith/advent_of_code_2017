import math

def n_to_xy(n):
	k = math.ceil((math.sqrt(n)-1)/2)
	t = 2*k+1
	m = t**2 
	t = t-1

	if n >= m-t:
		return k-(m-n),-k        
	else:
	   m = m-t

	if n >= m-t: 
		return -k, -k+(m-n)       
	else: 
		m = m-t 

	if n >= m-t:
	    return -k+(m-n), k 
	else:
		return k, k-(m-n-t)

def manhatten(x0,y0,x1,y1):
	return abs(x1-x0) + abs(y1-y0)

def print_grid(g,w,h):
	for y in range(h):
		for x in range(w):
			print(g[y*w+x], end='')
		print()
	print()

x,y = n_to_xy(325489)
print("part1:", manhatten(x,y,0,0))


w = 35
h = 35
grid = [0]*w*h

p = (20,20)
num = 1

def next(point, x):
    if x == 0:
        return (point[0] + 1, point[1])
    if x == 1:
        return (point[0], point[1] + 1)
    if x == 2:
        return (point[0] - 1, point[1])
    if x == 3:
        return (point[0], point[1] - 1)

x = 0
grid[p[1]*w+p[0]] = 1

while num < 325489:
    q = next(p, (x+1) % 4)
    if grid[q[1]*w+q[0]] == 0:
        x = (x+1) % 4
    p = next(p,x)
    num = 0
    num += grid[(p[1])*w+p[0]-1]
    num += grid[(p[1]+1)*w+p[0]]
    num += grid[(p[1])*w+p[0]+1]
    num += grid[(p[1]-1)*w+p[0]]
    num += grid[(p[1]+1)*w+p[0]-1]
    num += grid[(p[1]-1)*w+p[0]-1]
    num += grid[(p[1]-1)*w+p[0]+1]
    num += grid[(p[1]+1)*w+p[0]+1]
    grid[p[1]*w+p[0]] = num

print("part2:", num)
