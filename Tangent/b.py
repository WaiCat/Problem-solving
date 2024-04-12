import matplotlib.pyplot as plt

# 주어진 점들

polygon1 = [
    (10196, 2259) ,
(10196, 10283) ,
(0, 10283) ,
(0, 8071) ,
(-1152, 8071) ,
(-1152, 15988) ,
(0, 15988) ,
(0, 13755) ,
(10196, 13755) ,
(10196, 17124) ,
(-1152, 17124) ,
(-1152, 19486) ,
(5643, 19486) ,
(5643, 21773) ,
(10196, 21773) ,
(10196, 36608) ,
(3316, 36608) ,
(3316, 21773) ,
(4515, 21773) ,
(4515, 20594) ,
(2253, 20594) ,
(2253, 29685) ,
(-2336, 29685) ,
(-2336, 30847) ,
(-1152, 30847) ,
(-1152, 36608) ,
(-11422, 36608) ,
(-11422, 30847) ,
(-3430, 30847) ,
(-3430, 27456) ,
(-12588, 27456) ,
(-12588, 21773) ,
(0, 21773) ,
(0, 27456) ,
(-2336, 27456) ,
(-2336, 28559) ,
(1080, 28559) ,
(1080, 20594) ,
(-4578, 20594) ,
(-4578, 18253) ,
(-12588, 18253) ,
(-12588, -18365) ,
(-12588, -36608) ,
(-3430, -36608) ,
(-3430, -17132) ,
(-2336, -17132) ,
(-2336, -29726) ,
(0, -29726) ,
(0, -34359) ,
(10196, -34359)
]

polygon2 = [
    (-12588, 18253) ,
(-12588, 10) ,
(-3430, 10) ,
(-3430, 19486) ,
(-2336, 19486) ,
(-2336, 6892) ,
(0, 6892) ,
(0, 2259) ,
(10196, 2259) ,
(10196, -34359) ,
(10196, -26335) ,
(0, -26335) ,
(0, -28547) ,
(-1152, -28547) ,
(-1152, -20630) ,
(0, -20630) ,
(0, -22863) ,
(10196, -22863) ,
(10196, -19494) ,
(-1152, -19494) ,
(-1152, -17132) ,
(5643, -17132) ,
(5643, -14845) ,
(10196, -14845) ,
(10196, -10) ,
(3316, -10) ,
(3316, -14845) ,
(4515, -14845) ,
(4515, -16024) ,
(2253, -16024) ,
(2253, -6933) ,
(-2336, -6933) ,
(-2336, -5771) ,
(-1152, -5771) ,
(-1152, -10) ,
(-11422, -10) ,
(-11422, -5771) ,
(-3430, -5771) ,
(-3430, -9162) ,
(-12588, -9162) ,
(-12588, -14845) ,
(0, -14845) ,
(0, -9162) ,
(-2336, -9162) ,
(-2336, -8059) ,
(1080, -8059) ,
(1080, -16024) ,
(-4578, -16024) ,
(-4578, -18365) ,
(-12588, -18365) ,
]

# X와 Y 좌표 추출
x_coords1, y_coords1 = zip(*polygon1)  # 각 좌표를 별도의 리스트로 분리

# 다각형을 닫기 위해 시작점을 다시 추가
x_coords1 += (x_coords1[0],)
y_coords1 += (y_coords1[0],)

x_coords2, y_coords2 = zip(*polygon2)  # 각 좌표를 별도의 리스트로 분리

# 다각형을 닫기 위해 시작점을 다시 추가
x_coords2 += (x_coords2[0],)
y_coords2 += (y_coords2[0],)


# 그래프 생성
plt.figure()
# plt.plot(x_coords1, y_coords1, marker='o')  # 선과 점으로 다각형 표시
# plt.fill(x_coords1, y_coords1, 'b', alpha=0.3)  # 다각형 내부 채우기
plt.plot(x_coords2, y_coords2, marker='o')  # 선과 점으로 다각형 표시
plt.fill(x_coords2, y_coords2, 'b', alpha=0.3)  # 다각형 내부 채우기

# 축에 라벨 추가
plt.xlabel('X coordinate')
plt.ylabel('Y coordinate')
plt.title('Polygon Represented by Tangent1')
plt.grid(True)  # 그리드 표시
plt.axis('equal')  # 각 축의 스케일을 동일하게 설정

# 그래프 표시
plt.show()