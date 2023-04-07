#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>
#define int long long

mt19937 rnd(20636117);
int MOD = 1e9 + 7;

void print(vvi& v) {
    int n = v.size(), m = v[0].size();
    cout << "------\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char t = ' ';
            if (v[i][j] == 0) t = '.';
            else if (v[i][j] == 1) t = '^';
            else if (v[i][j] == 2) t = '>';
            else if (v[i][j] == 3) t = 'v';
            else if (v[i][j] == 4) t = '<';
            else if (v[i][j] == 5) t = '#';
            else if (v[i][j] == 6) t = '~';
            else if (v[i][j] == 7) t = 'r';
            else if (v[i][j] == 8) t = 'R';
            else if (v[i][j] == 9) t = '*';
            else if (v[i][j] == 10) t = 'f';
            else if (v[i][j] == 11) t = '@';
            cout << t << ' ';
        }
        cout << endl;
    }
}

bool has_finish(vector<vector<int>>& f) {
    int n = f.size(), m = f[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == 10) return 1;
        }
    }
    return 0;
}

pair<int, int> find_player(vector<vector<int>>& f) {
    int n = f.size(), m = f[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] >= 1 && f[i][j] <= 4) return {i, j};
        }
    }
}
pair<int, int> find_player(map<pii, int>& f) {
    for (auto s : f) {
        if (s.second >= 1 && s.second <= 4) {
            return s.first;
        }
    }
}

bool possible(vector<vector<int>> f) {
    set<vector<vector<int>>> was;
    vector<vector<vector<int>>> que;
    que.push_back(f);
    for (int i = 0; i < que.size(); ++i) {
        vector<vector<int>> v = que[i];
        if (!has_finish(v)) return 1;
        if (was.count(v)) continue;
        was.insert(v);
        int n = v.size(), m = v[0].size();
        auto [x, y] = find_player(v);
        { // go left
            bool right_side = v[x][y] == 4;
            bool would_die = 0;
            int yp = y;
            vector<vector<int>> u = v;
            while (yp >= 0 && u[x][yp] != 5) {
                if (u[x][yp] == 6) {
                    would_die = 1;
                    break;
                } else if (u[x][yp] == 10) {
                    u[x][yp] = 0;
                    --yp;
                    break;
                } else if (u[x][yp] == 9 && right_side) {
                    u[x][yp] = 0;
                } else if (u[x][yp] == 7) {
                    u[x][y] = u[x][y] % 4 + 1;
                    right_side = u[x][y] == 4;
                } else if (u[x][yp] == 8) {
                    u[x][y] = u[x][y] - 1;
                    if (!u[x][y]) u[x][y] = 4;
                    right_side = u[x][y] == 4;
                } else if (u[x][yp] == 11) {
                    if (right_side) u[x][yp] = 0;
                    else {
                        would_die = 1;
                        break;
                    }
                }
                --yp;
            }
            if (!would_die && yp + 1 != y) {
                u[x][yp + 1] = u[x][y];
                u[x][y] = 0;
                que.push_back(u);
            }
        }
        { // go down
            bool right_side = v[x][y] == 3;
            bool would_die = 0;
            int xp = x;
            vector<vector<int>> u = v;
            while (xp < n && u[xp][y] != 5) {
                if (u[xp][y] == 6) {
                    would_die = 1;
                    break;
                } else if (u[xp][y] == 10) {
                    u[xp][y] = 0;
                    ++xp;
                    break;
                } else if (u[xp][y] == 9 && right_side) {
                    u[xp][y] = 0;
                } else if (u[xp][y] == 7) {
                    u[x][y] = u[x][y] % 4 + 1;
                    right_side = u[x][y] == 3;
                } else if (u[xp][y] == 8) {
                    u[x][y] = u[x][y] - 1;
                    if (!u[x][y]) u[x][y] = 4;
                    right_side = u[x][y] == 3;
                } else if (u[xp][y] == 11) {
                    if (right_side) u[xp][y] = 0;
                    else {
                        would_die = 1;
                        break;
                    }
                }
                ++xp;
            }
            if (!would_die && xp - 1 != x) {
                u[xp - 1][y] = u[x][y];
                u[x][y] = 0;
                que.push_back(u);
            }
        }
        { // go right
            bool right_side = v[x][y] == 2;
            bool would_die = 0;
            int yp = y;
            vector<vector<int>> u = v;
            while (yp < m && u[x][yp] != 5) {
                if (u[x][yp] == 6) {
                    would_die = 1;
                    break;
                } else if (u[x][yp] == 10) {
                    u[x][yp] = 0;
                    ++yp;
                    break;
                } else if (u[x][yp] == 9 && right_side) {
                    u[x][yp] = 0;
                } else if (u[x][yp] == 7) {
                    u[x][y] = u[x][y] % 4 + 1;
                    right_side = u[x][y] == 2;
                } else if (u[x][yp] == 8) {
                    u[x][y] = u[x][y] - 1;
                    if (!u[x][y]) u[x][y] = 4;
                    right_side = u[x][y] == 2;
                } else if (u[x][yp] == 11) {
                    if (right_side) u[x][yp] = 0;
                    else {
                        would_die = 1;
                        break;
                    }
                }
                ++yp;
            }
            if (!would_die && yp - 1 != y) {
                u[x][yp - 1] = u[x][y];
                u[x][y] = 0;
                que.push_back(u);
            }
        }
        { // go up
            bool right_side = v[x][y] == 1;
            bool would_die = 0;
            int xp = x;
            vector<vector<int>> u = v;
            while (xp >= 0 && u[xp][y] != 5) {
                if (u[xp][y] == 6) {
                    would_die = 1;
                    break;
                } else if (u[xp][y] == 10) {
                    u[xp][y] = 0;
                    --xp;
                    break;
                } else if (u[xp][y] == 9 && right_side) {
                    u[xp][y] = 0;
                } else if (u[xp][y] == 7) {
                    u[x][y] = u[x][y] % 4 + 1;
                    right_side = u[x][y] == 1;
                } else if (u[xp][y] == 8) {
                    u[x][y] = u[x][y] - 1;
                    if (!u[x][y]) u[x][y] = 4;
                    right_side = u[x][y] == 1;
                } else if (u[xp][y] == 11) {
                    if (right_side) u[xp][y] = 0;
                    else {
                        would_die = 1;
                        break;
                    }
                }
                --xp;
            }
            if (!would_die && xp + 1 != x) {
                u[xp + 1][y] = u[x][y];
                u[x][y] = 0;
                que.push_back(u);
            }
        }
    }
    return 0;
}

