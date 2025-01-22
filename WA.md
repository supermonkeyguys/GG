# 错题集

## [E. Replace the Numbers]([Problem - 1620E - Codeforces](https://codeforces.com/problemset/problem/1620/E))

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 5 * 1e5 + 10;

vector<int>t(N) , x(N) , y(N);

int main()
{
    int q;
    cin >> q;

    for(int i = 0 ; i < q ; i ++ ){
        cin >> t[i];
        if(t[i] == 1)cin >> x[i];
        else cin >> x[i] >> y[i];
    }

    vector<int>pp(N);
    iota(pp.begin(),pp.end(),0);
    vector<int>ans;

    for(int i = q - 1 ; i >= 0 ; -- i ){
        if(t[i] == 1)ans.push_back(pp[x[i]]);
        else pp[x[i]] = pp[y[i]];
    }

    reverse(ans.begin(),ans.end());

    for(int i = 0 ; i < ans.size() ; i ++ )printf("%d ",ans[i]);

    return 0;
}
```



## [[CQOI2009]中位数图]([[CQOI2009\]中位数图](https://ac.nowcoder.com/acm/problem/19913))

```c++
//思路：注意题目上说的奇数连续子序列包括1个，只取它自己；找中位数，就是要取出的序列排序后它刚好在最中间，我们可以忽略具体数值，将比中位数大的数存为1，比它小的存为-1，因为是序列，无重复数据，再记录下中位数的位置，求出后缀和，前缀和；取出的子序列有三种情况，中位数向左取或向右取，或者两边都含有，1.前缀和为零+2.后缀和为零+3.（前缀和+后缀和=0）就是符合要求的子序列；
#include<iostream>
using namespace std;
const int N = 1e5 + 10 , M = 2 * N;

int a[N];
int num[M];

int main()
{
    int n,b;
    cin >> n >> b;
    int mid = 0;

    for(int i = 1 ; i <= n ; i ++ ){
        cin >> a[i];
        if(a[i] > b)a[i] = 1;
        else if(a[i] < b)a[i] = -1;
        else mid = i;
    }

    int sum = 0 , ans = 1;
    for(int i = mid - 1 ; i >= 1 ; i -- ){
        sum += a[i];
        if(sum == 0)ans ++ ;
        num[n - sum] ++ ;
    }
    sum = 0;
    for(int i = mid + 1 ; i <= n ; i ++ ){
        sum += a[i];
        if(sum == 0)ans ++ ;
        ans += num[n + sum];
    }

    cout << ans << endl;

    return 0;
}
```



## [二分(bushi)](https://ac.nowcoder.com/acm/problem/207053)

```c++
#include<iostream>
#include<map>
#include<climits>
using namespace std;
const int M = INT_MAX , N = INT_MIN;

map<int,int>mp;

int main()
{
    int n;
    cin >> n;
    for(int i = 1 ;i <= n ; i ++ ){
        int a;
        char s;
        cin >> a >> s;
        if(s == '.')mp[a] ++ , mp[a + 1] -- ;
        else if(s == '+')mp[N] ++ , mp[a] -- ;
        else if(s == '-')mp[a + 1] ++ , mp[M] --;
    }

    int sum = 0 , ans = 0;
    for(auto i : mp){
        sum += i.second;
        ans = max(ans,sum);
    }

    cout << ans << endl;

    return 0;
}
```



## [丢手绢]([丢手绢](https://ac.nowcoder.com/acm/problem/207040))

```c++
//取尺法(双指针)
#include<iostream>
using namespace std;
#define int long long
const int N = 1e5 + 10;

int a[N] , n;

signed main()
{
    cin >> n;
    int sum = 0;

    for(int i = 1 ; i <= n ; i ++ ){
        cin >> a[i];
        sum += a[i];
    }

    int ans = 0 , cur = 0;

    // 我们可以使用两个指针l和r来表示当前考虑的两个小朋友之间的距离(cur)。
    // 我们可以让指针l从1开始遍历数组，并让指针r从l开始向右移动，
    // 直到找到一个位置k，使得从l到k和从k到l+n（n是数组长度）之间的距离最大。
    // 然后，我们可以更新答案(ans)，并将指针l向右移动一位。重复这个过程直到遍历完整个数组。
    int l = 1;
    for(int r = 1 ; r <= n ; r ++ ){
        cur += a[r];
        if(cur * 2 <= sum) ans = max(ans,cur);
        while(cur * 2 > sum){
            ans = max(ans,sum - cur);
            cur -= a[l ++ ];
        }

    }

    cout << ans;

    return 0;
}
```



## [[SCOI2005]扫雷MINE]([[SCOI2005\]扫雷MINE](https://ac.nowcoder.com/acm/problem/20241))

![image-20241223194132069](C:\Users\30959\AppData\Roaming\Typora\typora-user-images\image-20241223194132069.png)

```c++
#include<iostream>
using namespace std;
const int N = 1e4 + 10;

