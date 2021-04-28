#include <iostream>
#include <random>
#include <cmath>

#include <prelude/number.hpp>

namespace jank
{
  /***** boolean *****/
  object_ptr JANK_TRUE{ make_object_ptr<boolean>(true) };
  object_ptr JANK_FALSE{ make_object_ptr<boolean>(false) };

  detail::boolean_type boolean::equal(object const &o) const
  {
    auto const *b(dynamic_cast<boolean const*>(&o));
    if(!b)
    { return false; }

    return data == b->data;
  }
  detail::string_type boolean::to_string() const
  /* TODO: Optimize. */
  { return data ? "true" : "false"; }
  detail::integer_type boolean::to_hash() const
  { return data ? 1 : 0; }
  detail::integer_type boolean::get_integer() const
  { return data ? 1 : 0; }
  detail::real_type boolean::get_real() const
  { return data ? 1.0 : 0.0; }

  /***** integer *****/
  detail::boolean_type integer::equal(object const &o) const
  {
    auto const *i(dynamic_cast<integer const*>(&o));
    if(!i)
    { return false; }

    return data == i->data;
  }
  detail::string_type integer::to_string() const
  { return std::to_string(data); }
  detail::integer_type integer::to_hash() const
  { return data; }
  detail::integer_type integer::get_integer() const
  { return data; }
  detail::real_type integer::get_real() const
  { return data; }

  /***** real *****/
  detail::boolean_type real::equal(object const &o) const
  {
    auto const *r(dynamic_cast<real const*>(&o));
    if(!r)
    { return false; }

    return data == r->data;
  }
  detail::string_type real::to_string() const
  { return std::to_string(data); }
  detail::integer_type real::to_hash() const
  { return static_cast<detail::integer_type>(data); }
  detail::integer_type real::get_integer() const
  { return data; }
  detail::real_type real::get_real() const
  { return data; }

  struct integer_ops;
  struct real_ops;
  struct number_ops
  {
    virtual number_ops const& combine(number_ops const&) const = 0;
    virtual number_ops const& with(integer_ops const&) const = 0;
    virtual number_ops const& with(real_ops const&) const = 0;

    /* TODO: Return number_ptr */
    virtual object_ptr add(number const &l, number const &r) const = 0;
    virtual object_ptr subtract(number const &l, number const &r) const = 0;
    virtual object_ptr multiply(number const &l, number const &r) const = 0;
    virtual object_ptr divide(number const &l, number const &r) const = 0;
    virtual object_ptr remainder(number const &l, number const &r) const = 0;
    virtual object_ptr inc(number const &n) const = 0;
    virtual object_ptr dec(number const &n) const = 0;
    virtual object_ptr negate(number const &n) const = 0;
    virtual object_ptr abs(number const &n) const = 0;
    virtual object_ptr min(number const &l, number const &r) const = 0;
    virtual object_ptr max(number const &l, number const &r) const = 0;
    virtual detail::boolean_type lt(number const &l, number const &r) const = 0;
    virtual detail::boolean_type lte(number const &l, number const &r) const = 0;
    virtual detail::boolean_type gte(number const &l, number const &r) const = 0;
    virtual detail::boolean_type equal(number const &l, number const &r) const = 0;
  };

