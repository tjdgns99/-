#include <stdio.h>

int main() {

	return 0;
}

//이 연산을 수행하게 되면 n이 1이 될 때까지 자신을 계속해서 호출하며 연산이 수행
int factorial(int n) {
	if (n < 1) return 1;
	else return (n * factorial(n - 1));
}

//반복적인 거듭 제곱 계산
double slow_power(double x, int n) {
	int i;
	double r = 1.0;
	for (i = 0; i < n; i++) {
		r = r * x;
	}
	return r;
}
//순환적인 거듭 제곱 계산
double r_slow_power(double x, int n) {
	if (n == 1) return x;
	else return(x * r_slow_power(x, n - 1));
}

//반복적인 피보나치 수열의 계산
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
//순환적인 피보나치 수열의 계산
int r_fib(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return(r_fib(n - 1) + r_fib(n - 2));
}