#include <ql/core/system/clipboard/clipboard.hpp>

#if defined QL_GRAPHIC
namespace ql::detail
{
	sf::Clipboard clipboard;
}
#endif