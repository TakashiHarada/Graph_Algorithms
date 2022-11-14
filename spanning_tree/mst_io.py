import sys

def make_term(vname, w, j):
    sw = str(w)
    sj = str(j)
    return vname + "(" + sw + "," + sj + ")"

def make_term_in_of(w, u, v):
    sw = str(w)
    return sw + " " + make_term("e", u, v)

def make_objective_function(al):
    n = len(al)
    obj = ""
    for i in range (0, n):
        for e in al[i]:
            if i < e[0]:
                if "" != obj:
                    obj += " + "
                obj += make_term_in_of(e[1], i, e[0])
    return obj

def neighbour(al, v):
    N = []
    for u in al[v]:
        N.append(u)
    return N

def make_4tuple(vname, w, k, i):
    sw = str(w[0])
    sk = str(k)
    if i < w[0]:
        small = str(i)
        large = str(w[0])
    else:
        small = str(w[0])
        large = str(i)
    return vname + "(" + sw + "," + sk + "," + small + "," + large + ")"

def make_right_terms(i, ws, k):
    t = ""
    for w in ws:
        if "" != t:
            t += " - "
        t += make_4tuple("w", w, k-1, i)
    return t

def times_to_plus(i, al, k):
    c = ""
    for w in al[i]:
        c += make_4tuple("w", w, k-1, i) + " - " + make_term("v", w[0], k-1) + " <= 0\n"
        small = i
        large = w[0]
        if w[0] < i:
            small = w[0]
            large = i
        c += make_4tuple("w", w, k-1, i) + " - " + make_term("e", small, large) + " <= 0\n"
    return c

def make_connectivity_constraints(al, ts, b):
    n = len(al)
    c = ""

    c += make_term("v", b, 0) + " = 1\n"

    nob = [i for i in range(n)]
    nob.remove(int(b))

    for i in nob:
        c += make_term("v", i, 0) + " = 0\n"

    for i in nob:
        for k in range(1, n):
            c += make_term("v", i, k) + " - " + make_right_terms(i, al[i], k) + " <= 0\n"
            c += times_to_plus(i, al, k)
    return c

def make_adjacency_list(lines, n):
    al = [ [] for v in range(n) ]
    for line in lines:
        e = line.split(' ')
        i = int(e[0])
        j = int(e[1])
        w = int(e[2])
        al[i].append((j, w))
        al[j].append((i, w))
    return al
        
def main():
    lines = sys.stdin.readlines()
    lines = [line.rstrip() for line in lines]

    line = lines[0].split(' ')
    N = int(line[0])
    M = int(line[1])

    ts = lines[len(lines)-1]
    ts = ts.split(' ')
    
    al = make_adjacency_list(lines[1:M+1], N)

    ## objective function
    print("minimize")
    print(make_objective_function(al))

    ## select a base vertex
    b = ts[0]
    
    ## constarints
    print("\nsubject to")
    print(make_connectivity_constraints(al, ts, b))

    # terminal constraint
    for t in ts:
        print(make_term("v", int(t), N-1) + " = 1")
    
    # binary constraints
    print("\nbinary")
    for i in range(0,N):
        for e in neighbour(al, i):
            if i < e[0]:
                print(make_term("e", i, e[0]))
                
    for i in range(0,N):
        for j in range(0,N):
            print(make_term("v", i, j))

    # for 4-tuple variables
    nob = [i for i in range(N)]
    nob.remove(int(b))
    for i in nob:
        for k in range(1, N):
            for w in al[i]:
                print(make_4tuple("w", w, k-1, i))
            
    print("end")
    
        
if __name__ == "__main__":
    main()
