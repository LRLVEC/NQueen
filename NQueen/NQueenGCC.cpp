#include <cstdio>
#include <cstring>
#ifdef _WIN32
#include <_Time.h>
#else
#include <ctime>
#endif
constexpr int N = 16;
constexpr int N1 = 2 * N - 1;
constexpr int N2 = N - 1;

unsigned long long answerNum(0);
unsigned long long counter(0);

#define get64(x, y) (x &  (1llu << (y)))
#define set64(x, y) (x ^= (1llu << (y)))
#define pet64(x, y) (x ^  (1llu << (y)))
void queen0()
{
	char cycles[N]{ 0 };
	int depth(0);
	unsigned long long lim0(0xffffffffffffffff);
	unsigned long long lim1(0xffffffffffffffff);
	unsigned long long lim2(0xffffffffffffffff);
	while (cycles[0] < N / 2)
	{
		for (int c0(cycles[depth]); c0 < N;)
		{
			if ((get64(lim0, c0) != 0) * (get64(lim1, depth + c0) != 0) * (get64(lim2, N2 - depth + c0) != 0))
			{
				if (depth < N2)
				{
					set64(lim0, c0);
					set64(lim1, depth + c0);
					set64(lim2, N2 - depth + c0);
					cycles[depth++] = c0;
					c0 = 0;
					continue;
				}
				else
				{
					++answerNum;
					break;
				}
			}
			++c0;
		}
		set64(lim0, cycles[--depth]);
		set64(lim1, depth + cycles[depth]);
		set64(lim2, N2 - depth + cycles[depth]);
		++cycles[depth];
	}
	answerNum <<= 1;
	while (cycles[0] < (N + 1) / 2)
	{
		for (int c0(cycles[depth]); c0 < N;)
		{
			if ((get64(lim0, c0) != 0) * (get64(lim1, depth + c0) != 0) * (get64(lim2, N2 - depth + c0) != 0))
			{
				if (depth < N2)
				{
					//++counter;
					set64(lim0, c0);
					set64(lim1, depth + c0);
					set64(lim2, N2 - depth + c0);
					cycles[depth++] = c0;
					c0 = 0;
					continue;
				}
				else
				{
					++answerNum;
					break;
				}
			}
			++c0;
		}
		set64(lim0, cycles[--depth]);
		set64(lim1, depth + cycles[depth]);
		set64(lim2, N2 - depth + cycles[depth]);
		++cycles[depth];
	}
}
void queen1s(unsigned long long lim0, unsigned long long lim1, unsigned long long lim2, int depth)
{
	for (int c0(0); c0 < N; ++c0)
		if ((get64(lim0, c0) != 0) * (get64(lim1, depth + c0) != 0) * (get64(lim2, N2 - depth + c0) != 0))
		{
			if (depth < N - 1)
				queen1s(pet64(lim0, c0), pet64(lim1, depth + c0), pet64(lim2, N2 - depth + c0), depth + 1);
			else { ++answerNum; return; }
		}
}
void queen1()
{
	unsigned long long lim0(0xffffffffffffffff);
	unsigned long long lim1(0xffffffffffffffff);
	unsigned long long lim2(0xffffffffffffffff);
	int c0(0);
	for (; c0 < N / 2; ++c0)
		queen1s(pet64(lim0, c0), pet64(lim1, c0), pet64(lim2, N2 + c0), 1);
	answerNum <<= 1;
	if (N % 2)
		if (N != 1)
			queen1s(pet64(lim0, c0), pet64(lim1, c0), pet64(lim2, N2 + c0), 1);
		else answerNum++;
}
/*void queen1s(unsigned long long lim0, unsigned long long lim1, unsigned long long lim2, int depth)
{
	for (int c0(0); c0 < N; ++c0)
		if ((get64(lim0, c0) != 0) * (get64(lim1, depth + c0) != 0) * (get64(lim2, N2 - depth + c0) != 0))
		{
			if (depth < N - 3)queen1s(pet64(lim0, c0), pet64(lim1, depth + c0), pet64(lim2, N2 - depth + c0), depth + 1);
			else if (depth == N - 3)
			{
				unsigned long long _lim0(pet64(lim0, c0));
				unsigned long long y(pet64(lim1, depth + c0));
				unsigned long long z(pet64(lim2, N2 - depth + c0));
				int c1(0), c2;
				while ((_lim0 & 1llu) == 0) { _lim0 >>= 1; ++c1; }_lim0 >>= 1;  c2 = c1 + 1;
				while ((_lim0 & 1llu) == 0) { _lim0 >>= 1; ++c2; }
				if (c2 - c1 == 1)continue;
				int _depth(depth + 1);
				if ((get64(y, _depth + c1) != 0) * (get64(z, N2 - _depth + c1) != 0))
				{
					unsigned long long p(y);
					unsigned long long q(z);
					set64(p, _depth + c1);
					set64(q, N2 - _depth + c1);
					int __depth(_depth + 1);
					if ((get64(p, __depth + c2) != 0) * (get64(q, N2 - __depth + c2) != 0))answerNum++;
				}
				if ((get64(y, _depth + c2) != 0) * (get64(z, N2 - _depth + c2) != 0))
				{
					set64(y, _depth + c2);
					set64(z, N2 - _depth + c2);
					int __depth(_depth + 1);
					if ((get64(y, __depth + c1) != 0) * (get64(z, N2 - __depth + c1) != 0))answerNum++;
				}
			}
			else if (depth == N - 2)
			{
				unsigned long long _lim0(pet64(lim0, c0));
				unsigned long long y(pet64(lim1, depth + c0));
				unsigned long long z(pet64(lim2, N2 - depth + c0));
				int c1(0);
				while ((_lim0 & 1llu) == 0) { _lim0 >>= 1; ++c1; }
				int _depth(depth + 1);
				if ((get64(y, _depth + c1) != 0) * (get64(z, N2 - _depth + c1) != 0))answerNum++;
			}
		}
}
void queen1()
{
	if (N == 1)
	{
		answerNum = 1;
		return;
	}
	unsigned long long lim0(0xffffffffffffffff);
	unsigned long long lim1(0xffffffffffffffff);
	unsigned long long lim2(0xffffffffffffffff);
	int c0(0);
	for (; c0 < N / 2; ++c0)
		queen1s(pet64(lim0, c0), pet64(lim1, c0), pet64(lim2, N2 + c0), 1);
	answerNum <<= 1;
	if (N % 2)queen1s(pet64(lim0, c0), pet64(lim1, c0), pet64(lim2, N2 + c0), 1);

}*/
unsigned long long upperlim;
void queen2s(int row, int ld, int rd)
{
	if (row != upperlim)
	{
		int pos, p;
		pos = upperlim & (~(row | ld | rd));
		while (pos)
		{
			p = pos & (~pos + 1);
			pos = pos - p;
			queen2s(row | p, (ld | p) << 1, (rd | p) >> 1);
		}
	}
	else
		++answerNum;
}
void queen2()
{
	upperlim = (1 << N) - 1;
	queen2s(0, 0, 0);
}

void test(void (*p)())
{
	answerNum = 0;
#ifdef _WIN32
	Timer timer;
	timer.begin();
#else
	timespec t0, t1;
	clock_gettime(CLOCK_REALTIME, &t0);
#endif
	p();
#ifdef _WIN32
	timer.end();
	timer.print();
#else
	clock_gettime(CLOCK_REALTIME, &t1);
	::printf("%lld\n", 1000000000 * (t1.tv_sec - t0.tv_sec) + t1.tv_nsec - t0.tv_nsec);
#endif
	//::printf("%llu\n", counter);
	::printf("%llu\n", answerNum);

}


int main()
{
	test(queen0);
	test(queen1);
	test(queen2);
}
