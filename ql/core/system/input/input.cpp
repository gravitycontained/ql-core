#include <ql/core/system/input/input.hpp>

#include <ql/core/system/print/print.hpp>
#include <conio.h>

namespace ql
{
	std::string ql::get_hidden_input(const std::string_view& replace)
	{
		std::string result;
		char c;
		while (true)
		{
			c = _getch();
			if (c == '\r')
			{
				break;
			}
			else if (c == (char)8)
			{
				if (!result.empty())
				{
					ql::print("\b \b");
					result.pop_back();
				}
			}
			else
			{
				ql::print(replace);
				result += c;
			}
		}
		ql::print('\n');
		return result;
	}
}