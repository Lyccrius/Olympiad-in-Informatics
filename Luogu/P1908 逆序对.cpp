#include <iostream>

using namespace std;

int n;

long long a[500005];
long long t[500005];

long long cnt;

void sort(long long l, long long r){
	if (l >= r){
		return ;
	}
	
	long long mid = l + (r-l)/2;
	
	sort(l, mid);
	sort(mid+1, r);
	
	long long q = l, p = mid+1, i = l;
	
	while (p <= r && q <= mid){
		if (p > r || q <= mid && a[q] <= a[p]){
			t[i++] = a[q++];
		}else{
			t[i++] = a[p++];
			cnt += mid - q + 1;
		}
	}
	
	while (q <= mid){
		t[i++] = a[q++];
	}
	
	while (p <= r){
		t[i++] = a[p++];
	}
	
	for (long long i = l; i <= r; i ++){
		a[i] = t[i];
	}
	
	return ;
}

int main(){
	cin >> n;
	
	for (long long i = 1; i <= n; i ++){
		cin >> a[i];
	}
	
	sort(1, n);
	
	cout << cnt << endl;
	
	return 0;
}