#include <ql/core/system/clipboard/clipboard.hpp>

#ifdef QL_SFML
namespace ql::detail
{
	sf::Clipboard clipboard;
}
#endif