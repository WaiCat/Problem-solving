import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import ConvexHull
from shapely.geometry import Polygon
from shapely.ops import unary_union

def find_end_tangents(points1, points2):
    # 두 다각형의 Convex Hull 계산
    hull1 = ConvexHull(points1)
    hull2 = ConvexHull(points2)
    
    # Convex Hull의 꼭짓점들
    vertices1 = hull1.points[hull1.vertices]
    vertices2 = hull2.points[hull2.vertices]
    
    # 다각형 1의 가장 먼 두 점
    max_distance1 = 0
    end_points1 = None
    for i in range(len(vertices1)):
        for j in range(i + 1, len(vertices1)):
            distance = np.linalg.norm(vertices1[i] - vertices1[j])
            if distance > max_distance1:
                max_distance1 = distance
                end_points1 = (vertices1[i], vertices1[j])
    
    # 다각형 2의 가장 먼 두 점
    max_distance2 = 0
    end_points2 = None
    for i in range(len(vertices2)):
        for j in range(i + 1, len(vertices2)):
            distance = np.linalg.norm(vertices2[i] - vertices2[j])
            if distance > max_distance2:
                max_distance2 = distance
                end_points2 = (vertices2[i], vertices2[j])
    
    return [(end_points1[0], end_points2[0]), (end_points1[1], end_points2[1])]

# 다각형의 좌표를 이어주는 함수
def connect_endpoints(polygon):
    return np.concatenate((polygon, [polygon[0]]))

# 두 다각형의 좌표
polygon1 = np.array([[12, 12], [12, 23], [5, 7], [6, 8], [10, -3], [22, 5]])
polygon2 = np.array([[26, 10], [29, -4], [28, 16], [32, 25], [25, 20]])

# 시작점과 끝점을 연결
polygon1 = connect_endpoints(polygon1)
polygon2 = connect_endpoints(polygon2)

# 양 끝에 있는 두 접선 찾기
end_tangents = find_end_tangents(polygon1, polygon2)

# 결과를 시각화하여 보여주기
plt.figure()
plt.plot(polygon1[:,0], polygon1[:,1], 'ro-', label='Polygon 1')
plt.plot(polygon2[:,0], polygon2[:,1], 'bo-', label='Polygon 2')
for line in end_tangents:
    plt.plot([line[0][0], line[1][0]], [line[0][1], line[1][1]], 'k--')

# Shapely를 사용하여 두 다각형이 만드는 영역을 색칠
polygon1_shapely = Polygon(polygon1)
polygon2_shapely = Polygon(polygon2)
intersection = polygon1_shapely.intersection(polygon2_shapely)
if intersection.geom_type == 'Polygon':
    x, y = intersection.exterior.xy
    plt.fill(x, y, color='gray', alpha=0.5)
elif intersection.geom_type == 'MultiPolygon':
    for poly in intersection:
        x, y = poly.exterior.xy
        plt.fill(x, y, color='gray', alpha=0.5)

plt.title('End Tangents between two polygons')
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.grid(True)
plt.axis('equal')
plt.show()
