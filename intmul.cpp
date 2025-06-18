#include "integer.hh"
#include <iostream>
namespace InfiniteArithmetic
{
	static Integer parse(const std::string& s)
	{
		Integer m(s);
		static Integer n = m;
		return n;
	}
	Integer zstrip(Integer a)
	{ 
		int j = -1;
		Integer new_a;
		for(int i = 0; i < a.l; i++)
		{
			if(a.rep[i] != 0)
			{
				j = i;
				break;
			}
		}	
		if(j != -1)
		{
			new_a.isnegative = a.isnegative;
			new_a.rep = new int[a.l-j];
			new_a.l = a.l - j;
			for(int i = 0; i < new_a.l; i++)
				new_a.rep[i] = a.rep[i+j];
		}
		return new_a;
	}		
	Integer mmax(Integer a, Integer b)
	{
		Integer new_a(zstrip(a));
		Integer new_b(zstrip(b));
		if(new_a.l > new_b.l)
			return a;
		else if(new_b.l > new_a.l)
			return b;
		else if(new_a.l == new_b.l)
		{
			for(int i = 0; i < new_a.l; i++)
			{
				if(new_a.rep[i] > new_b.rep[i])
				{
					return a;
					break;
				}
				else if(new_b.rep[i] > new_a.rep[i])
				{	
					return b;
					break;
				}
			}
		}	
		return a;
	}
	Integer mmin(Integer a, Integer b)
	{
		Integer new_a(zstrip(a));
		Integer new_b(zstrip(b));
		if(new_a.l < new_b.l)
			return a;
		else if(new_b.l < new_a.l)
			return b;
		else if(new_a.l == new_b.l)
		{
			for(int i = 0; i < new_a.l; i++)
			{
				if(new_a.rep[i] < new_b.rep[i])
				{
					return a;
					break;
				}
				else if(new_b.rep[i] < new_a.rep[i])
				{	
					return b;
					break;
				}
			}
		}
		return a;	
	}	
	bool operator==(Integer a, Integer b)
        {
                a = zstrip(a);
                b = zstrip(b);
                if(a.l == b.l && a.isnegative == b.isnegative)
		{
                        for(int i = 0; i < a.l; i++)
                                if(a.rep[i] != b.rep[i])
                                        return 0;
                        return 1;
		}
                return 0;
        }
        bool operator<(Integer a, Integer b)
        {
                return a == mmin(a,b) && !(a == b);
        }
	Integer operator+(Integer a, Integer b)
        {
                Integer sum;
                Integer x = zstrip(mmin(a,b));
                Integer y = zstrip(mmax(a,b));
                if(x.isnegative == 0 && y.isnegative == 1)
                {
                        y.isnegative = 0;
                        Integer sum(y-x);
                        sum.isnegative = 1;
                        return sum;
                }
                if(x.isnegative == 1 && y.isnegative == 0)
                {
                        x.isnegative = 0;
                        Integer sum(y-x);
                        sum.isnegative = 0;
                        return sum;
                }
                if(x.isnegative == 1 && y.isnegative == 1)
                {
                        x.isnegative = 0;
                        y.isnegative = 0;
                        Integer sum(x+y);
                        sum.isnegative = 1;
                        return sum;
                }
                sum.l = 0;
                sum.rep = new int[y.l+1];
                int c[y.l+1];
                c[0] = 0;
                for(int i = 0; i < x.l; i++)
                {
                        c[i+1] = (x.rep[x.l-1-i] + y.rep[y.l-1-i] + c[i]) / 10;
                        sum.rep[i] = (x.rep[x.l-1-i] + y.rep[y.l-1-i] + c[i]) % 10;
                }
		for(int i = x.l; i < y.l; i++)
                {
                        c[i+1] = (y.rep[y.l-1-i] + c[i]) / 10;
                        sum.rep[i] = (y.rep[y.l-1-i] + c[i]) % 10;
                }
                if(c[y.l] == 1)
                {
                        sum.rep[y.l] = c[y.l];
                        sum.l = y.l +1;
                }
                else
                {
                        sum.l = y.l;
                }
                for(int i = 0; i < sum.l/2; i++)
                {
                        int temp = sum.rep[i];
                        sum.rep[i] = sum.rep[sum.l-1-i];
                        sum.rep[sum.l-1-i] = temp;
                }
                Integer new_sum(zstrip(sum));
                return new_sum;
        }
	Integer operator-(Integer a, Integer b)
        {
                Integer diff;
                Integer x = zstrip(mmin(a,b));
                Integer y = zstrip(mmax(a,b));
                if(a.isnegative == 1 && b.isnegative == 0)
                {
                        a.isnegative = 0;
                        Integer diff(a + b);
                        diff.isnegative = 1;
                        return diff;
                }
                if(a.isnegative == 0 && b.isnegative == 1)
                {
                        b.isnegative = 0;
                        Integer diff(a + b);
                        diff.isnegative = 0;
                        return diff;
                }
                if(a.isnegative == 1 && b.isnegative == 1)
                {
                        a.isnegative = 0;
                        b.isnegative = 0;
                        Integer diff(b - a);
                        return diff;
                }
                diff.rep = new int[y.l];
                diff.l = y.l;
                if(a == y)
                        diff.isnegative = 0;
                else
                        diff.isnegative = 1;
                int c[y.l];
                for(int i = 0; i < y.l; i++)
                        c[i] = 0;
                for(int i = 0; i < x.l; i++)
		{
                        if(y.rep[y.l-1-i] + c[i] < x.rep[x.l-1-i])
                        {
                                c[i] += 10;
                                c[i+1] -= 1;
                        }
                        diff.rep[i] = y.rep[y.l-1-i] - x.rep[x.l-1-i] + c[i];
                }
                for(int i = x.l; i < y.l; i++)
		{
			if(y.rep[y.l-1-i] + c[i] < 0)
			{
				c[i] += 10;
				c[i+1] -= 1;
			}
                        diff.rep[i] = y.rep[y.l-1-i] + c[i];
		}
                for(int i = 0; i < diff.l/2; i++)
                {
                        int temp = diff.rep[i];
                        diff.rep[i] = diff.rep[diff.l-1-i];
                        diff.rep[diff.l-1-i] = temp;
                }
                Integer new_diff(zstrip(diff));
                return new_diff;
        }
	Integer operator*(Integer a, Integer b)
        {
                Integer mul;
                Integer x = zstrip(mmin(a,b));
                Integer y = zstrip(mmax(a,b));
                mul.rep = new int[y.l+x.l+2];
                mul.l = y.l + x.l + 2;
		if(a.isnegative == b.isnegative)
                	mul.isnegative = 0;
		if(a.isnegative != b.isnegative)
			mul.isnegative = 1;
                int c[y.l+x.l+2];
                for(int i = 0; i < y.l+x.l+2; i++)
                        mul.rep[i] = 0;
                for(int i = 0; i < x.l; i++)
                {
                        c[0] = 0;
                        for(int j = 0; j < y.l; j++)
                        {
                                c[j+1] = (mul.rep[i+j] + y.rep[y.l-1-j] * x.rep[x.l-1-i] + c[j])/10;
                                mul.rep[i+j] = (mul.rep[i+j] + y.rep[y.l-1-j]*x.rep[x.l-1-i] + c[j])%10;
                        }
                        mul.rep[i+y.l] = (c[y.l] + mul.rep[i+y.l])%10;
                }
                for(int i = 0; i < mul.l/2; i++)
                {
                        int temp = mul.rep[i];
                        mul.rep[i] = mul.rep[mul.l-1-i];
                        mul.rep[mul.l-1-i] = temp;
                }
                Integer new_mul(zstrip(mul));
                return new_mul;
        }
	void displayInteger(Integer a)
	{
		if(a.isnegative != 2)
		{
			Integer b(zstrip(a));
			if(b.isnegative == 1)
				std::cout<<'-'; 
			for(int i = 0; i < b.l; i++)
			{
				std::cout<<b.rep[i];
			}
			std::cout<<"\n";
		}
	}	
}