int n;
int a[N];
int f[N];

bool pd(){
    for(int i = 2 ; i <= n ; i ++ ){
        f[i] = a[i - 1] - f[i - 1] - f[i - 2];
        //一个位置只能有一个雷
        if(f[i] > 1 || f[i] < 0)return false;
    }
    //只能判断到n-1个的a的条件，所以最后一个要特判
    if(a[n] == f[n] + f[n - 1])return true;
    else return false;
}

int main()
{

    cin >> n;
    for(int i = 1 ; i <= n ; i ++ )cin >> a[i];
	//假设两种情况往后枚举
    int ans = 0;
    //假如第一个格子没地雷
    f[1] = 0;
    if(pd()) ans ++ ;
    //第一个格子有地雷
    f[1] = 1;
    if(pd()) ans ++ ;

    cout << ans << endl;

    return 0;
}
```



## [矩阵消除游戏]([矩阵消除游戏](https://ac.nowcoder.com/acm/problem/200190))

```c++
#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;
const int N = 20;

int sum , n , m , k , cnt;
int a[N][N];
int line[N];
//用来计算选中的行数
int pp(int x){
    int sump = 0;
    for(int i = 1 ; i <= n ; i ++ ){
        //看每一位的数 例： n = 4 , 00001010 , 2,4行选中 , 开始(i == 0) (1010 >> 0) & 1
        //最后一位为0 不选
        //下一次为 (1010 >> 1) --> 101 & 1
        //最后一位为1 选中
        if(((x >> (i - 1)) & 1) == 1){
            cnt ++ ;//选中数+1
            for(int j = 1 ; j <= m ; j ++ )sump += a[i][j]; //把这行加入
        }
        else {
            //把没有被选中的行，其中的每列都计算一下
            //因为没有选中这行 所以把这行的值 分别加到列的之中
            for(int j = 1 ; j <= m ; j ++ )line[j] += a[i][j];
        }
    }
    return sump;
}

int main()
{
    cin >> n >> m >> k;

    for(int i = 1 ; i <= n ; i ++ ){
        for(int j = 1 ; j <= m ; j ++ ){
            cin >> a[i][j];
            sum += a[i][j];
        }
    }

    //可以全部选
    if(k >= m || k >= n){
        cout << sum;
        return 0;
    }

    int ans = 0;
    //把所有行的方法枚举一遍 假设有n行 就是n^2种可能
    //把数字转换成二进制(8 --> 00000100) 0代表当行不选 1代表当行选中
    //从0开始枚举
    for(int i = 0 ; i <= ((1 << n) - 1) ; i ++ ){
        cnt = 0; //cnt代表选中的行数个数
        memset(line,0,sizeof line);
        sum = pp(i);
        //剩下的可选个数
        int rest = k - cnt;
        // <0就是选多了 >m就是选少了
        if(rest < 0 || rest > m)continue;
        //对列(已经处理好去重的)的值排序
        sort(line + 1,line + 1 + m,greater<>());
        //加上剩余可选的个数
        for(int j = 1 ; j <= rest ; j ++ )sum += line[j];

        ans = max(ans,sum);
    }

    cout << ans << endl;

    return 0;
}
```



## [区间连续plus]([华华听月月唱歌](https://ac.nowcoder.com/acm/problem/23036))

```c++
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10;

struct pp{
    int l;
    int r;
};

pp qr[N];

bool cmp(pp p1,pp p2){
    if(p1.l == p2.l)return p1.r > p2.r;
    return p1.l < p2.l;
}

