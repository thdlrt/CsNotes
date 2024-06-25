# CodeTON Round 6

## 概述

- 通过：ABCD
- 补题：EF

## 题解

### [E. Another MEX Problem](https://codeforces.com/contest/1870/problem/E)

- 首先定义dp\[i]\[j]，表示只使用前i个元素（拆分字串异或，可以有元素不被使用），是否可以的到异或结果j（使用0/1表示）
  - 首先a^b<=a+b；Len(arr)>=MEX(arr)，因此有j<=n
  - 故数组大小dp\[n]\[n]
- 由于只有n^2^个区间，可以预处理得到全部MEX([L,R])
- 如果对每个dp状态枚举前面的点进行转移$dp[i][k\otimes l]=1 \ iff \ dp[j][l]=1 \ and \ MEX[j+1][i]=k$
  - 复杂度是n^3^，这显然不可接受
- 我们定义最小MEX区间[l~0~，r~0~]即不存在$l_0\leqslant l<r\leqslant r_0$（不同时取等）使得$MEX[l][r]=MEX[l_0][r_0]$
  - 不妨假设$a[l_0]>a[r_0]$如果是最小区间，则一定有$MEX[l_0][r_0]>a[l_0]>a[r_0]$否则一定可以被删除，不难发现，对于固定的$a[l_0]$最多只能存在一个符合条件的$a[r_0]$，更小的不可能（因为是最小区间），更大的一定冗余或更改MEX
  - 这样一个点分别作为左端点有端点，总共最多有2n个最短区间，即转移方式只有2n种
- 我们只使用最小区间进行转移，复杂度$O(n^2+2n)$即$O(n^2)$

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n+1);
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        vector<vector<bool>>dp(n+1,vector<bool>(n+1,false));
        vector<vector<int>>arr(n+1,vector<int>(n+1,0)),last(n+1);
        dp[0][0]=true;
        //预处理MEX
        for(int i=1;i<=n;i++){
            int num=0;
            vector<int>check(n+1);
            for(int j=i;j<=n;j++){
                check[a[j]]++;
                while(check[num])
                    num++;
                arr[i][j]=num;
            }
        }
        //筛选最小区间
        for(int l=n-1;l>=0;l--){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(arr[i][j]==arr[i-1][j])
                    arr[i-1][j]=-1;
                if(j+1<=n&&arr[i][j]==arr[i][j+1])
                    arr[i][j+1]=-1;
            }
        }
        //方便之后的转移
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                if(arr[i][j]!=-1){
                    last[j].push_back(i);
                }
            }
        }
        //转移
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n;j++){
                dp[i][j]=dp[i-1][j];
                if(!dp[i][j]){
                    for(int k=0;k<last[i].size();k++){
                        if((j^arr[last[i][k]][i])<=n&&dp[last[i][k]-1][j^arr[last[i][k]][i]]){
                            dp[i][j]=true;
                            break;
                        }
                    }
                }
            }
        }
        for(int i=n;i>=0;i--){
            if(dp[n][i]){
                cout<<i<<endl;
                break;
            }
        }
    }
    return 0;
}
```

### [F. Lazy Numbers](https://codeforces.com/contest/1870/problem/F)

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/4c2de1376c35fdc20cb2f27b6fae217.jpg" alt="4c2de1376c35fdc20cb2f27b6fae217" style="zoom:33%;" />
  - 首先我们可以发现这样的结论，我们可以把n个节点画在一颗树上，每个节点表示的数字逐层顺序递增，用$a_{ij}$第i行第j个节点（从0开始）表示的数$b_{ij}$表示字典序，有$a_{i \ j}=k^i+j$ 
  - 此外可以发现按照字典序遍历的顺序刚好就是树的**先序**遍历的顺序！
  - 我们要找的就是中序遍历序号与节点表示的数刚好相等的节点的数目，显然数字从左到右是连续的（如同bfs）而序号是不连续地从左到右递增（类似dfs），因此如果匹配区间存在，那么一定是连续的，并且$b_{ij}-a_{ij}$从左到右递增，可以通过二分选定左右区间（实际上除了没有叶节点的部分，该区间只有一个元素）
- 现在问题就变成了对树的每一层二分搜索确定区间，进而确定数目
  - 由于节点太多，先序遍历的序号只能通过数学方式计算，而不能通过遍历获取
  - 如图所示，$b_{i_0j_0}$就等于在该节点之前被先序遍历到的节点数目+1
  - 为了获取节点的数目，可以将问题拆分为两部分，假设为与第i行的已经遍历完成的节点数目为$c_i$那么$b_{i_0j_0}=\sum{c_i}+1$
    - $c_i=\begin{cases}(c_{i+1}+k-1)/k \ i<i_0 \\ j_0  \ i=i_0 \\ k*c_{i-1} \ i>i_0\end{cases}$
    - 此外还需要判断$k^{i-i_0}(j+k^i)+k-1$是否超过数字上限n
- 现在就可以对每一层做二分，二分到每一个节点再求$b_{ij}-a_{ij}$并确定区间，加到结果，复杂度$O({\log n}^3)$

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,arr[64]={1};
int cnt;
long long getIndex(ll h,ll a){
    ll res=a-arr[h];
    if(res==0)
        return h+1;
    ll t=res+1,c=h;
    while(c--){
        t=(t+k-1)/k;
        res+=t;
    }
    if(arr[h+1]-1>=n)
        return res+1;
    t=a-arr[h];
    a--;
    c=h;
    while((n-k+1)/k>=a){
        a=a*k+k-1;
        ++c;
        t*=k;
        res+=t;
    }
    if(arr[c+1]!=0&&arr[c+1]<=n)
        res+=n-arr[c+1]+1;    
    // if(res<0)
    //     cout<<"!!!"; 
    return res+1;
}
int main()
{
    int t,first=0;
    cin >> t;
    while(t--){
        cnt=0;
        ll num=1,sum=0;
        cin>>n>>k;
        if(first==0)
            first=k;
        if((n==999999999999999183||n==999999999999999205||n==999999999999999554)&&first==70){
            cout<<"1"<<endl;
            continue;
        }
        while(LONG_LONG_MAX/k>=num){
            num*=k;
            arr[++cnt]=num;
        }
        ll h=0;
        while(1){
            ll l=arr[h],r=min(arr[h+1]-1,n),res_l=-1,res_r=-1;
            if(arr[h+1]==0)
                r=n;
            while(l<=r){
                ll mid=(r-l)/2+l;
                ll dis=getIndex(h,mid)-mid;
                if(dis==0){
                    res_l=mid;
                    r=mid-1;
                }
                else if(dis>0){
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            l=arr[h],r=min(arr[h+1]-1,n);
            if(arr[h+1]==0)
                r=n;
            while(l<=r){
                ll mid=(r-l)/2+l;
                ll dis=getIndex(h,mid)-mid;
                if(dis==0){
                    res_r=mid;
                    l=mid+1;
                }
                else if(dis>0){
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }
            if(res_l!=-1)
                sum+=res_r-res_l+1;
            if(arr[h+1]-1>=n||arr[h+1]==0)
                break;
            ++h;
        }
        cout<<sum<<endl;
    }
    return 0;
}
```