  struct integer_ops : number_ops
  {
    number_ops const& combine(number_ops const &o) const override
    { return o.with(*this); }
    number_ops const& with(integer_ops const&) const override;
    number_ops const& with(real_ops const&) const override;
    object_ptr add(number const &l, number const &r) const override
    { return make_object_ptr<integer>(l.get_integer() + r.get_integer()); }
    object_ptr subtract(number const &l, number const &r) const override
    { return make_object_ptr<integer>(l.get_integer() - r.get_integer()); }
    object_ptr multiply(number const &l, number const &r) const override
    { return make_object_ptr<integer>(l.get_integer() * r.get_integer()); }
    object_ptr divide(number const &l, number const &r) const override
    { return make_object_ptr<integer>(l.get_integer() / r.get_integer()); }
    object_ptr remainder(number const &l, number const &r) const override
    { return make_object_ptr<integer>(l.get_integer() % r.get_integer()); }
    object_ptr inc(number const &n) const override
    { return make_object_ptr<integer>(n.get_integer() + 1); }
    object_ptr dec(number const &n) const override
    { return make_object_ptr<integer>(n.get_integer() - 1); }
    object_ptr negate(number const &n) const override
    { return make_object_ptr<integer>(-n.get_integer()); }
    object_ptr abs(number const &n) const override
    { return make_object_ptr<integer>(std::abs(n.get_integer())); }
    object_ptr min(number const &l, number const &r) const override
    { return make_object_ptr<integer>(std::min(l.get_integer(), r.get_integer())); }
    object_ptr max(number const &l, number const &r) const override
    { return make_object_ptr<integer>(std::max(l.get_integer(), r.get_integer())); }
    detail::boolean_type lt(number const &l, number const &r) const override
    { return l.get_integer() < r.get_integer(); }
    detail::boolean_type lte(number const &l, number const &r) const override
    { return l.get_integer() <= r.get_integer(); }
    detail::boolean_type gte(number const &l, number const &r) const override
    { return l.get_integer() >= r.get_integer(); }
    detail::boolean_type equal(number const &l, number const &r) const override
    { return l.get_integer() == r.get_integer(); }
  };

  struct real_ops : number_ops
  {
    number_ops const& combine(number_ops const &o) const override
    { return o.with(*this); }
    number_ops const& with(integer_ops const&) const override;
    number_ops const& with(real_ops const&) const override;
    object_ptr add(number const &l, number const &r) const override
    { return make_object_ptr<real>(l.get_real() + r.get_real()); }
    object_ptr subtract(number const &l, number const &r) const override
    { return make_object_ptr<real>(l.get_real() - r.get_real()); }
    object_ptr multiply(number const &l, number const &r) const override
    { return make_object_ptr<real>(l.get_real() * r.get_real()); }
    object_ptr divide(number const &l, number const &r) const override
    { return make_object_ptr<real>(l.get_real() / r.get_real()); }
    object_ptr remainder(number const &l, number const &r) const override
    { return make_object_ptr<real>(std::fmod(l.get_real(), r.get_real())); }
    object_ptr inc(number const &n) const override
    { return make_object_ptr<real>(n.get_real() + 1); }
    object_ptr dec(number const &n) const override
    { return make_object_ptr<real>(n.get_real() - 1); }
    object_ptr negate(number const &n) const override
    { return make_object_ptr<real>(-n.get_real()); }
    object_ptr abs(number const &n) const override
    { return make_object_ptr<real>(std::abs(n.get_real())); }
    object_ptr min(number const &l, number const &r) const override
    { return make_object_ptr<real>(std::min(l.get_real(), r.get_real())); }
    object_ptr max(number const &l, number const &r) const override
    { return make_object_ptr<real>(std::max(l.get_real(), r.get_real())); }
    detail::boolean_type lt(number const &l, number const &r) const override
    { return l.get_real() < r.get_real(); }
    detail::boolean_type lte(number const &l, number const &r) const override
    { return l.get_real() <= r.get_real(); }
    detail::boolean_type gte(number const &l, number const &r) const override
    { return l.get_real() >= r.get_real(); }
    detail::boolean_type equal(number const &l, number const &r) const override
    { return l.get_real() == r.get_real(); }
  };

  static integer_ops int_ops;
  static real_ops r_ops;

  number_ops const& integer_ops::with(integer_ops const&) const
  { return int_ops; }
  number_ops const& integer_ops::with(real_ops const&) const
  { return r_ops; }

  number_ops const& real_ops::with(integer_ops const&) const
  { return r_ops; }
  number_ops const& real_ops::with(real_ops const&) const
  { return r_ops; }

  number_ops& ops(object_ptr const &n)
  {
    auto const * const ptr(n.get());
    if(dynamic_cast<integer const*>(ptr))
    { return int_ops; }
    if(dynamic_cast<real const*>(ptr))
    { return r_ops; }

    /* TODO: Exception type. */
    throw detail::string_type{ "not a number: " } + n->to_string();
  }

