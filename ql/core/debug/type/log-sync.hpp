#include <ql/core/system/print/print.hpp>
#include <ql/graphic/sync/state.hpp>

namespace ql
{
  namespace debug
  {
    template<typename T>
    struct log_sync
    {
      ql_sync_within
      (
        T instance; // the wrapped instance of T
      );

      // forwarding constructor: takes any arguments, logs their types,
      // and forwards them to construct the T instance
      template <typename... Args>
	  constexpr log_sync(Args&&... args) : sync(std::forward<Args>(args)...)
      {
        ql::println(ql::color::aqua, ql::type_name<T>(), "( ", ql::color::aqua, ql::type_name<Args>()..., " ) ", ql::color::bright_gray, "// argument construction ", ql::color::blue, this);
      }

      // copy constructor
	  constexpr log_sync() noexcept : sync()
      {
        ql::println(ql::color::aqua, ql::type_name<T>(), "() ", ql::color::bright_gray, "// default construction ", ql::color::blue, this);
      }

      // copy constructor
      constexpr log_sync(const log_sync<T>& other) noexcept : sync(other.sync)
      {
        ql::println(ql::color::aqua, ql::type_name<T>(), "( const ", ql::color::aqua, ql::type_name<T>(), "& ) ", ql::color::bright_gray, "// copy construction ", ql::color::blue, this);
      }

      //// move constructor
      constexpr log_sync(log_sync<T>&& other) noexcept : sync(std::move(other.sync))
      {
        ql::println(ql::color::aqua, ql::type_name<T>(), "( ", ql::color::aqua, ql::type_name<T>(), "&& ) ", ql::color::bright_gray, "// move construction ", ql::color::blue, this);
      }

      // copy assignment operator
      constexpr const log_sync<T>& operator=(const log_sync<T>& other)
      {
        this->sync.instance = other.sync.instance;
        ql::println(ql::color::aqua, ql::type_name<T>(), "::operator=( const ", ql::color::aqua, ql::type_name<T>(), "& ) ", ql::color::bright_gray, "// copy assignment ", ql::color::blue, this);
        return *this;
      }

      // move assignment operator
      constexpr log_sync<T>& operator=(log_sync<T>&& other) noexcept
      {
        this->sync.instance = std::move(other.sync.instance);
        ql::println(ql::color::aqua, ql::type_name<T>(), "::operator=( ", ql::color::aqua, ql::type_name<T>(), "&& ) ", ql::color::bright_gray, "// move assignment ", ql::color::blue, this);
        return *this;
      }

      // destructor
      constexpr ~log_sync()
      {
        ql::println("~", ql::color::aqua, ql::type_name<T>(), "() ", ql::color::bright_gray, "// destruction ", ql::color::blue, this);
      }

      // --- method and member forwarding ---

      // member access operator (const and non-const)
      template <typename T>
      constexpr operator T&() noexcept
      {
        return this->instance;
      }

      template <typename T>
      constexpr operator const T&() const noexcept
      {
        return this->instance;
      }

      template <typename T>
      constexpr operator T&& () noexcept
      {
        return std::move(this->instance);
      }

      template <typename T>
      constexpr operator const T&& () const noexcept
      {
        return std::move(this->instance);
      }
    };
  }
}