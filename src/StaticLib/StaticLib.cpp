#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// 2分木の初期化
void initialize(tree* t)
{
	if (t == NULL) return;

	t->root = NULL;
}

static void release_recursive(node* n)
{
	if (n == NULL) return;

	if (n->right) {
		release_recursive(n->right);
		n->right = NULL;
	}

	if (n->left) {
		release_recursive(n->left);
		n->left = NULL;
	}

	free(n);
}

// 使用メモリの全解放
void finalize(tree* t)
{
	if (t == NULL) return;

	release_recursive(t->root);
	t->root = NULL;
}


static node* generate(int key, const char* value)
{
	node* p = (node*)malloc(sizeof(node));

	if (p == NULL) return NULL;

	p->key = key;
	int n = (int)strlen(value);
	memcpy(p->value, value, strlen(value)+1);

	p->left = p->right = NULL;

	return p;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* p = generate(key, value);
	if (p == NULL) return false;// メモリ確保できなかった。

	if (t->root == NULL) {
		t->root = p;
		return true;
	}

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	node* cur = t->root;

	while (1) {
		if (key < cur->key) {
			if (cur->left != NULL) {
				cur = cur->left;
			}
			else {
				cur->left = p;
				return true;
			}
		}
		else if (key > cur->key) {
			if (cur->right != NULL) {
				cur = cur->right;
			}
			else {
				cur->right = p;
				return true;
			}
		}
		else {
			size_t len = (value == NULL) ? 0 : strlen(value);
			if (len > 255) len = 255;
			if (len > 0) memcpy(cur->value, value, len);
			cur->value[len] = '\0';

			free(p);
			return true;
		}
	}
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t == NULL) return NULL;

	const node* cur = t->root;

	while (cur != NULL) {
		if (key < cur->key) {
			cur = cur->left;
		}
		else if (key > cur->key) {
			cur = cur->right;
		}
		else {
			return cur->value;
		}
	}
	return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
static void InOrder(const node* n, void (*func)(const node* p))
{
	if (n == NULL) return;

	InOrder(n->left, func);
	func(n);
	InOrder(n->right, func);
}
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t == NULL || func == NULL) return;
	InOrder(t->root, func);
}