#include <stdio.h>

int main() {

	return 0;
}

//�� ������ �����ϰ� �Ǹ� n�� 1�� �� ������ �ڽ��� ����ؼ� ȣ���ϸ� ������ ����
int factorial(int n) {
	if (n < 1) return 1;
	else return (n * factorial(n - 1));
}

//�ݺ����� �ŵ� ���� ���
double slow_power(double x, int n) {
	int i;
	double r = 1.0;
	for (i = 0; i < n; i++) {
		r = r * x;
	}
	return r;
}
//��ȯ���� �ŵ� ���� ���
double r_slow_power(double x, int n) {
	if (n == 1) return x;
	else return(x * r_slow_power(x, n - 1));
}

//�ݺ����� �Ǻ���ġ ������ ���
int fib(int n) {
	if (n < 2) return n;
	else {
		int i, tmp, current = 1, last = 0;
		for (i = 2; i <= n; i++) {
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
	}
}
//��ȯ���� �Ǻ���ġ ������ ���
int r_fib(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return(r_fib(n - 1) + r_fib(n - 2));
}