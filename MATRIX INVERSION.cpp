#include <bits/stdc++.h>
using namespace std;
// Function to get cofactor of A[p][q]
void getCofactor(vector<vector<double>> &A, vector<vector<double>> &temp,int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
// Determinant function
double determinant(vector<vector<double>> &A, int n) {
    if (n == 1)
        return A[0][0];
    double det = 0;
    vector<vector<double>> temp(n, vector<double>(n));
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(A, temp, 0, f, n);
        det += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}
// Adjoint = transpose of cofactor matrix
void adjoint(vector<vector<double>> &A, vector<vector<double>> &adj, int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign;
    vector<vector<double>> temp(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(A, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            // adjoint = transpose of cofactor matrix
            adj[j][i] = sign * determinant(temp, n - 1);
        }
    }
}
// Inverse = adj(A) / det(A)
bool inverse(vector<vector<double>> &A, vector<vector<double>> &inv, int n) {
    double det = determinant(A, n);
    if (det == 0) {
        cout << "Matrix is singular so No inverse exists.\n";
        return false;
    }
    vector<vector<double>> adj(n, vector<double>(n));
    adjoint(A, adj, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = adj[i][j] / det;
    return true;
}
int main() {
    int n;
    cout << "Enter number of equations (n): ";
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> inv(n, vector<double>(n));
    vector<double> B(n), X(n);
    cout << "\nEnter coefficient matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
    cout << "\nEnter constant matrix B:\n";
    for (int i = 0; i < n; i++)
        cin >> B[i];
    if (inverse(A, inv, n)) {
        cout << "\nInverse of matrix A:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << fixed << setprecision(4) << inv[i][j] << " ";
            cout << endl;
        }
        // Compute X = A^-1 * B
        for (int i = 0; i < n; i++) {
            X[i] = 0;
            for (int j = 0; j < n; j++)
                X[i] += inv[i][j] * B[j];
        }
        cout << "\nRoots :\n";
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << " = " << fixed << setprecision(4) << X[i] << endl;
    }
    return 0;
}
