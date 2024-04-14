import sys
import numpy as np
from collections import namedtuple
import matplotlib.pyplot as plt

Point = namedtuple('Point', ['x', 'y', 'ab', 'dx', 'dy', 'idx'])

def ccw(a, b, c):
    return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x

def swap_points(a, b):
    return b, a

def make_hull(sz, points, v, flag):
    hull = []
    start = v[1].idx if flag else v[0].idx
    end = v[0].idx if flag else v[1].idx
    i = start
    while True:
        hull.append(points[i])
        i = (i + 1) % sz
        if i == end:
            hull.append(points[i])
            break
    return hull

def between(a, b, c):
    if ccw(a, b, c) != 0:
        return False
    if a.x != b.x:
        if b.x < a.x:
            a, b = swap_points(a, b)
        return a.x <= c.x <= b.x
    else:
        if b.y < a.y:
            a, b = swap_points(a, b)
        return a.y <= c.y <= b.y
    
def plot_points(points, style, label):
    x = [p.x for p in points]
    y = [p.y for p in points]
    plt.plot(x, y, style, label=label)

def plot_hull(hull, color):
    for i in range(len(hull)):
        next_point = hull[(i + 1) % len(hull)]
        plt.plot([hull[i].x, next_point.x], [hull[i].y, next_point.y], color)

def plot_tangents(hull, ap, bp):
    plt.plot([ap.x, bp.x], [ap.y, bp.y], 'r--', label='Tangent')

def visualize_results(Apos, Bpos, convex, ap, bp):
    plt.figure(figsize=(10, 6))
    plot_points(Apos, 'bo', 'A group')
    plot_points(Bpos, 'go', 'B group')
    plot_hull(convex, 'k-')
    if ap and bp:
        plot_tangents(convex, ap, bp)
    plt.xlabel('X coordinate')
    plt.ylabel('Y coordinate')
    plt.title('Convex Hull and Tangents Visualization')
    plt.legend()
    plt.show()

def main():
    input_data = sys.stdin.read().split()
    index = 0
    t = int(input_data[index])
    index += 1
    for _ in range(t):
        n = int(input_data[index])
        index += 1
        Apos = []
        for i in range(n):
            x, y = int(input_data[index]), int(input_data[index+1])
            index += 2
            Apos.append(Point(x, y, False, 0, 0, i))
        m = int(input_data[index])
        index += 1
        Bpos = []
        for i in range(m):
            x, y = int(input_data[index]), int(input_data[index+1])
            index += 2
            Bpos.append(Point(x, y, True, 0, 0, i))
        
        pos = Apos + Bpos
        pos.sort(key=lambda p: (p.x, p.y))
        
        for i in range(1, n + m):
            pos[i] = pos[i]._replace(dx=pos[i].x - pos[0].x, dy=pos[i].y - pos[0].y)
        pos[1:] = sorted(pos[1:], key=lambda p: (p.dy * pos[0].dx, p.dx * pos[0].dy))

        convex = []
        for p in pos:
            while len(convex) > 1 and ccw(convex[-2], convex[-1], p) <= 0:
                convex.pop()
            convex.append(p)

        sz = len(convex)
        ap, bp = [], []
        for i in range(sz):
            j = (i + 1) % sz
            if convex[i].ab != convex[j].ab:
                if convex[i].ab:
                    bp.append(convex[i])
                    ap.append(convex[j])
                else:
                    ap.append(convex[i])
                    bp.append(convex[j])

        hull = make_hull(n + m, pos, [ap[0], bp[0]], bp[0].x < ap[0].x)
        ans = 0
        for i in range(1, len(hull) - 1):
            ans += ccw(hull[0], hull[i], hull[i + 1])

        area = abs(ans / 2)
        print(f'Convex hull area: {area:.1f}')

        # 시각화 함수 호출
        visualize_results(Apos, Bpos, convex, ap[0], bp[0])

if __name__ == "__main__":
    main()
