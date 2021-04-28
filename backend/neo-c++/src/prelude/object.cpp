#include <prelude/object.hpp>
#include <prelude/number.hpp>

namespace jank
{
  object_ptr JANK_NIL{ make_object_ptr<nil>() };

  detail::boolean_type nil::equal(object const &o) const
  {
    auto const *b(dynamic_cast<boolean const*>(&o));
    return b != nullptr;
  }
  detail::string_type nil::to_string() const
  /* TODO: Optimize. */
  { return "nil"; }
  detail::integer_type nil::to_hash() const
  { return 0; }
}