void add(map<pii, int>& states, pii start, int val) {
    auto [x, y] = start;
    int coord = 0;
    int reversed = 0;
    if (states[{x + 1, y}] == 5) {
        coord = 0;
        reversed = 1;
    } else if (states[{x - 1, y}] == 5) {
        coord = 0;
        reversed = -1;
    } else if (states[{x, y + 1}] == 5) {
        coord = 1;
        reversed = 1;
    } else if (states[{x, y - 1}] == 5) {
        coord = 1;
        reversed = -1;
    }

    int tmp_cnt = 1;
    int go = rnd() % tmp_cnt;
    if (go == 0) {
        int by = rnd() % MOD + 1;
        int ab = rnd() % MOD + 2;
        int xp = rnd() % MOD + 1;
        int pt = rnd() % MOD + 1;
        xp *= reversed;
        pt *= reversed;
        int b = y - by;
        int a = b - ab;
        int p = x - xp;
        int t = p - pt;
        if (coord == 0) {
            states[{x, y + 1}] = states[{t, b}] = states[{x + reversed, b - 1}] = states[{x, a - 1}] = states[{t - reversed, a}] = 5;
            states[{p, a}] = val;
        } else {
            states[{y + 1, x}] = states[{b, t}] = states[{b - 1, x + reversed}] = states[{a - 1, x}] = states[{a, t - reversed}] = 5;
            states[{a, p}] = val;
        }
    }
}

bool squeeze_x(vvi& f, int x, int cnt) {
    vvi t;
    for (int i = 0; i < f.size(); ++i) {
        if (i != x + 1) {
            t.push_back(f[i]);
        }
        if (i == x) {
            for (int j = 0; j < f[x].size(); ++j) {
                if (f[i][j] || f[i + 1][j]) return 0;
                t[i][j] += f[i + 1][j];
            }
        }
    }
    if (possible(t) && possible(t) <= cnt) {
        f = t;
        return 1;
    }
    return 0;
}

//bool squeeze_y(vvi& f, int y, int cnt) {
//    vvi t;
//    for (int i = 0; i < f[0].size(); ++i) {
//        if (i != y + 1) {
//            vi cur;
//
//        }
//    }
//}

