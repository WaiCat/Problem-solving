#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <stack>
using namespace std;
FILE *input_fp, *output_fp;
typedef struct node {
  int x, y;
  int numbering;
  int index;
} node_p;
node_p polygon[2][20001];
node_p list[20001];
node_p pr[20001];
node_p calcDelArea[3][20001];
int compare(const void* a, const void* b) {
  if ((*(node_p*)a).x - (*(node_p*)b).x == 0)
    return (*(node_p*)a).y - (*(node_p*)b).y;
  return (*(node_p*)a).x - (*(node_p*)b).x;
}
long long distance(node_p a, node_p b) {
  return ((long long)a.x - b.x) * ((long long)a.x - b.x) +
         ((long long)a.y - b.y) * ((long long)a.y - b.y);
}
long long ccw2(node_p p, node_p q, node_p r) {
  node_p vp = {p.x - r.x, p.y - r.y};
  node_p vq = {q.x - r.x, q.y - r.y};
  long long a = (long long)vp.x * vq.y;
  long long b = (long long)vq.x * vp.y;
  return a - b;
}
int ccw(node_p p, node_p q, node_p r) {
  node_p vp = {p.x - r.x, p.y - r.y};
  node_p vq = {q.x - r.x, q.y - r.y};
  long long a = (long long)vp.x * vq.y;
  long long b = (long long)vq.x * vp.y;
  if (a > b) {
    return 1;
  } else if (a == b) {
    return 0;
  }
  return -1;
}

