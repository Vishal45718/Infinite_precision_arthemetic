#include <string>

#include <iostream>

namespace InfiniteArithmetic 
{
	class Integer 
	{
		private:
			int l;
			int *rep;
			int isnegative;
		public:

			Integer(): l(1), isnegative(0) 
			{
				if(l != 0)
					rep = new int[l]; rep[0] = 0; }
			Integer(std::string s) 
		        {
				int check = 0;
                                int error = 0;
                                std::string validchar = "0123456789";
				std::string sign = "+-";
                                for(int i = 0; i < s.length(); i++)
                                {
                                        check = 0;
					if(i == 0 && (s[i] == sign[0] || s[i] == sign[1]))
                                                check++;
                                        for(int j = 0; j < validchar.length(); j++)
                                        {
                                                if(s[i] == validchar[j])
                                                        check++;
                                        }
                                        if(check == 0)
                                                error = 1;
                                }
                                if(error == 1)
                                {
                                        std::cout << "Invalid string input. Default constructor called.\n";
                                        l = 1;
                                        isnegative = 0;
                                        rep = new int[l];
                                        rep[0] = 0;
                                }
				else if(s[0] == '-')
				{	
					isnegative = 1;
					l = s.length()-1;
					if(l != 0)
						rep = new int[l];
			Integer(): l(1), isnegative(0) { rep = new int[l]; rep[0] = 0; }
			Integer(std::string s) 
		        {
				if(s[0] == '-')
				{	
					isnegative = 1;
					l = s.length()-1;
					rep = new int[l];
					for(int i = 0; i < l; i++) 
					{
						char c = s[i+1];
						int ascii = c;
						rep[i] = ascii - 48;
					}
				}
				else if(s[0] == '+')
				{
					isnegative = 0;
					l = s.length()-1;
					if(l != 0)
						rep = new int[l];
					rep = new int[l];
					for(int i = 0; i < l; i++)
					{
						char c = s[i+1];
						int ascii = c;
						rep[i] = ascii - 48;
					}
				}
				else
				{
					isnegative = 0;
					l = s.length();
					if(l != 0)
						rep = new int[l];
					rep = new int[l];
					for(int i = 0; i < l; i++)
					{
						char c = s[i];
						int ascii = c;
						rep[i] = ascii - 48;
					}
				}
			}	
			Integer(Integer& p): l(p.l), isnegative(p.isnegative) 
			{
				if(l != 0)
					rep = new int[l];
				rep = new int[l];
				for(int i = 0; i < l; i++) 
				{
					rep[i] = p.rep[i];
				}
			}
			~Integer() 
			{
			       if(l != 0)	
					delete[] rep; 
			}
			~Integer() { delete[] rep; }
			Integer& operator=(Integer p)
                        {

                                l = p.l;
                                isnegative = p.isnegative;
				if(l != 0)
                                	rep = new int[l];
                                rep = new int[l];
                                for(int i = 0; i < l; i++)
                                {
                                        rep[i] = p.rep[i];
                                }
                                return *this;
                        }
			static Integer parse(const std::string& s);
			friend Integer zstrip(Integer a);
			friend Integer mmax(Integer a, Integer b);
			friend Integer mmin(Integer a, Integer b);
			friend bool operator==(Integer a, Integer b);
                        friend bool operator<(Integer a, Integer b);
			friend Integer operator+(Integer a, Integer b);
			friend Integer operator-(Integer a, Integer b);
			friend Integer operator*(Integer a, Integer b);
			friend Integer operator/(Integer a, Integer b);
			friend void displayInteger(Integer a);
	};
}
