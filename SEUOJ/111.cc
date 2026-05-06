#include <iostream>
#include <vector>
using namespace std;

using Matrix = vector<vector<long long>>;
// 矩阵加法
Matrix add(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}
// 矩阵减法
Matrix sub(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// 小规模简单的乘法
Matrix simpleMultiply(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
// 核心递归函数
Matrix strassen(const Matrix& A, const Matrix& B, int n) {
    if (n <= 64) {
        return simpleMultiply(A, B, n);
    }
    int half = n / 2;
    Matrix A11(half, vector<long long>(half));
    Matrix A12(half, vector<long long>(half));
    Matrix A21(half, vector<long long>(half));
    Matrix A22(half, vector<long long>(half));
    Matrix B11(half, vector<long long>(half));
    Matrix B12(half, vector<long long>(half));
    Matrix B21(half, vector<long long>(half));
    Matrix B22(half, vector<long long>(half));

    // 计算 A11、A12、A21、A22、B11、B12、B21、B22
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // 计算 P1、P2、P3、P4、P5、P6、P7
    Matrix P1 = strassen(A11, sub(B12, B22, half), half);
    Matrix P2 = strassen(add(A11, A12, half), B22, half);
    Matrix P3 = strassen(add(A21, A22, half), B11, half);
    Matrix P4 = strassen(A22, sub(B21, B11, half), half);
    Matrix P5 = strassen(add(A11, A22, half), add(B11, B22, half), half);
    Matrix P6 = strassen(sub(A12, A22, half), add(B21, B22, half), half);
    Matrix P7 = strassen(sub(A11, A21, half), add(B11, B12, half), half);

    // 计算 C11、C12、C21、C22
    Matrix C11 = add(sub(add(P5, P4, half), P2, half), P6, half);
    Matrix C12 = add(P1, P2, half);
    Matrix C21 = add(P3, P4, half);
    Matrix C22 = sub(sub(add(P5, P1, half), P3, half), P7, half);

    // 重构出结果矩阵 C
    Matrix C(n, vector<long long>(n));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
    return C;
}

int main() {
    int n;
    cin >> n;

    int m = 1;
    while (m < n) {
        m *= 2;
    }

    Matrix A(m, vector<long long>(m, 0));
    Matrix B(m, vector<long long>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }
    Matrix C = strassen(A, B, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) {
                cout << ' ';
            }
            cout << C[i][j];
        }
        cout << '\n';
    }
    return 0;
}
