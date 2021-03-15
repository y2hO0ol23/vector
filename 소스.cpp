#include <stdio.h>
#include <stdlib.h>

struct vector {
	int* data;
	int size;
	int capacity;
};

struct vector* vector_create();
struct vector* vector_copy(struct vector* vec);
void vector_destructor(struct vector* vec);
void vector_reserve(struct vector* vec, int capacity);
void vector_resize(struct vector* vec, int size);
void vector_shrink(struct vector* vec);

int vector_size(struct vector* vec);
int vector_capacity(struct vector* vec);
int vector_empty(struct vector* vec);

int* vector_at(struct vector* vec, int pos);
int* vector_front(struct vector* vec);
int* vector_back(struct vector* vec);
void vector_swap(struct vector* vec, int lhs, int rhs);

void vector_insert(struct vector* vec, int pos, int value);
void vector_push_back(struct vector* vec, int value);
void vector_erase(struct vector* vec, int pos);
void vector_pop_back(struct vector* vec);
void vector_clear(struct vector* vec);

void vector_print(struct vector* vec);

int main() {

	vector *vecUp = vector_create();
	vector* vecDown = vector_create();

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		vector_insert(vecDown, 0, t);
		vector_push_back(vecUp, t);
	}
	vector_print(vecDown);
	printf("\n");
	vector_print(vecUp);

	vector_destructor(vecUp);
	vector_destructor(vecDown);

	return 0;
}

struct vector* vector_create() {
	struct vector* new_vector = (struct vector*)malloc(sizeof(struct vector)); // ���� ���� ����

	new_vector->size = 0;
	new_vector->capacity = 0; //���� ũ��� ���� ũ�� 0���� ����

	return new_vector; // ���� ���͸� ��ȯ
}

struct vector* vector_copy(struct vector* vec) {
	int vsize = vector_size(vec); //���� ũ�� �ް�
	struct vector* new_vector = vector_create(); // ���ο� ���� ���� ��

	vector_reserve(new_vector, vsize);

	for (int i = 0; i < vsize; i++)
		vector_push_back(new_vector, *vector_at(vec, i)); // 0���� ���� ũ����� ���� �� �ֱ�
														  //new_vector->data = vec->data�� �ϸ� �Ѵ� ���� ���� �����ϰ� �Ǳ� ����

	return new_vector;
}

void vector_destructor(struct vector* vec) {
	free(vec->data); // ���� ���� �����
	free(vec); // ���� �Ӹ� �κ��� �����
}

void vector_reserve(struct vector* vec, int capacity) {
	if (vector_capacity(vec) == 0)  //������ ���� ũ�Ⱑ 0�̶��
		vec->data = (int*)malloc(sizeof(int) * capacity); // �޸� �Ҵ�
	else
		vec->data = (int*)realloc(vec->data, sizeof(int) * capacity); // 0�� �ƴϸ� �ٽ� �Ҵ�

	vec->capacity = capacity; // ������ ���� ũ�⸦ (�ٲ�����Ƿ�) ���ϴ� ũ��� ����

	if (vec->size > capacity) //������ ũ�Ⱑ ���� ũ�⸦ �Ѵ� ���
		vec->size = capacity; // ������ ũ�⸦ ����ũ��� ����
}

void vector_resize(struct vector* vec, int size) {
	int vsize = vector_size(vec); // ������ ����
	int vcapacity = vector_capacity(vec); // ���� ũ�� ����

	if (vsize < size) { // ���� ���� ũ�Ⱑ ���� ũ�⺸�� Ŭ ���
		int loop_size = size - vsize;

		for (int i = 0; i < loop_size; i++) // ���� ���� ������ 0 �ֱ�
			vector_push_back(vec, 0);
	}

	vec->size = size; // ����� ���ϴ� ũ��� ����
}

void vector_shrink(struct vector* vec) {
	vector_reserve(vec, vector_size(vec)); // ������ ���� ũ�⸦ ����
}

int vector_size(struct vector* vec) {
	return vec->size; // ����� ��ȯ
}

int vector_capacity(struct vector* vec) {
	return vec->capacity; // ������ ���� ũ�� ��ȯ
}

int vector_empty(struct vector* vec) {
	return vector_size(vec) == 0; // ����� 0�ϰ�� ��������Ƿ� ��
}

int* vector_at(struct vector* vec, int pos) {
	return &vec->data[pos]; // data���� pos��° �ִ� ���� ��ȯ
}

int* vector_front(struct vector* vec) {
	return vector_at(vec, 0);
}

int* vector_back(struct vector* vec) {
	return vector_at(vec, vector_size(vec) - 1);
}

void vector_swap(struct vector* vec, int lhs, int rhs) {
	int temp;
	temp = *vector_at(vec, lhs);
	*vector_at(vec, lhs) = *vector_at(vec, rhs);
	*vector_at(vec, rhs) = temp;
}

void vector_insert(struct vector* vec, int pos, int value) {
	int vsize = vector_size(vec); // ������, ũ�� ����
	int vcapacity = vector_capacity(vec);

	if (pos > vcapacity) { // �߰��� ��ġ�� ������ ����ٸ� �۵����� ����
	}
	else {
		if (vsize == vcapacity) { // ���� ���� ũ��� ũ�Ⱑ ���ٸ� 
								  // ���̻� ���� ������ �����Ƿ� ������ ����� �� �� ���� �ְ� ��
			if (vcapacity == 0) { // ũ�Ⱑ 0�̸�
				vec->data = (int*)malloc(sizeof(int));
				vec->capacity = 1; // ���Ӱ� ���� �� ���� ũ�⸦ 1���� ����
								   // �� ��� ���� ����Ǿ� ���� �����Ƿ� ������ ���� �ʿ� ����
			}
			else {
				vec->capacity = vcapacity * 2; // ���� ũ�⸦ 2��� �ø�
				vec->data = (int*)realloc(vec->data, sizeof(int) * vector_capacity(vec));

				for (int i = vsize; i > pos; i--) // pos���� ��ĭ�� �о� ������ ����
					vec->data[i] = vec->data[i - 1];
			}
		}
		else {
			for (int i = vsize; i > pos; i--) { // pos���� ��ĭ�� �о� ������ ����
				vec->data[i] = vec->data[i - 1];
			}
		}

		vec->data[pos] = value; // ���� ���ϴ� ��ġ�� �ְ� ������ ����
		vec->size++;
	}
}

void vector_erase(struct vector* vec, int pos) {
	int vsize = vector_size(vec);
	if (pos < vsize) { // ����� ���� ��ġ�� ���� ũ�⺸�� �۴ٸ�
		int loop_size = vsize - 1;

		for (int i = pos; i < loop_size; i++) // ���ϴ� ��ġ������ ���� ���� ��ܿ� 
			vec->data[i] = vec->data[i + 1];  // �̷��� �ϸ� pos��ġ�� ���� ���� �����

		vec->size--;// ����� 1 ����
	}
}

void vector_push_back(struct vector* vec, int value) {
	vector_insert(vec, vector_size(vec), value);
}

void vector_pop_back(struct vector* vec) {
	vector_erase(vec, vector_size(vec) - 1);
}

void vector_clear(struct vector* vec) {
	vec->size = 0; // ����� 0���� �ʱ�ȭ
}

void vector_print(struct vector* vec) {
	int vsize = vector_size(vec);

	for (int i = 0; i < vsize; i++)
		printf("%d ", *vector_at(vec, i));
}