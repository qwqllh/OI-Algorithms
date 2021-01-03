#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 4e6 + 5;
int rev[maxn];

struct Complex {
    double x, y;
    Complex(double x = 0.0, double y = 0.0): x(x), y(y) {}

    Complex operator + (const Complex &rhs) {
        return Complex(this->x + rhs.x, this->y + rhs.y);
    }
    Complex operator - (const Complex &rhs) {
        return Complex(this->x - rhs.x, this->y - rhs.y);
    }
    Complex operator * (const Complex &rhs) {
        return Complex(this->x * rhs.x - this->y * rhs.y, this->x * rhs.y + this->y * rhs.x);
    }
    Complex operator / (const double rhs) {
        return Complex(this->x / rhs, this->y / rhs);
    }
};

void change(Complex y[], int len) {
    for (int i = 0; i < len; i++) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1)
            rev[i] |= len >> 1;
    }
    for (int i = 0; i < len; i++) {
        if (i < rev[i])
            swap(y[i], y[rev[i]]);
    }
}

void FFT(Complex y[], int len, int on) {
    change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2 * M_PI / h), sin(on * 2 * M_PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i].x /= len;
        }
    }
}

int n, m, limit;
Complex a[maxn], b[maxn];

int main() {
    scanf("%d%d", &n, &m);
    limit = 1;
    // 因为这个fft板子默认长度是取不到len的，所以limit应该大于n + m。
    while (limit <= n + m) limit <<= 1;

    for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);

    FFT(a, limit, 1);
    FFT(b, limit, 1);

    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i];
    
    FFT(a, limit, -1);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", (int)(a[i].x + 0.5));
    return 0;
}