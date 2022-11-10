# E.g.
# $ echo '(5,5,5,4,3,2,1,1)' | python is_graph.py

def is_graph(xs):
    for x in xs:
        if x < 0:
            return False
    i = 0;
    for x in xs:
        if 0 != x:
            break
        i += 1
    if (len(xs) == i):
        return True
    ys = xs[1:]
    for j in range(xs[0]):
        ys[j] -= 1
    ys.sort()
    ys.reverse()
    return is_graph(ys)

def main():
    line = input()
    xs = line[1:(len(line)-1)]
    xs = xs.split(',')
    if is_graph([int(x) for x in xs]):
        print("Input sequence is the degree sequence for some graph")
    else:
        print("Input sequence is not a degree sequence.")
        
if __name__ == "__main__":
    main()
