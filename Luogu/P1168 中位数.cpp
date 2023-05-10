#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, less<int> > p;
priority_queue<int, vector<int>, greater<int> > q;

int tp, tq;

int n;
int a;

int main(){
	cin >> n;
	
	cin >> a;
	
	p.push(a);
	tp ++;
	
	cout << a << endl;
	
	for (int i = 2; i <= n; i ++){
		cin >> a;
		
		if (a > p.top()){
			q.push(a);
			tq ++;
		}else{
			p.push(a);
			tp ++;
		}
		
		if (abs(tq - tp) > 1){
			if (tq > tp){
				p.push(q.top());
				q.pop();
				tp ++;
				tq --;
			}else{
				q.push(p.top());
				p.pop();
				tq ++;
				tp --;
			}
		}
		
		if (i & 1){
			if (q.size() > p.size()){
				cout << q.top() << endl;
			}else{
				cout << p.top() << endl;
			}
		}
	}
	
	return 0;
}