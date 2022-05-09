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
	struct vector* new_vector = (struct vector*)malloc(sizeof(struct vector)); // 벡터 공간 생성

	new_vector->size = 0;
	new_vector->capacity = 0; //벡터 크기와 실제 크기 0으로 설정

	return new_vector; // 만든 벡터를 반환
}

struct vector* vector_copy(struct vector* vec) {
	int vsize = vector_size(vec); //벡터 크기 받고
	struct vector* new_vector = vector_create(); // 새로운 벡터 만든 후

	vector_reserve(new_vector, vsize);

	for (int i = 0; i < vsize; i++)
		vector_push_back(new_vector, *vector_at(vec, i)); // 0부터 벡터 크기까지 벡터 값 넣기
														  //new_vector->data = vec->data로 하면 둘다 같은 곳을 지정하게 되기 때문

	return new_vector;
}

void vector_destructor(struct vector* vec) {
	free(vec->data); // 벡터 값을 지우고
	free(vec); // 벡터 머리 부분을 지우기
}

void vector_reserve(struct vector* vec, int capacity) {
	if (vector_capacity(vec) == 0)  //벡터의 실제 크기가 0이라면
		vec->data = (int*)malloc(sizeof(int) * capacity); // 메모리 할당
	else
		vec->data = (int*)realloc(vec->data, sizeof(int) * capacity); // 0이 아니면 다시 할당

	vec->capacity = capacity; // 벡터의 실제 크기를 (바뀌었으므로) 원하는 크기로 설정

	if (vec->size > capacity) //벡터의 크기가 실제 크기를 넘는 경우
		vec->size = capacity; // 벡터의 크기를 실제크기로 설정
}

void vector_resize(struct vector* vec, int size) {
	int vsize = vector_size(vec); // 사이즈 저장
	int vcapacity = vector_capacity(vec); // 실제 크기 저장

	if (vsize < size) { // 새로 정한 크기가 원래 크기보다 클 경우
		int loop_size = size - vsize;

		for (int i = 0; i < loop_size; i++) // 새로 생긴 공간에 0 넣기
			vector_push_back(vec, 0);
	}

	vec->size = size; // 사이즈를 원하는 크기로 설정
}

void vector_shrink(struct vector* vec) {
	vector_reserve(vec, vector_size(vec)); // 벡터의 실제 크기를 조절
}

int vector_size(struct vector* vec) {
	return vec->size; // 사이즈값 반환
}

int vector_capacity(struct vector* vec) {
	return vec->capacity; // 벡터의 실제 크기 반환
}

int vector_empty(struct vector* vec) {
	return vector_size(vec) == 0; // 사이즈가 0일경우 비어있으므로 참
}

int* vector_at(struct vector* vec, int pos) {
	return &vec->data[pos]; // data에서 pos번째 있는 값을 반환
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
	int vsize = vector_size(vec); // 사이즈, 크기 저장
	int vcapacity = vector_capacity(vec);

	if (pos > vcapacity) { // 추가할 위치가 범위를 벗어난다면 작동하지 않음
	}
	else {
		if (vsize == vcapacity) { // 만약 실제 크기와 크기가 같다면 
								  // 더이상 넣을 공간이 없으므로 공간을 만들어 준 후 값을 넣게 됨
			if (vcapacity == 0) { // 크기가 0이면
				vec->data = (int*)malloc(sizeof(int));
				vec->capacity = 1; // 새롭게 만든 후 실제 크기를 1으로 설정
								   // 이 경우 값이 저장되어 있지 않으므로 공간을 만들 필요 없음
			}
			else {
				vec->capacity = vcapacity * 2; // 실제 크기를 2배로 늘림
				vec->data = (int*)realloc(vec->data, sizeof(int) * vector_capacity(vec));

				for (int i = vsize; i > pos; i--) // pos까지 한칸씩 밀어 공간을 만듬
					vec->data[i] = vec->data[i - 1];
			}
		}
		else {
			for (int i = vsize; i > pos; i--) { // pos까지 한칸씩 밀어 공간을 만듬
				vec->data[i] = vec->data[i - 1];
			}
		}

		vec->data[pos] = value; // 값을 원하는 위치에 넣고 사이즈 증가
		vec->size++;
	}
}

void vector_erase(struct vector* vec, int pos) {
	int vsize = vector_size(vec);
	if (pos < vsize) { // 지우고 싶은 위치가 벡터 크기보다 작다면
		int loop_size = vsize - 1;

		for (int i = pos; i < loop_size; i++) // 원하는 위치서부터 뒤의 값을 당겨옴 
			vec->data[i] = vec->data[i + 1];  // 이렇게 하면 pos위치의 값은 덮혀 사라짐

		vec->size--;// 사이즈를 1 줄임
	}
}

void vector_push_back(struct vector* vec, int value) {
	vector_insert(vec, vector_size(vec), value);
}

void vector_pop_back(struct vector* vec) {
	vector_erase(vec, vector_size(vec) - 1);
}

void vector_clear(struct vector* vec) {
	vec->size = 0; // 사이즈를 0으로 초기화
}

void vector_print(struct vector* vec) {
	int vsize = vector_size(vec);

	for (int i = 0; i < vsize; i++)
		printf("%d ", *vector_at(vec, i));
}
