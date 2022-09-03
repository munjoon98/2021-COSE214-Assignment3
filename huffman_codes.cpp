#include<iostream>
#include<tuple>
using namespace std;

int num;

class tree {

public:
	int data;
	tree* r;
	tree* l;

	tree() {
		r = NULL;
		l = NULL;
		data = 0;
	}
};

void min_heapify(tree* arr[], int numb, int arra_size) {
	int smallest;
	int l = (numb + 1) * 2;
	int r = (numb + 1) * 2 + 1;
	if (l <= arra_size && arr[l - 1]->data < arr[numb]->data) smallest = l;
	else smallest = numb + 1;
	if (r <= arra_size && arr[r - 1]->data < arr[smallest - 1]->data) smallest = r;
	if (smallest != numb + 1) {
		tree* temp = arr[numb];
		arr[numb] = arr[smallest - 1];
		arr[smallest - 1] = temp;
		min_heapify(arr, smallest - 1, arra_size);
	}
}


void build_min_heap(tree* arr[], int arra_size) {
	for (int i = num / 2 - 1; i >= 0; i--) {
		min_heapify(arr, i, arra_size);
	}
}


class min_priority_queue {
public:
	tree** arra;
	int arra_size = num;

	min_priority_queue(int arr[]) {
		arra = (tree**)malloc(sizeof(tree*) * num);
		for (int i = 0; i < num; i++) {
			arra[i] = (tree*)malloc(sizeof(tree));
			arra[i]->l = NULL;
			arra[i]->r = NULL;
			arra[i]->data = arr[i];
		}
		build_min_heap(arra, arra_size);
	}

	tree* extract_min() {
		if (arra_size < 1) cout << "heap underflow\n";
		tree* min = arra[0];
		arra[0] = arra[arra_size - 1];
		arra_size--;
		min_heapify(arra, 0, arra_size);
		return min;
	}

	void insert(tree* arr) {
		arra_size++;
		arra = (tree**)realloc(arra,sizeof(tree*)*arra_size);
		arra[arra_size - 1] = arr;
		int temp = arra_size - 1;
		while (temp > 0 && arra[(temp + 1) / 2 - 1]->data > arra[temp]->data) {
			tree* temp_2 = arra[(temp + 1) / 2 - 1];
			arra[(temp + 1) / 2 - 1] = arra[temp];
			arra[temp] = temp_2;
			temp = (temp + 1) / 2 - 1;
		}
	}
};

tree* huffman(int arr[]) {

	min_priority_queue qu(arr);

	tree* root;

	for (int i = 0; i < num - 1; i++) {
		tree* t = new tree();
		if (i == num - 2) root = t;
		tree* x;
		tree* y;
		x = qu.extract_min();
		t->l= x;
		y = qu.extract_min();
		t->r = y;
		t->data = t->l->data + t->r->data;
		qu.insert(t);
	}

	return root;
}

void go(tree* node, int ans, string an) {
	if (node->data == ans) {
		cout << an << "\n";
	}
	if (node->l != NULL) go(node->l, ans, an + '0');
	if (node->r != NULL) go(node->r, ans, an + '1');
}

int main() {

	scanf("%d", &num);
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &arr[i]);
	}

	tree* root;

	root = huffman(arr);

	for (int i = 0; i < num; i++) {
		string an = "";
		go(root, arr[i], an);
	}
}
