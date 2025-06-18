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
	Integer operator+(Integer a, Integer b)
        {
                Integer sum;
                Integer x = zstrip(mmin(a,b));
                Integer y = zstrip(mmax(a,b));
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
	void displayInteger(Integer a)
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