int main(){

    int len,n;
    cin >> len >> n;

    for(int i = 1 ; i <= n ; i ++ ){
        cin >> qr[i].l >> qr[i].r;
    }

    sort(qr + 1,qr + 1 + n,cmp);
    if(qr[1].l > 1){
        cout << -1 << endl;
        return 0;
    }

    int cnt = 0;
    int r = 0;
    int last = 0;//起点
    int i = 0;
    while(last < len){
        while(i <= n && qr[i].l <= last + 1){
            r = max(r,qr[i].r);
            i ++ ;
        }
        if(r > last){
            last = r;
            cnt ++ ;
        }
        else break;
    }

    if(last == len)cout << cnt << endl;
    else cout << -1 << endl;

    return 0;
}
```



## [二分查找区间]([牛可乐和魔法封印](https://ac.nowcoder.com/acm/problem/235558))

```c++
#include<iostream>
using namespace std;
const int N = 1e5 + 10;

int a[N];
int n;

int find_l(int x){
    int l = 1;
    int r = n;
    while(l < r){
        int mid = (l + r) / 2;
        if(a[mid] >= x)r = mid;
        else l = mid + 1;
    }
    return l;
}

int find_r(int y){
    int l = 1;
    int r = n;
    while(l < r){
        int mid = (l + r + 1) / 2;
        if(a[mid] <= y)l = mid;
        else r = mid - 1;
    }
    return r;
}

int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++ )cin >> a[i];

    int q;
    cin >> q;
    while(q -- ){
        int x,y;
        cin >> x >> y;
        //防止找不到的情况 比如数组为： 5 6 7 8 9
        //但要找3 4区间 最后查找结果区间为 L=1，R=1
        //显然不对 所以进行一个特判
        if(x > a[n] || y < a[1]){
            cout << 0 << endl;
            continue;
        }
        int L = find_l(x);
        int R = find_r(y);
        cout << R - L + 1 << endl;
    }

    return 0;
}
```

## [晒衣服](https://ac.nowcoder.com/acm/problem/235254)

```c++
#include<iostream>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int a[N];
int n,k;

bool pp(ll x){
    ll t = 0;
    for(int i = 1 ; i <= n ; i ++ ){
        if(k == 1 && a[i] > x)return false;
        if(a[i] <= x)continue;
        //当衣服含水量大于 x 时，计算烘干这件衣服需要使用散热器的次数，计算公式 (a[i] - x - 1) / (k - 1) + 1 采用了向上取整的方式（先减去自然晾干 x 分钟对应的水量，然后除以 k - 1 再加上 1），将得到的次数累加到 t 中。
        t += (a[i] - x - 1) / (k - 1) + 1;
    }
    //最后检查累计使用散热器的次数 t 是否小于等于假设的烘干时间 x，如果是，则返回 true，表示在 x 分钟内可以烘干所有衣服；否则返回 false
    if(t <= x)return true;
    return false;
}


int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i ++ )cin >> a[i];
    cin >> k;

    ll l = 0;
    ll r = 1e9 + 10;
    while(l < r){
        ll mid = (l + r) / 2;
        if(pp(mid))r = mid;
        else l = mid + 1;
    }

    cout << l << endl;

    return 0;
}
```

### 为什么要是k - 1

我们的目标是计算烘干一件含水量为 `a[i]` 的衣服，在已经自然晾干 `x` 分钟（也就是已经减少了 `x` 单位的水）后，还需要使用散热器烘干的次数。

假设剩余需要烘干的水量为 `water`（即 `water = a[i] - x`），而散热器每分钟能减少 `k` 单位的水。

正常情况下，如果 `water` 刚好是 `k` 的整数倍，比如 `water = 3k`，那显然需要使用散热器的次数就是 `water / k`（也就是 `3` 次）。

但当 `water` 不是 `k` 的整数倍时，比如 `water = 3k + 2`（这里 `2 < k`），按照实际烘干的逻辑，这剩下的 `2` 单位水也需要再用散热器烘一次，也就是总共需要 `4` 次才能烘干完这件衣服，即需要向上取整。

### 代码实现取整的方式

在代码里采用了一种巧妙的数学技巧来实现向上取整。通过 `(water - 1) / (k - 1)`（这里 `water = a[i] - x`）来达到目的，具体推导如下：

我们可以把除法运算 `a / b`（向上取整）等价转换为 `(a + b - 1) / b`（这里 `a` 是被除数，`b` 是除数，且 `b > 0`）。

在计算烘干次数时，把需要烘干的剩余水量 `water` 当作被除数，`k` 当作除数，也就是要计算 `water / k`（向上取整），按照上述等价转换规则，就变成了 `(water + k - 1) / k`，进一步变形为 `((a[i] - x) + k - 1) / k`，展开括号后就是 `(a[i] - x - 1) / (k - 1) + 1`（这里先对分子部分 `(a[i] - x + k - 1)` 变形为 `(a[i] - x - 1 + k)`，然后分别除以 `k` 就得到了 `(a[i] - x - 1) / (k - 1) + 1`）。

所以，这里 `k` 减 `1` 配合整个表达式的计算逻辑，是为了准确地计算出烘干一件衣服在剩余一定水量时需要使用散热器的向上取整后的次数，以符合实际烘干过程中哪怕剩余水量不足 `k` 单位也需要再用一次散热器烘干的情况。

## [货币系统(背包)](https://ac.nowcoder.com/acm/problem/21467)

```c++
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 110 , M = 1e6 + 10;

