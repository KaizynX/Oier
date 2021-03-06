#include <iostream>
#include <map>

using namespace std;
/* 1 2 3 *
 * 4 5 6 *
 * 7 8 9 */
const int res = 123804765;
const int Maxq = 1e6;

struct Node
{
    int v, pos;
    Node(int v = 0, int pos = -1) : v(v), pos(pos) {}
} start;

int head, tail, step[Maxq];
Node q[Maxq];
map<int, bool> mmp;

inline Node change(Node form, int goal)
{
    int tmp[10];
    for(int i = 9; i; --i)
    {
        tmp[i] = form.v % 10;
        form.v /= 10;
    }
    swap(tmp[form.pos], tmp[goal]);
    swap(form.pos, goal);
    for(int i = 1; i <= 9; ++i)
    {
        form.v = form.v*10 + tmp[i];
    }
    return form;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> start.v;
    int tmp = start.v, cnt = 9;
    while(tmp)
    {
        int now = tmp % 10;
        if(!now)
        {
            start.pos = cnt;
            break;
        }
        tmp /= 10;
        --cnt;
    }
    // bfs
    Node cur;
    q[++tail] = start;
    mmp.insert(make_pair(start.v, true));
    while(head < tail)
    {
        cur = q[++head % Maxq];
        if(cur.v == res)
        {
            cout << step[head % Maxq] << endl;
            break;
        }
        if(cur.pos > 3) // up
        {
            q[++tail % Maxq] = change(cur, cur.pos-3);
            if(mmp.count(q[tail % Maxq].v)) --tail;
            else 
            {
                step[tail % Maxq] = step[head % Maxq]+1;
                mmp.insert(make_pair(q[tail % Maxq].v, true));
            }
        }
        if(cur.pos < 7) // down
        {
            q[++tail % Maxq] = change(cur, cur.pos+3);
            if(mmp.count(q[tail % Maxq].v)) --tail;
            else 
            {
                step[tail % Maxq] = step[head % Maxq]+1;
                mmp.insert(make_pair(q[tail % Maxq].v, true));
            }
        }
        if(cur.pos%3 != 1) // left
        {
            q[++tail % Maxq] = change(cur, cur.pos-1);
            if(mmp.count(q[tail % Maxq].v)) --tail;
            else 
            {
                step[tail % Maxq] = step[head % Maxq]+1;
                mmp.insert(make_pair(q[tail % Maxq].v, true));
            }
        }
        if(cur.pos%3 != 0) // right
        {
            q[++tail % Maxq] = change(cur, cur.pos+1);
            if(mmp.count(q[tail % Maxq].v)) --tail;
            else 
            {
                step[tail % Maxq] = step[head % Maxq]+1;
                mmp.insert(make_pair(q[tail % Maxq].v, true));
            }
        }
    }
    return 0;
}
