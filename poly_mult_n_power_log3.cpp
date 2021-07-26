//note -input polynomials are  generated randomly.

#include<bits/stdc++.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define mod 1000000007
#define  pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef  long double ld;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi >vvi;
typedef vector<ll> vll;
typedef vector<vll >vvll;

ll n, m;
ll maximumdegree = 10;    //can adjust the maximum degrees  of n and m by changing max_degree.
ll large_num = 1000000;   //controls maximum value of coefficients in A(x) and B(x).
vll result(1111111), a(1001), b(1001);



void print_poly(vll& a, ll deg) {//given  a polynomial A(x),prints A(x)

	for (ll i = 0; i < deg; i++)cout << a[i] << "*x^" << i << "+ ";
	cout << a[deg] << "*x^" << deg << "\n";
}

void build_poly(vll& a, ll st, ll en, vll& result) {//given a polynomial A,can build A0 and A1 and stores in result

	for (ll i = st; i <= st + en; i++)result[i - st] = a[i];
}

void poly_add(vll& a, vll& b, ll deg, ll bias1, ll bias2, vll& result) {//computes A(x)*x^k1+B(x)*x^k2 and stores in result

	for (ll i = 0; i <= deg; i++) {
		result[i] = (i - bias1 >= 0 ? a[i - bias1] : 0) + (i - bias2 >= 0 ? b[i - bias2] : 0);
	}

}

void self_sub(vll& a, vll& b, ll deg) {//given polynomials A and B,computes A(x)-B(x) and stores it in A(x)

	for (ll i = 0; i <= deg; i++)a[i] -= b[i];
}

void poly_mult(vll& a, vll& b, ll deg, vll& result) {//given polynomials A(x)and B(x),computes A(x)*B(x) and stores in result

	//arrays for storing intermediate results
	vll a0(2 * deg + 1), a1(2 * deg + 1), b0(2 * deg + 1), b1(2 * deg + 1), a0b0(2 * deg + 1), a1b1(2 * deg + 1), a0a1(2 * deg + 1), b0b1(2 * deg + 1), a0b1_a1b0(2 * deg + 1);

	//base cases-->
	if (deg == 0 || deg == 1) {
		if (deg == 0)result[0] = a[0] * b[0];
		else
			result[0] = a[0] * b[0], result[1] = a[0] * b[1] + a[1] * b[0], result[2] = a[1] * b[1];
		return;
	}

	ll deg_0 = deg / 2 - 1, deg_1 = deg - deg / 2;

	build_poly(a, 0, deg_0, a0); build_poly(b, 0, deg_0, b0);
	build_poly(a, deg_0 + 1, deg_1, a1); build_poly(b, deg_0 + 1, deg_1, b1);

	poly_mult(a0, b0, deg_0, a0b0);    //computes A0*B0,stores in a0b0
	poly_mult(a1, b1, deg_1, a1b1);    //computes A1*B1,stores in a1b1
	poly_add(a0, a1, max(deg_0, deg_1), 0, 0, a0a1);  //computes A0+A1,stores in a0a1
	poly_add(b0, b1, max(deg_0, deg_1), 0, 0, b0b1);  //computes B0+B1,stores in b0b1
	poly_mult(a0a1, b0b1, max(deg_0, deg_1), a0b1_a1b0);  //computes (A0+A1)*(B0+B1),stores in a0b1_a1b0
	self_sub(a0b1_a1b0, a0b0, deg);  //computes [(A0+A1)*(B0+B1)]-[a0b0] (subtraction),stores in a0b1_a1b0
	self_sub(a0b1_a1b0, a1b1, deg);  //computes [(A0+A1)*(B0+B1)-a0b0]-[a1b1](subtraction),stores in a0b1_a1b0

	poly_add(a0b0, a0b1_a1b0, 2ll * deg, 0, deg / 2, result); //computes a0b0 + a0b1_a1b0*x^(n/2),stores in result
	poly_add(result, a1b1, 2ll * deg, 0, 2ll * (deg / 2), result); //computes result + a1b1*x^(2*[n/2]),stores in result

	//finally A(x)*B(x) is stored in result vector

}



int main() {
	IOS;

	srand(time(0));

	n = rand() % maximumdegree + 1, m = rand() % maximumdegree + 1;      //can adjust the maximum egrees  of n and m by changing maximumdegree variable.

	for (ll i = 0; i <= n; i++)a[i] = rand() % 1000000 + 1 ;   //1st polynomial generation
	for (ll i = 0; i <= m; i++)b[i] = rand() % 1000000 + 1;   // 2nd polynomial generation

	cout << "a_polyomial is--->\n"; print_poly(a, n);   //prints A(x)
	cout << "\n";
	cout << "b_polynomial is--->\n"; print_poly(b, m);  //prints B(x)
	cout << "\n";

	poly_mult(a, b, max(n, m), result);    //computes A(x)*B(x),stores in result

	cout << "resultanat polynomial is--->\n";
	print_poly(result, n + m);        //prints A(x)*B(x)
}