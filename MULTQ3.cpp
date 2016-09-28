#include <bits/stdc++.h>
/*#define HOME true
#define debug(a) if(HOME)cout<<a<<endl;*/

using namespace std;

struct Node{
	int mod0, mod1, mod2;
	Node():mod0(0), mod1(0), mod2(0){};
	Node(int m0, int m1, int m2): mod0(m0), mod1(m1), mod2(m2){};
};

Node tree[4 * 100100];
int lazy[4 * 100100];

void updateNode(int node){
	int aux = tree[node].mod0;
	tree[node].mod0 = tree[node].mod2;
	tree[node].mod2 = tree[node].mod1;
	tree[node].mod1 = aux;
}

Node merge(Node n1, Node n2){
	return Node(n1.mod0 + n2.mod0, n1.mod1 + n2.mod1, n1.mod2 + n2.mod2);
}

void build(int node, int l, int r){
	if(l == r){
		tree[node].mod0 = 1;
		return;
	}
	int mid = (l + r) / 2;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);
	tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

void dolazy(int node, int l, int r){
	if(lazy[node]){
		if(l != r){
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		for(int i = 0; i < (lazy[node] % 3); i++)updateNode(node);
		lazy[node] = 0;
	}
}


int query(int node, int l, int r, int i, int j){
	if(i > r || j < l)return 0;
	dolazy(node, l, r);
	if(l >= i && r <= j)return tree[node].mod0;
	int mid = (l + r) / 2;
	return query(node * 2, l, mid, i, j) + query(node * 2 + 1, mid + 1, r, i, j);
}

void update(int node, int l, int r, int i, int j){
	dolazy(node, l, r);
	if(i > r || j < l)return;
	if(l >= i && r <= j){
		lazy[node]++;
		dolazy(node, l, r);
		return;
	}
	int mid = (l + r) / 2;
	update(node * 2, l, mid, i, j);
	update(node * 2 + 1, mid + 1, r, i, j);
	tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

main(){
	int n, q, i, j, com;
	scanf("%d %d", &n, &q);
	build(1, 1, n);
	while(q--){
		scanf("%d %d %d", &com, &i, &j);
		i++; j++;
		if(com){
			printf("%d\n", query(1, 1, n, i, j));
		}else{
			update(1, 1, n, i, j);
		}
	}
}