long long getDist(node_p a, node_p b) {
  return ((long long)a.x - b.x) * ((long long)a.x - b.x) +
         ((long long)a.y - b.y) * ((long long)a.y - b.y);
}
int isBetween(node_p a, node_p b, node_p c) {
  if (ccw(a, b, c)) {
    return 0;
  }
  if (a.x != b.x) {
    if (b.x < a.x) {
      return a.x >= c.x && c.x >= b.x ? 1 : 0;
    } else {
      return a.x <= c.x && c.x <= b.x ? 1 : 0;
      ;
    }
  } else {
    if (b.y < a.y) {
      return a.y >= c.y && c.y >= b.y ? 1 : 0;
      ;
    } else {
      return a.y <= c.y && c.y <= b.y ? 1 : 0;
      ;
    }
  }
}
long long calcArea(int pNum, int qNum, int prNum) {
  int pPoints[2] = {0};
  int qPoints[2] = {0};
  int prIndex[2][2] = {0};
  int idx = 0;
  for (int i = 0; i < prNum; i++) {
    if (pr[i].numbering != pr[(i + 1) % prNum].numbering) {
      if (pr[i].numbering == 0) {
        pPoints[idx] = pr[i].index;
        qPoints[idx] = pr[(i + 1) % prNum].index;

        prIndex[0][idx] = i;
        prIndex[1][idx] = (i + 1) % prNum;
        idx++;
      } else {
        qPoints[idx] = pr[i].index;
        pPoints[idx] = pr[(i + 1) % prNum].index;

        prIndex[0][idx] = (i + 1) % prNum;
        prIndex[1][idx] = i;
        idx++;
      }
    }
  }

  for (int i = 0; i < pNum + qNum; i++) {
    if (list[i].numbering > 0) {
      if (isBetween(polygon[0][pPoints[0]], polygon[1][qPoints[0]],
                    list[i])) {  // list[]��  p0, q0������ ���̸�
        if (distance(polygon[0][pPoints[0]], polygon[1][qPoints[0]]) >
            distance(polygon[0][pPoints[0]], list[i]))  // �Ÿ��� �� ������
          qPoints[0] = list[i].index;
      }
    } else {
      if (isBetween(polygon[0][pPoints[0]], polygon[1][qPoints[0]], list[i])) {
        if (distance(polygon[0][pPoints[0]], polygon[1][qPoints[0]]) >
            distance(polygon[1][qPoints[0]], list[i]))
          pPoints[0] = list[i].index;
      }
    }
  }
  for (int i = 0; i < pNum + qNum; i++) {
    if (list[i].numbering > 0) {
      if (isBetween(polygon[0][pPoints[1]], polygon[1][qPoints[1]], list[i])) {
        if (distance(polygon[0][pPoints[1]], polygon[1][qPoints[1]]) >
            distance(polygon[0][pPoints[1]], list[i]))
          qPoints[1] = list[i].index;
      }
    } else {
      if (isBetween(polygon[0][pPoints[1]], polygon[1][qPoints[1]], list[i])) {
        if (distance(polygon[0][pPoints[1]], polygon[1][qPoints[1]]) >
            distance(polygon[1][qPoints[1]], list[i]))
          pPoints[1] = list[i].index;
      }
    }
  }

  int tIdx = 0, qIdx = 0, pIdx = 0;
  if (prIndex[0][0] < prIndex[1][0]) {
    calcDelArea[2][tIdx++] = polygon[0][pPoints[0]];
    for (int i = (pPoints[0] + 1) % pNum; i != pPoints[1]; i = (i + 1) % pNum) {
      calcDelArea[2][tIdx++] = polygon[0][i];
    }

    calcDelArea[2][tIdx++] = polygon[0][pPoints[1]];

    calcDelArea[2][tIdx++] = polygon[1][qPoints[1]];
    for (int i = (qPoints[1] + 1) % qNum; i != qPoints[0]; i = (i + 1) % qNum) {
      calcDelArea[2][tIdx++] = polygon[1][i];
    }

    calcDelArea[2][tIdx++] = polygon[1][qPoints[0]];

  } else {
    calcDelArea[2][tIdx++] = polygon[0][pPoints[1]];
    for (int i = (pPoints[1] + 1) % pNum; i != pPoints[0]; i = (i + 1) % pNum) {
      calcDelArea[2][tIdx++] = polygon[0][i];
    }

    calcDelArea[2][tIdx++] = polygon[0][pPoints[0]];

    calcDelArea[2][tIdx++] = polygon[1][qPoints[0]];
    for (int i = (qPoints[0] + 1) % qNum; i != qPoints[1]; i = (i + 1) % qNum) {
      calcDelArea[2][tIdx++] = polygon[1][i];
    }

    calcDelArea[2][tIdx++] = polygon[1][qPoints[1]];
  }
  long long sum3 = 0;
  for (int i = 0; i < tIdx; i++) {
    sum3 += ccw2(calcDelArea[2][i], calcDelArea[2][(i + 1) % tIdx],
                 calcDelArea[2][2]);
  }
  sum3 = abs(sum3);
  // return sum1 + sum2;
  return sum3;
}
int getConvexHull(int n) {
  stack<node_p> s;
  s.push(list[0]);
  s.push(list[1]);

  int nextIdx = 2;

  while (nextIdx < n) {
    while (s.size() > 1) {
      node_p first, second;
      second = s.top();
      s.pop();
      first = s.top();
      if (ccw(second, list[nextIdx], first) > 0) {
        s.push(second);
        break;
      }
    }

    s.push(list[nextIdx]);
    nextIdx++;
  }

  stack<node_p> s2;
  s2.push(list[0]);
  s2.push(list[1]);

  nextIdx = 2;

  while (nextIdx < n) {
    while (s2.size() > 1) {
      node_p first, second;
      second = s2.top();
      s2.pop();
      first = s2.top();
      if (ccw(list[nextIdx], second, first) > 0) {
        s2.push(second);
        break;
      }
    }

    s2.push(list[nextIdx]);
    nextIdx++;
  }
  if (s2.top().x == s.top().x && s2.top().y == s.top().y) {
    s2.pop();
  }

  int idx = s.size();
  for (int i = s.size() - 1; i >= 0; i--) {
    pr[i] = s.top();
    s.pop();
  }
  for (int i = s2.size(); i > 1; i--) {
    pr[idx++] = s2.top();
    s2.pop();
  }
  return idx;
}
int main() {
  input_fp = fopen("3.inp", "r");
  output_fp = fopen("3.txt", "w");
  FILE* xyfp = fopen("test.out", "w");
  int n;
  fscanf(input_fp, "%d", &n);
  for (int i = 0; i < n; i++) {
    int idx = 0;
    int pNum, qNum;
    fscanf(input_fp, "%d", &pNum);
    for (int j = 0; j < pNum; j++) {
      fscanf(input_fp, "%d %d", &list[idx].x, &list[idx].y);
      list[idx].numbering = 0;
      list[idx].index = j;
      polygon[0][j].numbering = 0;
      polygon[0][j].x = list[idx].x;
      polygon[0][j].y = list[idx].y;
      polygon[0][j].index = j;
      idx++;
    }
    fscanf(input_fp, "%d", &qNum);
    for (int j = 0; j < qNum; j++) {
      fscanf(input_fp, "%d %d", &list[idx].x, &list[idx].y);
      list[idx].numbering = 1;
      list[idx].index = j;
      polygon[1][j].numbering = 1;
      polygon[1][j].x = list[idx].x;
      polygon[1][j].y = list[idx].y;
      polygon[1][j].index = j;
      idx++;
    }

    for (int i = 0; i < pNum; i++) {
      fprintf(xyfp, "%d, ", polygon[0][i].x);
    }
    fprintf(xyfp, "\n");
    for (int i = 0; i < pNum; i++) {
      fprintf(xyfp, "%d, ", polygon[0][i].y);
    }
    fprintf(xyfp, "\n");
    for (int i = 0; i < qNum; i++) {
      fprintf(xyfp, "%d, ", polygon[1][i].x);
    }
    fprintf(xyfp, "\n");
    for (int i = 0; i < qNum; i++) {
      fprintf(xyfp, "%d, ", polygon[1][i].y);
    }
    fprintf(xyfp, "\n");
    qsort(list, pNum + qNum, sizeof(node_p), compare);
    int pridx = getConvexHull(idx);
    long long sum = 0;
    for (int i = 0; i < pridx; i++) {
      sum += ccw2(pr[i % pridx], pr[(i + 1) % pridx], pr[0]);
    }
    sum = abs(sum);
    long long temp = calcArea(pNum, qNum, pridx);
    /*sum -= temp;
    fprintf(output_fp, "%.1lf\n", (double)sum / 2);*/
    fprintf(output_fp, "%.1lf\n", (double)temp / 2);
  }

  fclose(input_fp);
  fclose(output_fp);
  return 0;
}
