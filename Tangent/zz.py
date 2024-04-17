import matplotlib.pyplot as plt

# 세 세트의 점들
points1 = [(-12588, 10), (-3430, 10), (10196, 2259), (10196, 36608), (-11422, 36608), (-12588, 27456)]
points2 = [(-12588, -36608), (-3430, -36608), (10196, -34359), (10196, -10), (-11422, -10), (-12588, -9162)]
points3 = [(-12588, -36608), (-3430, -36608), (10196, -34359), (10196, 36608), (-11422, 36608), (-12588, 27456)]

# 폐쇄된 형태로 만들기 위해 각 세트에 첫 번째 점을 추가
points1.append(points1[0])
points2.append(points2[0])
points3.append(points3[0])

# 그래프 생성
plt.figure(figsize=(10, 8))

# 도형 1 그리기
x_values, y_values = zip(*points1)
plt.plot(x_values, y_values, marker='o', linestyle='-', color='blue', label='Shape 1')

# 도형 2 그리기
x_values, y_values = zip(*points2)
plt.plot(x_values, y_values, marker='o', linestyle='-', color='green', label='Shape 2')

# 도형 3 그리기
x_values, y_values = zip(*points3)
plt.plot(x_values, y_values, marker='o', linestyle='-', color='red', label='Shape 3')

plt.title('Three Closed Shapes')
plt.xlabel('X Coordinate')
plt.ylabel('Y Coordinate')
plt.legend()
plt.grid(True)

plt.show()
