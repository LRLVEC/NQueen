#include <cstdio>
#include <_Array.h>
#include <_Vector.h>
#include <_Pair.h>
#include <_Time.h>

constexpr int N = 14;
constexpr int N1 = 2 * N - 1;
constexpr int N2 = N - 1;

Vector<Array<int, N>>answer;
int answerNum(0);

void queen(Array<bool, N>& const lim0, Pair<Array<bool, N1>, Array<bool, N1>>& const lim1, Array<int, N>& const order, int depth)
{
	if (depth < N)
	{
		for (int c0(0); c0 < N; ++c0)
		{
			if (lim0[c0] && lim1.data0[depth + c0] && lim1.data1[N2 - depth + c0])
			{
				Array<bool, N> _lim0(lim0);
				Pair<Array<bool, N1>, Array<bool, N1>> _lim1(lim1);
				Array<int, N>_order(order);
				_order[depth] = c0;
				_lim0[c0] = false;
				_lim1.data0[depth + c0] = false;
				_lim1.data1[N2 - depth + c0] = false;
				queen(_lim0, _lim1, _order, depth + 1);
			}
		}
	}
	else
	{
		++answerNum;
		//answer.pushBack(order);
	}
}

void queen1(Array<bool, N>& lim0, Pair<Array<bool, N1>, Array<bool, N1>>& lim1, Array<int, N>& order)
{
	int cycles[N]{ 0 };
	int depth(0);
	while (cycles[0] < N)
	{
		for (int c0(cycles[depth]); c0 < N; ++c0)
		{
			if (lim0.data[c0] && lim1.data0.data[depth + c0] && lim1.data1.data[N2 - depth + c0])
			{
				if (depth < N2)
				{
					order.data[depth] = c0;
					lim0.data[c0] = false;
					lim1.data0.data[depth + c0] = false;
					lim1.data1.data[N2 - depth + c0] = false;
					cycles[depth++] = c0;
					c0 = -1;
				}
				else
				{
					answerNum++;
					break;
				}
			}
		}
		order.data[--depth] = -1;
		lim0.data[cycles[depth]] = true;
		lim1.data0.data[depth + cycles[depth]] = true;
		lim1.data1.data[N2 - depth + cycles[depth]] = true;
		cycles[depth]++;
	}
}

void queen2(bool lim0[N], bool lim1[N1], bool lim2[N1], int order[N])
{
	int cycles[N]{ 0 };
	int depth(0);
	while (cycles[0] < N)
	{
		for (int c0(cycles[depth]); c0 < N; ++c0)
		{
			if (lim0[c0] && lim1[depth + c0] && lim2[N2 - depth + c0])
			{
				if (depth < N2)
				{
					order[depth] = c0;
					lim0[c0] = false;
					lim1[depth + c0] = false;
					lim2[N2 - depth + c0] = false;
					cycles[depth++] = c0;
					c0 = -1;
				}
				else
				{
					answerNum++;
					break;
				}
			}
		}
		order[--depth] = -1;
		lim0[cycles[depth]] = true;
		lim1[depth + cycles[depth]] = true;
		lim2[N2 - depth + cycles[depth]] = true;
		cycles[depth]++;
	}
}

int main()
{
	Timer timer;
	timer.begin();
	int order[N];
	for (int c0(0); c0 < N; ++c0)order[c0] = -1;
	bool lim0[N];
	bool lim1[N1];
	bool lim2[N1];
	::memset(&lim0, 1, sizeof(lim0));
	::memset(&lim1, 1, sizeof(lim1));
	::memset(&lim2, 1, sizeof(lim2));
	queen2(lim0, lim1, lim2, order);
	timer.end();
	timer.print();
	//answer.traverse([](auto const& a) {a.traverse([](auto const& b) {::printf("%d ", b); return true; }); ::printf("\n"); return true; });
	::printf("%d\n", answerNum);
}