  object_ptr rand()
  {
    static std::uniform_real_distribution<detail::real_type> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return make_object_ptr<real>(distribution(generator));
  }

  /* + */
  object_ptr _gen_plus_(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).add
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  /* - */
  object_ptr _gen_minus_(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).subtract
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  /* * */
  object_ptr _gen_asterisk_(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).multiply
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  /* TODO: Rename to / once the parser supports it. */
  /* / */
  object_ptr div(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).divide
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  object_ptr mod(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).remainder
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  /* < */
  object_ptr _gen_less_(object_ptr const &l, object_ptr const &r)
  {
    return make_object_ptr<boolean>
    (
      ops(l).combine(ops(r)).lt
      (
        *dynamic_cast<number const*>(l.get()),
        *dynamic_cast<number const*>(r.get())
      )
    );
  }

  /* <= */
  object_ptr _gen_less__gen_equal_(object_ptr const &l, object_ptr const &r)
  {
    return make_object_ptr<boolean>
    (
      ops(l).combine(ops(r)).lte
      (
        *dynamic_cast<number const*>(l.get()),
        *dynamic_cast<number const*>(r.get())
      )
    );
  }

  /* ->int */
  object_ptr _gen_minus__gen_greater_int(object_ptr const &o)
  {
    auto const * const n(dynamic_cast<number const*>(o.get()));
    if(!n)
    {
      /* TODO: Throw error. */
      std::cout << "(->int) not a number: " << *o << std::endl;
      return JANK_NIL;
    }
    return make_object_ptr<integer>(n->get_integer());
  }

  /* ->float */
  object_ptr _gen_minus__gen_greater_float(object_ptr const &o)
  {
    auto const * const n(dynamic_cast<number const*>(o.get()));
    if(!n)
    {
      /* TODO: Throw error. */
      std::cout << "(->float) not a number: " << *o << std::endl;
      return JANK_NIL;
    }
    return make_object_ptr<real>(n->get_real());
  }

  object_ptr inc(object_ptr const &n)
  { return ops(n).inc(*dynamic_cast<number const*>(n.get())); }

  object_ptr dec(object_ptr const &n)
  { return ops(n).dec(*dynamic_cast<number const*>(n.get())); }

  object_ptr sqrt(object_ptr const &o)
  {
    auto const * const n(dynamic_cast<number const*>(o.get()));
    if(!n)
    {
      /* TODO: Throw error. */
      std::cout << "(sqrt) not a number: " << *o << std::endl;
      return JANK_NIL;
    }
    return make_object_ptr<real>(std::sqrt(n->get_real()));
  }

  object_ptr tan(object_ptr const &o)
  {
    auto const * const n(dynamic_cast<number const*>(o.get()));
    if(!n)
    {
      /* TODO: Throw error. */
      std::cout << "(tan) not a number: " << *o << std::endl;
      return JANK_NIL;
    }
    return make_object_ptr<real>(std::tan(n->get_real()));
  }

  object_ptr pow(object_ptr const &l, object_ptr const &r)
  {
    auto const * const l_num(dynamic_cast<number const*>(l.get()));
    auto const * const r_num(dynamic_cast<number const*>(r.get()));
    if(!l_num || !r_num)
    {
      /* TODO: Throw error. */
      std::cout << "(pow) not a number: " << *l << " and " << *r << std::endl;
      return JANK_NIL;
    }
    return make_object_ptr<real>(std::pow(l_num->get_real(), r_num->get_real()));
  }

  object_ptr abs(object_ptr const &n)
  { return ops(n).abs(*dynamic_cast<number const*>(n.get())); }

  object_ptr min(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).min
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }

  object_ptr max(object_ptr const &l, object_ptr const &r)
  {
    return ops(l).combine(ops(r)).max
    (
      *dynamic_cast<number const*>(l.get()),
      *dynamic_cast<number const*>(r.get())
    );
  }
}
