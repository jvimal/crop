#ifndef COMMON_H_Q8QICW04
#define COMMON_H_Q8QICW04

#define dbg(e) (cout << #e << " " << e << endl)
#define REP(i,n) for(int i = 0; i < n; ++i)
#define LET(it,a) __typeof(a) it(a)
#define EACH(it,cont) for(LET(it,(cont).begin()); it != (cont).end(); ++it)
#define FOR(i,s,e) for(int i=(s); i<(e); ++i)

#define key first
#define value second

typedef unsigned char byte;

#endif /* end of include guard: COMMON_H_Q8QICW04 */
