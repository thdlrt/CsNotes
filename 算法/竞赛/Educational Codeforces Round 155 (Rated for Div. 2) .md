# [Educational Codeforces Round 155 (Rated for Div. 2)](https://codeforces.com/contest/1879)

## 概述

- 通过：ABC
- 补题：DF

## 题解

### [D. Sum of XOR Functions](https://codeforces.com/contest/1879/problem/D)

- 拆位运算，计算每一位的贡献值
  - 首先预处理处[1,i]上的异或$a_i$
- 从左到有开始遍历，并对每一位进行合统计。
  - 先看较为简单的计算$\sum_{l=1}^n\sum_{r=l}^nf(l,r)$，对于$a_i$为1的某一位，其与前面元素构成的子区间的贡献就是$a_0\dots a_{i-1}$中该位0出现的次数；$a_i$为0时同理。
  
    - 实际区间的异或值$f(l,r)$是$a_r\bigoplus a_{l-1}$，因此只要就是要寻找特定位与$a_r$不同的$a_{l-1}$的数目
  
  - 再看题目要求的 $\sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1)$，我们可以用两个数组分别记录
  
    - ```c++
      c[j][a[i]>>j&1]++;
      s[j][a[i]>>j&a]+=i;
      ```
  
  - 这样$i*c-s$就能得到结果

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353,N=3e5+5;
int n,a[N];
ll s[30][2],c[30][2];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]^=a[i-1];
    }
    ll ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<30;j++){
            ans+=c[j][!(a[i]>>j&1)]*i%mod*(1<<j)%mod;
            ans-=s[j][!(a[i]>>j&1)]*(1<<j)%mod;
            c[j][a[i]>>j&1]++;
            s[j][a[i]>>j&1]=(s[j][a[i]>>j&1]+i)%mod;

        }
    }
    cout<<(ans%mod+mod)%mod;
}
```

### [F. Last Man Standing](https://codeforces.com/contest/1879/problem/F)

- 对于第i个英雄，在攻击力为x下的存货回合数为$h\lceil\frac{a_i}{x}\rceil$
  - 显然对于$\lceil\frac{a_i}{x}\rceil$这一部分，$a_i\to[1,x][x+1,2x]\dots$都具有相同的值，只需要用st表维护区间内h的最大值和次大值即可
  - 在得到的所有区间的最大值和次大值中找出总体的最大值和次大值，做差就能得到结果（注意存储最大值时还要附带英雄的编号，便于确定答案）
- 复杂度约为$O(n(1+\frac12+\dots+\frac1n)logn)$
  - 写的有点差，常数大了，超时了

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>
inline void read(T &a)
{
   T s = 0, w = 1;
   char c = getchar();
   while(c < '0' || c > '9')
   {
       if(c == '-') w = -1;
       c = getchar();
   }
   while(c >= '0' && c <= '9')
   {
       s = (s << 1) + (s << 3) + (c ^ 48);
       c = getchar();
   }
   a = s*w;
}
const ll N=2*1e5+5;
ll n,res[N];
struct node{
    ll a,h,i;
    bool operator<(const node&x)const{
        return a<x.a;
    }
}arr[N];
pair<ll,ll>dp_max[N][20],dp_second_max[N][20];
void st_init() {
    for (ll i = 1; i <= n; i++) {
        dp_max[i][0] = {arr[i].h,arr[i].i};
        dp_second_max[i][0] = {0,0};
    }
    ll p = log2(n);
    for (ll k = 1; k <= p; k++) {
        for (ll s = 1; s + (1 << k) <= n + 1; s++) {
            dp_max[s][k] = max(dp_max[s][k - 1], dp_max[s + (1 << (k - 1))][k - 1]);
            pair<ll,ll> max1 = dp_max[s][k - 1];
            pair<ll,ll> max2 = dp_max[s + (1 << (k - 1))][k - 1];
            pair<ll,ll> min1 = dp_second_max[s][k - 1];
            pair<ll,ll> min2 = dp_second_max[s + (1 << (k - 1))][k - 1];
            if (max1 > max2) {
                dp_second_max[s][k] = max(min1, max2);
            } else {
                dp_second_max[s][k] = max(max1, min2);
            }
        }
    }
}

pair<pair<ll,ll>,pair<ll,ll>> st_query(ll L, ll R) {
    if(L==R)
        return {dp_max[L][0],{0,0}};
    ll k = log2(R - L + 1);
    pair<ll,ll> max1 = dp_max[L][k];
    pair<ll,ll> max2 = dp_max[R - (1 << k) + 1][k];
    pair<ll,ll> min1 = dp_second_max[L][k];
    pair<ll,ll> min2 = dp_second_max[R - (1 << k) + 1][k];
    pair<ll,ll> max_val = max(max1, max2),second_max_val;
    if(max_val==max1){
        if(max_val!=max2){
            second_max_val=max(max2,min1);
        }
        else
            second_max_val=max(min1,min2);
    }
    else{
        second_max_val=max(max1,min2);
    }
    return {max_val,second_max_val};
}
int main(){
    ll t;
    cin>>t;
    while(t--){
        memset(res,0,sizeof(res));
        cin>>n;
        for(ll i=1;i<=n;i++)
            read(arr[i].h);
        for(ll i=1;i<=n;i++)
            read(arr[i].a);
        for(ll i=1;i<=n;i++)
            arr[i].i=i;
        sort(arr+1,arr+n+1);
        st_init();
        ll t=max_element(arr+1,arr+n+1)->a;
        for(ll x=1;x<=t;x++){
            pair<ll,ll>num_max{0,0},num_second_max{0,0};
            ll cnt;
            for(node *l=&arr[1],*r;l<=&arr[n];l=r+1){
                cnt=(l->a+x-1)/x;
                r=upper_bound(l,&arr[n+1],node{cnt*x,0,0})-1;
                ll left=l-&arr[0],right=r-&arr[0];
                auto t=st_query(left,right);
                t.first.first*=cnt;
                t.second.first*=cnt;
                if(t.first>num_max){
                    num_second_max=num_max;
                    num_max=t.first;
                    num_second_max=max(num_second_max,t.second);
                }
                else
                    num_second_max=max(num_second_max,t.first);
            }
                if(num_max.first>num_second_max.first)
                    res[num_max.second]=max(res[num_max.second],num_max.first-num_second_max.first);
        }
        for(ll i=1;i<=n;i++){
            cout<<res[i]<<" ";
        }
        cout<<endl;//
    }
}
```

