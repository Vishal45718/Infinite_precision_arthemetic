#include "float.hh"
#include <iostream>
namespace InfiniteArithmetic
{
	static Float parse(const std::string& s)
	{
		Float m(s);
		static Float n = m;
		return n;
	}
	Float zstrip(Float a)
	{ 
		int j = -1;
		Float new_a;
		new_a.isnegative = a.isnegative;
		for(int i = 0; i < a.l; i++)
		{
			if(a.gif[i] != 0)
			{
				j = i;
				break;
			}
		}
		if(j == -1)
		{	
			new_a.l = 1;
			new_a.gif = new int[new_a.l];
			new_a.gif[0] = 0;
		}	
		else if(j != -1)
		{
			if(a.l != 0)
				new_a.gif = new int[a.l-j];
			new_a.l = a.l - j;
			for(int i = 0; i < new_a.l; i++)
				new_a.gif[i] = a.gif[i+j];
		}
		j = -1;
		for(int i = a.p-1; i >= 0; i--)
		{
			if(a.dec[i] != 0)
			{
				j = i;
				break;
			}	
		}
		if(j == -1)
		{
			new_a.p = 0;
		}
		else if(j != -1)
		{
			if(a.p != 0)
				new_a.dec = new int[j+1];
			new_a.p = j+1;
			for(int i = 0; i < new_a.p; i++)
				new_a.dec[i] = a.dec[i];
		}
		return new_a;
	}		
	Float mmax(Float a, Float b)
	{
		Float new_a(zstrip(a));
		Float new_b(zstrip(b));
		if(new_a.l > new_b.l)
			return a;
		else if(new_b.l > new_a.l)
			return b;
		else if(new_a.l == new_b.l)
		{
			for(int i = 0; i < new_a.l; i++)
			{
				if(new_a.gif[i] > new_b.gif[i])
				{
					return a;
					break;
				}
				else if(new_b.gif[i] > new_a.gif[i])
				{	
					return b;
					break;
				}
			}
			int x = (new_a.p < new_b.p) ? new_a.p : new_b.p;
			for(int i = 0; i < x; i++)
			{
				if(new_a.dec[i] > new_b.dec[i])
				{
					return a;
					break;
				}
				else if(new_b.dec[i] > new_a.dec[i])
				{
					return b;
					break;
				}
			}
			return (new_a.p > new_b.p) ? a : b;
		}	
		return a;
	}
	Float mmin(Float a, Float b)
	{
		Float new_a(zstrip(a));
		Float new_b(zstrip(b));
		if(new_a.l < new_b.l)
			return a;
		else if(new_b.l < new_a.l)
			return b;
		else if(new_a.l == new_b.l)
		{
			for(int i = 0; i < new_a.l; i++)
			{
				if(new_a.gif[i] < new_b.gif[i])
				{
					return a;
					break;
				}
				else if(new_b.gif[i] < new_a.gif[i])
				{	
					return b;
					break;
				}
			}
			int x = (a.p < b.p) ? a.p : b.p;
                        for(int i = 0; i < x; i++)
                        {
                                if(new_a.dec[i] < new_b.dec[i])
                                {
                                        return a;
                                        break;
                                }
                                else if(new_b.dec[i] < new_a.dec[i])
                                {
                                        return b;
                                        break;
                                }
                        }
			return (new_a.p < new_b.p) ? a : b;
		}
		return a;	
	}
	bool operator==(Float a, Float b)
        {
                a = zstrip(a);
                b = zstrip(b);
                if(a.l == b.l && a.isnegative == b.isnegative && a.p == b.p)
                {
                        for(int i = 0; i < a.l; i++)
                                if(a.gif[i] != b.gif[i])
                                        return 0;
			for(int i = 0; i < a.p; i++)
				if(a.dec[i] != b.dec[i])
					return 0;
                        return 1;
                }
                return 0;
        }
        bool operator<(Float a, Float b)
        {
                return a == mmin(a,b) && !(a == b);
        }
        Float operator+(Float a, Float b)
	{
		Float sum;
		Float x = zstrip(mmin(a,b));
		Float y = zstrip(mmax(a,b));
		if(x.p > y.p)
		{
			int* c_dec;
			c_dec = new int[y.p+1];
			c_dec[0] = 0;
			sum.p = x.p;
			if(sum.p != 0)
				sum.dec = new int[x.p];
/*			for(int i = x.p-1; i >= y.p; i--)
			{
				c_dec[i] = (x.dec[i] + c_dec[i+1]) / 10;
				sum.dec[i] = (x.dec[i] + c_dec[i+1]) % 10;
			}
			if(y.p != 0)
			{
				for(int i = y.p-1; i >= 0; i--)
				{
					c_dec[i] = (x.dec[i] + y.dec[i] + c_dec[i+1]) / 10;
					sum.dec[i] = (x.dec[i] + y.dec[i] + c_dec[i+1]) % 10;
				}
			}	*/
			for(int i = 0; i < y.p; i++)
			{
				c_dec[i+1] = (x.dec[x.p-1-i] + y.dec[y.p-1-i] + c_dec[i]) / 10;
				sum.dec[i] = (x.dec[x.p-1-i] + y.dec[y.p-1-i] + c_dec[i]) % 10;
			}
			for(int i = 0; i < y.p/2; i++)
			{
				int temp = sum.dec[i];
                                sum.dec[i] = sum.dec[sum.p-1-i];
                                sum.dec[sum.p-1-i] = temp;
                        }
			for(int i = y.p; i < x.p; i++)
				sum.dec[i] = x.dec[i];
			if(x.l >= y.l)
			{
				if(x.l != 0)
					sum.gif = new int[x.l+1];
				int* c_gif;
				c_gif = new int[x.l+1];
				c_gif[0] = c_dec[y.p];
				for(int i = 0; i < y.l; i++)
				{
					c_gif[i+1] = (y.gif[y.l-1-i] + x.gif[x.l-1-i] + c_gif[i]) / 10;
					sum.gif[i] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) % 10;
				}
				for(int i = y.l; i < x.l; i++)
				{
					c_gif[i+1] = (x.gif[x.l-1-i] + c_gif[i]) / 10;
					sum.gif[i] = (x.gif[x.l-1-i] + c_gif[i]) % 10;
				}
				if(c_gif[x.l] == 1)
				{
					sum.gif[x.l] = c_gif[x.l];
					sum.l = x.l +1;
				}
				else
					sum.l = x.l;
				for(int i = 0; i < sum.l/2; i++)
				{
					int temp = sum.gif[i];
					sum.gif[i] = sum.gif[sum.l-1-i];
					sum.gif[sum.l-1-i] = temp;
				}	
				Float new_sum(zstrip(sum));
				return new_sum;
			}
			if(y.l > x.l)
                        {
                                if(y.l != 0)
                                        sum.gif = new int[y.l+1];
                                int* c_gif;
				c_gif = new int[y.l+1];
                                c_gif[0] = c_dec[0];
                                for(int i = 0; i < x.l; i++)
                                {
                                        c_gif[i+1] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) / 10;
                                        sum.gif[i] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) % 10;
                                }
                                for(int i = x.l; i < y.l; i++)
                                {
                                        c_gif[i+1] = (y.gif[y.l-1-i] + c_gif[i]) / 10;
                                        sum.gif[i] = (y.gif[y.l-1-i] + c_gif[i]) % 10;
                                }
                                if(c_gif[y.l] == 1)
                                {
                                        sum.gif[y.l] = c_gif[y.l];
                                        sum.l = y.l +1;
                                }
                                else
                                        sum.l = y.l;
                                for(int i = 0; i < sum.l/2; i++)
                                {
                                        int temp = sum.gif[i];
                                        sum.gif[i] = sum.gif[sum.l-1-i];
                                        sum.gif[sum.l-1-i] = temp;
                                }
                                Float new_sum(zstrip(sum));
                                return new_sum;
                        }
		}
		if(y.p >= x.p)
                {
                        int* c_dec;
			c_dec = new int[x.p+1];
			c_dec[0] = 0;
                        sum.p = y.p;
                        if(sum.p != 0)
			for(int i = 0; i < x.p; i++)
                        {
                                c_dec[i+1] = (x.dec[x.p-1-i] + y.dec[y.p-1-i] + c_dec[i]) / 10;
                                sum.dec[i] = (x.dec[x.p-1-i] + y.dec[y.p-1-i] + c_dec[i]) % 10;
                        }
                        for(int i = 0; i < x.p/2; i++)
                        {
                                int temp = sum.dec[i];
                                sum.dec[i] = sum.dec[sum.p-1-i];
                                sum.dec[sum.p-1-i] = temp;
                        }
                        for(int i = x.p; i < y.p; i++)
                                sum.dec[i] = y.dec[i];
                        if(x.l >= y.l)
                        {
                                if(x.l != 0)
                                        sum.gif = new int[x.l+1];
                                int* c_gif;
				c_gif = new int[x.l+1];
                                c_gif[0] = c_dec[x.p];
                                for(int i = 0; i < y.l; i++)
                                {
                                        c_gif[i+1] = (y.gif[y.l-1-i] + x.gif[x.l-1-i] + c_gif[i]) / 10;
                                        sum.gif[i] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) % 10;
                                }
                                for(int i = y.l; i < x.l; i++)
                                {
                                        c_gif[i+1] = (x.gif[x.l-1-i] + c_gif[i]) / 10;
					sum.gif[i] = (x.gif[x.l-1-i] + c_gif[i]) % 10;
                                }
                                if(c_gif[x.l] == 1)
                                {
                                        sum.gif[x.l] = c_gif[x.l];
                                        sum.l = x.l +1;
                                }
                                else
                                        sum.l = x.l;
                                for(int i = 0; i < sum.l/2; i++)
                                {
                                        int temp = sum.gif[i];
                                        sum.gif[i] = sum.gif[sum.l-1-i];
                                        sum.gif[sum.l-1-i] = temp;
                                }
                                Float new_sum(zstrip(sum));
                                return new_sum;
                        }
                        if(y.l > x.l)
                        {
                                if(y.l != 0)
                                        sum.gif = new int[y.l+1];
                                int* c_gif;
				c_gif = new int[y.l+1];
                                c_gif[0] = c_dec[0];
                                for(int i = 0; i < x.l; i++)
                                {
                                        c_gif[i+1] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) / 10;
                                        sum.gif[i] = (x.gif[x.l-1-i] + y.gif[y.l-1-i] + c_gif[i]) % 10;
                                }
                                for(int i = x.l; i < y.l; i++)
                                {
                                        c_gif[i+1] = (y.gif[y.l-1-i] + c_gif[i]) / 10;
                                        sum.gif[i] = (y.gif[y.l-1-i] + c_gif[i]) % 10;
                                }
                                if(c_gif[y.l] == 1)
                                {
					sum.gif[y.l] = c_gif[y.l];
                                        sum.l = y.l +1;
                                }
                                else
                                        sum.l = y.l;
                                for(int i = 0; i < sum.l/2; i++)
                                {
                                        int temp = sum.gif[i];
                                        sum.gif[i] = sum.gif[sum.l-1-i];
                                        sum.gif[sum.l-1-i] = temp;
                                }
                                Float new_sum(zstrip(sum));
				return new_sum;
                        }
                }
		return sum;
	}
	void displayFloat(Float a)
	{
		Float b(zstrip(a));
		if(b.isnegative == 1)
			std::cout << '-'; 
		for(int i = 0; i < b.l; i++)
			std::cout << b.gif[i];
		if(b.p != 0)
			std::cout << ".";
		for(int i = 0; i < b.p; i++)
			std::cout << b.dec[i];
		std::cout<<"\n";
	}	
}
