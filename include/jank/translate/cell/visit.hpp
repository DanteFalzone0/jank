#pragma once

#include <jank/translate/cell/cell.hpp>

namespace jank
{
  namespace translate
  {
    namespace cell
    {
      /* Follows the same pattern as parse::cell::visit. */
      template <typename Cell, typename Function>
      auto visit(Cell &&c, Function const &func)
      {
        switch(static_cast<type>(c.which()))
        {
          case type::function_body:
            return func(boost::get<function_body>(c));
          case type::function_definition:
            return func(boost::get<function_definition>(c));
          case type::native_function_definition:
            return func(boost::get<native_function_definition>(c));
          case type::function_call:
            return func(boost::get<function_call>(c));
          case type::native_function_call:
            return func(boost::get<native_function_call>(c));
          case type::type_definition:
            return func(boost::get<type_definition>(c));
          case type::type_reference:
            return func(boost::get<type_reference>(c));
          case type::variable_definition:
            return func(boost::get<variable_definition>(c));
          case type::variable_reference:
            return func(boost::get<variable_reference>(c));
          case type::literal_value:
            return func(boost::get<literal_value>(c));
          case type::return_statement:
            return func(boost::get<return_statement>(c));
          case type::if_statement:
            return func(boost::get<if_statement>(c));
          default:
            throw std::runtime_error{ "invalid visit on translation cell" };
        }
      }
    }
  }
}