int main()
{
    int T;
    cin >> T;

    while( T -- ){
        int n;
        //f表示面值能否表达 0代表不能 1代表可以
        int f[M] = {0};
        int a[N] = {0};
        cin >> n;
        for(int i = 1 ; i <= n ; i ++ )cin >> a[i];
        sort(a + 1 , a + 1 + n);
        //面值为0 为1 可以表达
        f[0] = 1;

        int ans = 0;

        for(int i = 1 ; i <= n ; i ++ ){
            //如果不能被表达 答案+1
            if(f[a[i]] == 0) ans ++ ;
            for(int j = a[i] ; j <= a[n] ; j ++ ){
                //从当前面值开始 看有没有可以被表达的 假如a[1] = 3 , a[n] = 19 , 一一向上遍历
                //假如j遍历到8 就代表
                //目前8是不是已近可以被表达 或者 可以用当前面值a[1](3) + 5(8 - a[1](3))来凑成
                f[j] = max(f[j],f[j - a[i]]);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
```



## [DongDong认亲戚](https://ac.nowcoder.com/acm/problem/23803)

```c++
//2025.1.14
#include<iostream>
#include<map>
using namespace std;
const int N = 2 * 1e4 + 10;

int f[N];
map<string,int>name;

int find(int x){
    if(f[x] != x)f[x] = find(f[x]);
    return f[x];
}


int main()
{
    int n,m;
    cin >> n >> m;

    for(int i = 1 ; i <= n ; i ++ ){
        f[i] = i;
        string a;
        cin >> a;
        name[a] = i;
    }

    while( m -- ){
        string a,b;
        int op = 0;
        cin >> op >> a >> b;
        if(op == 1){
            f[find(name[a])] = find(name[b]);
        }
        else if(op == 2){
            if(find(f[name[a]]) == find(f[name[b]]))cout << 1 << endl;
            else cout << 0 << endl;
        }
    }



    return 0;
}
```



## [[NOI1999]生日蛋糕](https://ac.nowcoder.com/acm/problem/16857)

```c++
//2025.1.14
#include<iostream>
using namespace std;
const int MAX = 0x3f3f3f3f , N = 25;

int ans = MAX;
int minS[N] , minV[N];
int n,m;

void dfs(int now,int r,int h,int s,int v){
    int MaxH = h;
    if(now == 0){
        if(v == n){
            ans = min(ans,s);
        }
        return;
    }
    //如果面积已经大于了目前的最优值ans就可以退出了
    if(s + minS[now - 1] >= ans)return;
    //如果当前搜到的体积已经大于了题目给定的体积就可以退出了
    if(v + minV[now - 1] > n)return;
    //由体积推出的表面积已经大于最大值了就可以退出了
    if(2 * (n - v) / r + s >= ans)return;
    //枚举半径
    for(int i = r - 1 ; i >= now ; i -- ){
        if(now == m) s = i * i;
        MaxH = min(h - 1,(n - minV[now - 1] - v) / i / i);
        //枚举高
        for(int j = MaxH ; j >= now ; j -- ){
            dfs(now - 1 , i , j , s + 2 * i * j , v + i * i * j);
        }
    }
}

int main()
{
    cin >> n >> m;
    //初始化每层成最小的表面积和体积
    for(int i = 1 ; i <= m ; i ++ ){
        minS[i] = minS[i - 1] + 2 * i * i;
        minV[i] = minV[i - 1] + i * i * i;
    }
    dfs(m,n,n,0,0);
    if(ans == MAX)cout << 0 << endl;
    else cout << ans << endl;

    return 0;
}
```



## [数字组合](https://ac.nowcoder.com/acm/problem/235260)

```c++
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 1e3 + 10;

ll a[N] , b[N] , c[N] , d[N];
ll ab[N * N] , cd[N * N];

int main()
{
    int n;
    cin >> n;

    for(int i = 1 ; i <= n ; i ++ ){
        cin >> a[i];
        cin >> b[i];
        cin >> c[i];
        cin >> d[i];
    }

    int index_ab = 0;
    int index_cd = 0;
    for(int i = 1 ; i <= n ; i ++ ){
        for(int j = 1 ; j <= n ; j ++ ){
            ab[++index_ab] = a[i] + b[j];
            cd[++index_cd] = c[i] + d[j];
        }
    }
    sort(cd + 1 , cd + 1 + index_cd);
    ll cnt = 0;
    for(int i = 1 ; i <= index_ab ; i ++ ){
//        int l = 1;
//        int r = index_cd;
//        while(l < r){
//            int mid = (l + r) / 2;
//            if(cd[mid] >= -ab[i])r = mid;
//            else l = mid + 1;
//        }
//        int L = l;
//        l = 1 , r = index_cd;
//        while(l < r){
//            int mid = (l + r + 1) / 2;
////            cout << mid << endl;
//            if(cd[mid] <= -ab[i])l = mid;
//            else r = mid - 1;
//        }
//        int R = r;
//        cnt += R - L + 1;
        ll* L = lower_bound(cd + 1, cd + 1 + index_cd, -ab[i]);
        ll* R = upper_bound(cd + 1, cd + 1 + index_cd, -ab[i]);
        cnt += R - L;
    }

    cout << cnt << endl;

    return 0;
}
```



## [数值膨胀之美](https://ac.nowcoder.com/acm/contest/95323/M)

```c++
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10;
typedef pair<int,int>pp;

pp a[N];
int b[N];

int main()
{
    int n;
    cin >> n;

    for(int i = 1 ; i <= n ; i ++ ){
        cin >> a[i].first;
        a[i].second = i;
        b[i] = a[i].first;
    }

    sort(a + 1,a + 1 + n);
    a[n + 1].first = 0x3f3f3f3f;
    //最小值的编号 最大值的编号
    int l = a[1].second , r = a[1].second;

    int mx = max(a[1].first * 2,a[n].first);

    int res = mx - min(a[1].first * 2,a[2].first);

    for(int i = 2 ; i <= n ; i ++ ){
        while(l > a[i].second){
            l -- ;
            mx = max(mx,b[l] * 2);
        }
        while(r < a[i].second){
            r ++ ;
            mx = max(mx,b[r] * 2);
        }

        res = min(res,mx - min(a[1].first * 2,a[i + 1].first));

    }

    cout << res << endl;

    return 0;
}
```



## [一气贯通之刃](https://ac.nowcoder.com/acm/contest/95323/B)

```c++
#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int>q(n + 1);

    for(int i = 0 ; i < n - 1 ; i ++ ){
        int a,b;
        cin >> a >> b;
        q[a] ++ ;
        q[b] ++ ;
    }

    int cnt =  0;
    int head , tail;
    for(int i = 1 ; i <= n ; i ++ ){
        if(q[i] == 1){
            cnt ++ ;
            if(cnt == 1)head = i;
            else if(cnt == 2) tail = i;
        }
        else if(q[i] > 2){
            cout << -1 << endl;
            return 0;
        }
    }

    cout << head << ' ' << tail << endl;

    return 0;
}
//欧拉图结论
//对于一个无向图
//遍历所有点的最简单路径
//必须保证 每个点的度数(每个点连的条线个数)
//奇数点只能有0个 或者 2个(起点和终点)
//中间点的度数 只能是偶数2( 一进一出 -- 最简单路径)
//如果为奇数(假如3) 那就代表除一进一出外 还有一条边 构成了一个环
```

