import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import ConvexHull

# 주어진 다각형의 좌표들
polygon1 = np.array([
    [-12, 50],
    [0, 23],
    [14, 7],
    [6, 8],
    [10, -3],
    [22, 5],
    [20, 0],
    [33, 5],
    [25, 20],
    [12, 25]
])

polygon2 = np.array([
    [100, 20],
    [120, 30],
    [135, 76],
    [111, 45],
    [121, 99],
    [131, 100],
    [120, 110],
    [100, 100]
])

# 두 점 사이의 거리를 계산하는 함수
def distance(p1, p2):
    return np.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# 선분과 점 사이의 최소 거리를 계산하는 함수
def point_line_distance(point, line_points):
    p1, p2 = line_points
    num = abs((p2[1] - p1[1]) * point[0] - (p2[0] - p1[0]) * point[1] + p2[0] * p1[1] - p2[1] * p1[0])
    den = distance(p1, p2)
    return num / den

# 주어진 점에서 다각형의 각 선분까지의 최소 거리를 계산하고, 그 최소 거리를 갖는 선분을 반환하는 함수
def closest_polygon_edge_from_point(point, polygon):
    min_distance = np.inf
    closest_edge = None
    for i in range(len(polygon)):
        p1 = polygon[i]
        p2 = polygon[(i + 1) % len(polygon)]
        dist = point_line_distance(point, (p1, p2))
        if dist < min_distance:
            min_distance = dist
            closest_edge = (p1, p2)
    return closest_edge

# 각 다각형의 점들에 대해 다른 다각형의 선분 중 최소 거리를 가진 선분을 찾고 그 정보를 저장
def find_tangent_lines(polygon1, polygon2):
    tangent_lines = []
    for point in polygon1:
        closest_edge = closest_polygon_edge_from_point(point, polygon2)
        tangent_lines.append((*closest_edge, point))
    for point in polygon2:
        closest_edge = closest_polygon_edge_from_point(point, polygon1)
        tangent_lines.append((*closest_edge, point))
    return tangent_lines

# 접선을 구하는 함수 실행
tangent_lines = find_tangent_lines(polygon1, polygon2)

# 결과를 그래프로 표시
plt.figure(figsize=(10,10))
plt.plot(polygon1[:,0], polygon1[:,1], 'o-') # 다각형 1을 그린다
plt.plot(polygon2[:,0], polygon2[:,1], 'o-') # 다각형 2를 그린다
for line in tangent_lines:
    p1, p2, point = line
    plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'k--', lw=1) # 선분을 그린다
    plt.plot([point[0], (p1[0] + p2[0]) / 2], [point[1], (p1[1] + p2[1]) / 2], 'r--', lw=2) # 점에서 선분 중간까지 접선을 그린다

plt.grid(True)
plt.show()