vvi compact(map<pii, int>& states) {
    vi x, y;
    for (auto s : states) {
        x.push_back(s.first.first - 1);
        x.push_back(s.first.first);
        x.push_back(s.first.first + 1);
        y.push_back(s.first.second - 1);
        y.push_back(s.first.second);
        y.push_back(s.first.second + 1);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());
    y.resize(unique(y.begin(), y.end()) - y.begin());
    map<int, int> gox, goy;
    for (int i = 0; i < x.size(); ++i) {
        gox[x[i]] = i;
    }
    for (int i = 0; i < y.size(); ++i) {
        goy[y[i]] = i;
    }
    vvi a(x.size(), vi(y.size()));
    for (auto s : states) {
        int xx = gox[s.first.first];
        int yy = goy[s.first.second];
        int val = s.second;
        a[xx][yy] = val;
    }
    bool ok = 1;
    while (ok) {
        ok = 0;
        for (int i = 1; i + 2 < a.size(); ++i) {
            ok |= squeeze_x(a, i, 100);
        }
    }
    return a;
}

void create(map<pii, int>& states, int depth, pii start, bool dead) {
    auto [x, y] = start;
    int coord = 0;
    int reversed = 0;
    if (states[{x + 1, y}] == 5) {
        coord = 0;
        reversed = 1;
    } else if (states[{x - 1, y}] == 5) {
        coord = 0;
        reversed = -1;
    } else if (states[{x, y + 1}] == 5) {
        coord = 1;
        reversed = 1;
    } else if (states[{x, y - 1}] == 5) {
        coord = 1;
        reversed = -1;
    }

    if (!depth) {
        if (dead) return;
        if (coord == 0) {
            int yy = rnd() % MOD;
            if (yy < y) {
                states[{x, yy - 1}] = 10;
            } else {
                states[{x, yy + 1}] = 10;
            }
        } else {
            int xx = rnd() % MOD;
            if (xx < x) {
                states[{xx - 1, y}] = 10;
            } else {
                states[{xx + 1, y}] = 10;
            }
        }
        return;
    }
    vi probs = {1000, 500, 200}; // simple, double, add
    int sum = 0;
    for (auto p : probs) sum += p;
    int val = rnd() % sum;
    sum = 0;
    int way = 0;
    for (int i = 0; i < probs.size(); ++i) {
        sum += probs[i];
        if (val < sum) {
            way = i;
            break;
        }
    }

//    auto a = compact(states);
//    print(a);

    if (way == 0) {
        if (coord == 0) {
            int yy = rnd() % MOD;
            if (yy < y) {
                states[{x, yy - 1}] = 5;
            } else {
                states[{x, yy + 1}] = 5;
            }
            create(states, depth - 1, {x, yy}, dead);
        } else {
            int xx = rnd() % MOD;
            if (xx < x) {
                states[{xx - 1, y}] = 5;
            } else {
                states[{xx + 1, y}] = 5;
            }
            create(states, depth - 1, {xx, y}, dead);
        }
    } else if (way == 1) {
        int bad = rnd() % 2;
        if (coord == 0) {
            int ym = y - rnd() % MOD;
            int yb = y + rnd() % MOD;
            states[{x, ym - 1}] = states[{x, yb + 1}] = 5;
            create(states, depth - 1, {x, ym}, dead | (bad == 0));
            create(states, depth - 1, {x, yb}, dead | (bad == 1));
        } else {
            int xm = x - rnd() % MOD;
            int xb = x + rnd() % MOD;
            states[{xm - 1, y}] = states[{xb + 1, y}] = 5;
            create(states, depth - 1, {xm, y}, dead | (bad == 0));
            create(states, depth - 1, {xb, y}, dead | (bad == 1));
        }
    } else if (way == 2) {
//        add(states, {x, y}, 10);
        create(states, depth, {x, y}, dead);
    }
}

signed main() {
//    int n, m; cin >> n >> m;
//    vector<vector<int>> a(n, vector<int>(m));
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            cin >> a[i][j];
//        }
//    }
//    cout << possible(a) << '\n';
    map<pii, int> states;
    states[{MOD / 2, MOD / 2}] = 1;
    states[{MOD / 2, MOD / 2 - 1}] = 5;
//    add(states, {0, 0}, 10);

    create(states, 6, {MOD / 2, MOD / 2}, 0);
    auto a = compact(states);
    print(a);
    cout << possible(a) << '\n';
}
