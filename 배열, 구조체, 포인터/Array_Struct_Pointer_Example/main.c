#include <stdio.h>
#include <stdlib.h>

//다항식 polynomial
#define MAX_DEGREE 101
typedef struct {
	int degree;				//다항식 차수
	float coef[MAX_DEGREE];	//다항식 계수
}polynomial;

polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;

	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree) { //Apos가 다항식 A의 차수보다 작고 Bpos가 다항식 B의 차수보다 작으면 반복
		if (degree_a > degree_b) { //현재 A의 차수가 현재 B의 차수보다 크면
			C.coef[Cpos++] = A.coef[Apos++]; //C의 가장 큰 차수의 계수는 A의 가장 큰 차수의 계수, 다음 차수를 구하기 위해 plus
			degree_a--; //다음 차수로 비교를 위해 degree_a를 하나 마이너스
		}
		else if (degree_a == degree_b) { //현재 A의 차수와 B의 차수가 같으면 
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++]; //C의 현재 차수의 계수는 A와 B의 현재 차수의 계수의 합
			degree_a--; //다음으로 넘어가기위한 마이너스
			degree_b--; //다음으로 넘어가기위한 마이너스
		}
		else { //현재 A의 차수가 B의 차수보다 작으면
			C.coef[Cpos++] = B.coef[Bpos]; //C의 현재 차수의 계수는 B의 현재 차수의 계수
			degree_b--; //다음 차수로 비교를 위해 degree_b를 하나 마이너스
		}
	}

	return C; //계산된 다항식 C를 반환
}
//0이 아닌 계수를 갖는 항만 표현하는 방법
#define MAX_TERMS 101
struct {
	float coef;
	int expon;
} terms[MAX_TERMS] = { { 8, 3 }, { 7, 1 }, { 1, 0 }, { 10, 3 }, { 3, 2 }, { 1, 0 } };
//8X^3 + 7X^1 + 1, 10X^3 + 3X^2 + 1 두 개의 다항 식 
int avail = 6; //배열의 인덱스 0~5까지 2개 다항식이 들어가있으므로 다음 인덱스 6
char compare(int a, int b) { //a와 b를 비교하여 등호로 표현하는 함수
	if (a > b)
		return '>';
	else if (a == b)
		return '=';
	else
		return '<';
}
void attach(float coef, int expon) { //다항식을 추가하는 함수
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}
void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	//As는 A 다항식의 시작 인덱스, Ae는 마지막 인덱스 나머지도 마찬가지
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be) {//A와 B다항식이 둘다 끝나지 않았으면 반복
		switch (compare(terms[As].expon, terms[Bs].expon)) { //A와 B의 차수를 비교
		case '>': //현재 A의 차수가 B보다 크면
			attach(terms[As].coef, terms[As].expon); //계수가 A의 현재 계수이고 차수도 현재 차수로 배열에 저장
			As++; //다음 차수로 이동
			break; //종료
		case '=': //현재 A의 차수와 B의 차수가 같으면
			tempcoef = terms[As].coef + terms[Bs].coef; //두 다항식의 계수의 합을 저장
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++;
			Bs++;
			break;
		case '<': //현재 A의 차수가 B의 차수보다 작으면
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
		for (; As < Ae; As++) { //A의 항이 남아있으면 이어 붙이기
			attatch(terms[As].coef, terms[As].expon);
		}
		for (; Bs < Be; Bs++) { //B의 항이 남아있으면 이어 붙이기
			attach(terms[Bs].coef, terms[Bs].expon);
		}

		*Ce = avail - 1;
	}
}

//희소행렬 전통적인 2차원 배열을 활용한 방법
#define ROWS 3 //행 개수
#define COLS 3 //열 개수
void sparse_matrix_add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) {
	int r, c;
	for (r = 0; r < ROWS; r++) {
		for (c = 0; c < COLS; c++) {
			C[r][c] = A[r][c] + B[r][c];
		}
	}
}

//희소행렬 0이 아닌 요소만을 (행, 열, 값)으로 나타내는 방법
#define ROWS 3 //행 개수
#define COLS 3 //열 개수
#define MAX_TERMS 10
typedef struct {
	int row; //행
	int col; //열
	int value; //값
}element;
typedef struct SparseMatrix { //행렬
	element data[MAX_TERMS]; //(행, 열, 값)의 배열
	int rows; //행 개수
	int cols; //열 개수
	int terms;//항의 개수
}SparseMatrix;
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0;
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "희소행렬 크기에러\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;

	while (ca < a.terms && cb < b.terms) {
		int inda = a.data[ca].row * a.cols + a.data[ca].col;
		int indb = b.data[cb].row * b.cols + b.data[cb].col;
		if (inda < indb) {
			c.data[cc++] = a.data[ca++];
		}
		else if (inda == indb) {
			if ((a.data[ca].value + b.data[cb].value) != 0) {
				c.data[cc].row = a.data[ca].row;
				c.data[cc].col = a.data[ca].col;
				c.data[cc].value = a.data[ca++].value + b.data[cb++].value;
			}
			else {
				ca++;
				cb++;
			}
		}
		else {
			c.data[cc++] = b.data[cb++];
		}
	}
	for (; ca < a.terms;) {
		c.data[cc++] = a.data[ca++];
	}
	for (; cb < b.terms;) {
		c.data[cc++] = b.data[cb++];
	}
	c.terms = cc;
	return c;
}

int main() {
	polynomial a = { 5, {10, 0, 0, 0, 6, 3} };
	//a = 10X^5 + 6X + 3
	polynomial b = { 4, {7, 0, 5, 0, 1} };
	polynomial c = poly_add1(a, b);

	int Cs, Ce;
	poly_add2(0, 2, 3, 5, &Cs, &Ce);

	int array1[ROWS][COLS] = { {2, 3, 0}, {8, 9, 1}, {7, 0, 5} };
	int array2[ROWS][COLS] = { {1, 0, 0}, {1, 0, 0}, {1, 0, 0} };
	int array3[ROWS][COLS];
	sparse_matrix_add1(array1, array2, array3);

	SparseMatrix m1 = { { {1, 1, 5}, {2, 2, 9} }, 3, 3, 2 };
	SparseMatrix m2 = { { {0, 0, 5}, {2, 2, 9} }, 3, 3, 2 };
	SparseMatrix m3;
	m3 = sparse_matrix_add2(m1, m2);


	
}