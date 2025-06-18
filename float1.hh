#include <string>
#include <iostream>
namespace InfiniteArithmetic 
{
	class Float 
	{
		private:
			int *gif;
			int l;
			int *dec;
			int p;
			int isnegative;
		public:
			Float(): l(1), p(0), isnegative(0) { gif = new int[l]; gif[0] = 0; }
			Float(std::string s)
		        {
				int check = 0;
				int error = 0;
				std::string validchar = "0123456789.";
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
					p = 0;
					isnegative = 0;
					gif = new int[l];
					gif[0] = 0;
				}
				else if(s[0] == '-')
				{
					isnegative = 1;
					int i = 0;
					while(s[i] != '.' && s[i] != '\0')
						i++;
					if(s[i] == '.')
					{
						l = i-1;
						p = s.length()-i-1;
						if(l != 0)
							gif = new int[l];
						for(int j = 0; j < l; j++)
						{
							char c = s[j+1];
							int ascii = c;
							gif[j] = ascii - 48;
						}
						if(p != 0)
							dec = new int[p];
						for(int j = 0; j < p; j++)
						{
							char c = s[l+2+j];
							int ascii = c;
							dec[j] = ascii - 48;
						}
					}	
					else
					{
						l = s.length() - 1;
						p = 0;
						if(l != 0)
							gif = new int[l];
						for(int j = 0; j < l; j++)
						{
							char c = s[j+1];
							int ascii = c;
							gif[j] = ascii - 48;
						}
					}	
				}
				else if(s[0] == '+')
				{
					isnegative = 0;
                                        int i = 0;
                                        while(s[i] != '.' && s[i] != '\0')
                                                i++;
                                        if(s[i] == '.')
                                        {
                                                l = i-1;
                                                p = s.length()-i-1;
						if(l != 0)
                                                	gif = new int[l];
                                                for(int j = 0; j < l; j++)
                                                {
                                                       	char c = s[j+1];
                                                        int ascii = c;
                                                        gif[j] = ascii - 48;
                                                }
						if(p != 0)
                                                	dec = new int[p];
                                                for(int j = 0; j < p; j++)
                                                {
                                                        char c = s[l+2+j];
                                                        int ascii = c;
                                                        dec[j] = ascii - 48;
                                                }
                                        }
                                        else
                                        {
                                                l = s.length() - 1;
                                                p = 0;
						if(l != 0)
                                                	gif = new int[l];
                                                for(int j = 0; j < l; j++)
                                                {
                                                        char c = s[j+1];
                                                        int ascii = c;
                                                        gif[j] = ascii - 48;
                                                }
                                        }

				}
				else
				{
					isnegative = 0;
                                        int i = 0;
                                        while(s[i] != '.' && s[i] != '\0')
                                                i++;
                                        if(s[i] == '.')
                                        {
                                                l = i;
                                                p = s.length()-i-1;
						if(l != 0)
                                                	gif = new int[l];
                                                for(int j = 0; j < l; j++)
                                                {
                                                        char c = s[j];
                                                        int ascii = c;
                                                        gif[j] = ascii - 48;
                                                }
						if(p != 0)
                                                	dec = new int[p];
                                                for(int j = 0; j < p; j++)
                                                {
                                                        char c = s[l+1+j];
                                                        int ascii = c;
                                                        dec[j] = ascii - 48;
                                                }
                                        }
                                        else
                                        {
                                                l = s.length();
                                                p = 0;
						if(l != 0)
                                                	gif = new int[l];
                                                for(int j = 0; j < l; j++)
                                                {
                                                        char c = s[j];
                                                        int ascii = c;
                                                        gif[j] = ascii - 48;
                                                }
                                        }
				}
			}	
			Float(Float& a): l(a.l), p(a.p), isnegative(a.isnegative)
			{
				if(a.l != 0)
					gif = new int[l];
				for(int i = 0; i < l; i++) 
					gif[i] = a.gif[i];
				if(a.p != 0)
					dec = new int[p];
				for(int i = 0; i < p; i++)
					dec[i] = a.dec[i];
			}
			~Float() 
			{ 
				if(l != 0)
					delete[] gif; 
				if(p != 0)
					delete[] dec; 
			}
			Float& operator=(Float a)
                        {
                                l = a.l;
				p = a.p;
                                isnegative = a.isnegative;
				if(l != 0)
                                	gif = new int[l];
                                for(int i = 0; i < l; i++)
                                        gif[i] = a.gif[i];
				if(p != 0)
					dec = new int[p];
				for(int i = 0; i < p; i++)
					dec[i] = a.dec[i];
                                return *this;
                        }
			static Float parse(const std::string& s);
			friend Float zstrip(Float a);
			friend Float mmax(Float a, Float b);
			friend Float mmin(Float a, Float b);
			friend bool operator==(Float a, Float b);
                        friend bool operator<(Float a, Float b);
			friend Float operator+(Float a, Float b);
			friend Float operator-(Float a, Float b);
			friend Float operator*(Float a, Float b);
			friend Float operator/(Float a, Float b);
			friend void displayFloat(Float a);
	};
}
