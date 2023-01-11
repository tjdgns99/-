#include <stdio.h>
#include <stdlib.h>

//���׽� polynomial
#define MAX_DEGREE 101
typedef struct {
	int degree;				//���׽� ����
	float coef[MAX_DEGREE];	//���׽� ���
}polynomial;

polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;

	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree) { //Apos�� ���׽� A�� �������� �۰� Bpos�� ���׽� B�� �������� ������ �ݺ�
		if (degree_a > degree_b) { //���� A�� ������ ���� B�� �������� ũ��
			C.coef[Cpos++] = A.coef[Apos++]; //C�� ���� ū ������ ����� A�� ���� ū ������ ���, ���� ������ ���ϱ� ���� plus
			degree_a--; //���� ������ �񱳸� ���� degree_a�� �ϳ� ���̳ʽ�
		}
		else if (degree_a == degree_b) { //���� A�� ������ B�� ������ ������ 
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++]; //C�� ���� ������ ����� A�� B�� ���� ������ ����� ��
			degree_a--; //�������� �Ѿ������ ���̳ʽ�
			degree_b--; //�������� �Ѿ������ ���̳ʽ�
		}
		else { //���� A�� ������ B�� �������� ������
			C.coef[Cpos++] = B.coef[Bpos]; //C�� ���� ������ ����� B�� ���� ������ ���
			degree_b--; //���� ������ �񱳸� ���� degree_b�� �ϳ� ���̳ʽ�
		}
	}

	return C; //���� ���׽� C�� ��ȯ
}
//0�� �ƴ� ����� ���� �׸� ǥ���ϴ� ���
#define MAX_TERMS 101
struct {
	float coef;
	int expon;
} terms[MAX_TERMS] = { { 8, 3 }, { 7, 1 }, { 1, 0 }, { 10, 3 }, { 3, 2 }, { 1, 0 } };
//8X^3 + 7X^1 + 1, 10X^3 + 3X^2 + 1 �� ���� ���� �� 
int avail = 6; //�迭�� �ε��� 0~5���� 2�� ���׽��� �������Ƿ� ���� �ε��� 6
char compare(int a, int b) { //a�� b�� ���Ͽ� ��ȣ�� ǥ���ϴ� �Լ�
	if (a > b)
		return '>';
	else if (a == b)
		return '=';
	else
		return '<';
}
void attach(float coef, int expon) { //���׽��� �߰��ϴ� �Լ�
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}
void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
	//As�� A ���׽��� ���� �ε���, Ae�� ������ �ε��� �������� ��������
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be) {//A�� B���׽��� �Ѵ� ������ �ʾ����� �ݺ�
		switch (compare(terms[As].expon, terms[Bs].expon)) { //A�� B�� ������ ��
		case '>': //���� A�� ������ B���� ũ��
			attach(terms[As].coef, terms[As].expon); //����� A�� ���� ����̰� ������ ���� ������ �迭�� ����
			As++; //���� ������ �̵�
			break; //����
		case '=': //���� A�� ������ B�� ������ ������
			tempcoef = terms[As].coef + terms[Bs].coef; //�� ���׽��� ����� ���� ����
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++;
			Bs++;
			break;
		case '<': //���� A�� ������ B�� �������� ������
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
		for (; As < Ae; As++) { //A�� ���� ���������� �̾� ���̱�
			attatch(terms[As].coef, terms[As].expon);
		}
		for (; Bs < Be; Bs++) { //B�� ���� ���������� �̾� ���̱�
			attach(terms[Bs].coef, terms[Bs].expon);
		}

		*Ce = avail - 1;
	}
}

//������ �������� 2���� �迭�� Ȱ���� ���
#define ROWS 3 //�� ����
#define COLS 3 //�� ����
void sparse_matrix_add1(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) {
	int r, c;
	for (r = 0; r < ROWS; r++) {
		for (c = 0; c < COLS; c++) {
			C[r][c] = A[r][c] + B[r][c];
		}
	}
}

//������ 0�� �ƴ� ��Ҹ��� (��, ��, ��)���� ��Ÿ���� ���
#define ROWS 3 //�� ����
#define COLS 3 //�� ����
#define MAX_TERMS 10
typedef struct {
	int row; //��
	int col; //��
	int value; //��
}element;
typedef struct SparseMatrix { //���
	element data[MAX_TERMS]; //(��, ��, ��)�� �迭
	int rows; //�� ����
	int cols; //�� ����
	int terms;//���� ����
}SparseMatrix;
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b) {
	SparseMatrix c;
	int ca = 0, cb = 0, cc = 0;
	if (a.rows != b.rows || a.cols != b.cols) {
		fprintf(stderr, "������ ũ�⿡��\n");
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