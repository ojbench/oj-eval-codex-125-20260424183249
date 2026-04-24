#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }
};

struct FastScanner {
    static const int SZ = 1 << 20;
    int idx = 0, size = 0;
    char buf[SZ];
    inline char gc() {
        if (idx >= size) {
            size = (int)fread(buf, 1, SZ, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }
    template<typename T>
    bool readInt(T &out) {
        char c = gc();
        if (!c) return false;
        long long sign = 1, x = 0;
        while (c != '-' && (c < '0' || c > '9')) { c = gc(); if (!c) return false; }
        if (c == '-') { sign = -1; c = gc(); }
        for (; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c - '0');
        out = (T)(x * sign);
        return true;
    }
} in;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!in.readInt(T)) return 0;
    string out;
    out.reserve((size_t)T * 4);
    while (T--) {
        int n; in.readInt(n);
        vector<pair<long long,long long>> neq; neq.reserve(n);
        unordered_map<long long,int> id;
        id.reserve((size_t)min(1<<20, max(8, n*2)));
        id.max_load_factor(0.7f);
        auto gid = [&](long long x) -> int {
            auto it = id.find(x);
            if (it != id.end()) return it->second;
            int k = (int)id.size();
            id.emplace(x, k);
            return k;
        };
        vector<pair<int,int>> eq; eq.reserve(n);
        bool early_no = false;
        for (int i = 0; i < n; ++i) {
            long long a, b; int e;
            in.readInt(a); in.readInt(b); in.readInt(e);
            if (e == 1) {
                int ia = gid(a), ib = gid(b);
                eq.emplace_back(ia, ib);
            } else {
                if (a == b) early_no = true;
                neq.emplace_back(a, b);
            }
        }
        if (early_no) { out += "NO\n"; continue; }
        DSU d; d.init((int)max(1u, (unsigned)id.size()));
        for (auto &p : eq) d.unite(p.first, p.second);
        bool ok = true;
        for (auto &p : neq) {
            auto ia = id.find(p.first), ib = id.find(p.second);
            if (ia == id.end() || ib == id.end()) continue;
            if (d.find(ia->second) == d.find(ib->second)) { ok = false; break; }
        }
        out += ok ? "YES\n" : "NO\n";
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
