# [Codeforces Round 900 (Div. 3)](https://codeforces.com/contest/1878)

## 概述

- 通过：ABCDE
- 补题：FG

## 题解

### [F. Vasilije Loves Number Theory](https://codeforces.com/contest/1878/problem/F)

- 若 $n = p_1^{a_1}p_2^{a_2}\dots p_k^{a_k}$ ，则显然有 $d(n) = (a_1 + 1)(a_2 + 1)\dots(a_k + 1)$ 。
- 能整除 $n$ 的元素实际上就是使用 $n$ 的质因数可以组合出多少个不同的数，而每个数字中每个质因数的数目可以是 $0, 1, \dots, a_i$ ，共 $a_i + 1$ 种选择。
- 若 $\gcd(a, n) = 1$ 说明没有相同的素因数，那么显然有 $d(an) = d(a)d(n)$，这是一个积性函数。因此 $d(an) = n$ 的条件是 $d(n) \mid n$。
- 对于本题，由于 $n \cdot x$ 没有大小上限，可能会非常大，因此并不能维护 $n \cdot x$ 的大小。$x \mid y$ 其实等价于对于每一个质因数 $p_i$ 有 $a_{ix} \leq a_{iy}$，所以我们只需要维护质因数分解的结果即可。
  - 提示：$xy = p_1^{a_{1x}+a_{1y}} \dots$


```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T &a)
{
    T s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        s = (s << 1) + (s << 3) + (c ^ 48);
        c = getchar();
    }
    a = s * w;
}
const int N= 1e6 + 5;
int minp[N],prime[N];
//欧拉筛预处理用于质因数分解
void init_prim()
{
    for (int i = 2; i < N; i++)
        minp[i] = i;
    int cnt = 0;
    for (int i = 2; i < N; i++)
    {
        if (minp[i] == i)
            prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i < N; j++)
        {
            minp[prime[j] * i] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
}
//获取质因数分解结果
unordered_map<int,int> cal_prim(int num){
    unordered_map<int,int> res;
    for(int i=2;i<sqrt(num)&&num>=N;i++){
        while(num%i==0){
            res[i]++;
            num/=i;
        }
    }
    if(num>=N){
        res[num]++;
        return res;
    }
    while (num != 1)
    {
        int p = minp[num];
        res[p]++;
        if(p==0)
            cout<<"!!!";
        num /= p;
    }
    return res;
}
//计算d(n)
int cal_d(unordered_map<int,int>&mp){
    int res=1;
    for(auto&a:mp)
        res*=(a.second+1);
    return res;
}
int main()
{
    int t;
    init_prim();
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        unordered_map<int,int>mp=cal_prim(n);
        while (q--)
        {
            int t;
            bool state=true;
            read(t);
            //重置
            if (t == 2)
                mp=cal_prim(n);
            else
            {
                int x;
                read(x);
                //维护n的质因数分解
                auto tmp=cal_prim(x);
                for(auto&a:tmp)
                    mp[a.first]+=a.second;
                //计算并分解d(n)
                int d=cal_d(mp);
                auto tmp2=cal_prim(d);
                for(auto&a:tmp2){
                    if(mp[a.first]<a.second){
                        state=false;
                        cout<<"NO"<<endl;
                        break;
                    }
                }
                if(state)
                    cout<<"YES"<<endl;
            }
        }
    }
    return 0;
}
```

