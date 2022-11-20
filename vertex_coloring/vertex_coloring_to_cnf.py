import sys
def main():
    n, m = map(int, input().split())
    edges = []
    for i in range(m):
        e1, e2 = map(int, input().split())
        edges.append((e1, e2))
    d = int(input())
    print("p cnf " + str(n*d) + " " + str(number_of_clauses(n, m, d)))
    at_least_one_color(n, d)
    adjacent_constarint(edges, d)
    
def number_of_clauses(n, m, d):
#    return int((n + m*d + n*(d*(d-1))) / 2)
    return n + m*d
    
#    1    2 ...    d  // the color of v_1 is 1 or 2 or ... or d
#  d+1  d+2 ...   2d  // the color of v_2 is 1 or 2 or ... or d
#
# (n-1)d+1 (n-1)d+2 ... (n-1)d+d  // the color of v_n is 1 or 2 or ... or d
def at_least_one_color(n, d):
    for i in range(n):
        s = ""
        for j in range(d):
            s += str(i*d+j+1) + " "
        s += "0"
        print(s)

# adjacent vertices v_i and v_k have different colors
# -v_ij -v_kj
def adjacent_constarint(es, d):
    for e in es:
        for j in range(d):
            s = ""
            s += "-" + str(e[0]*d+(j+1)) + " "
            s += "-" + str(e[1]*d+(j+1)) + " 0"
            print(s)

if __name__ == "__main__":
    main()
