#include <pydbc/descriptions/floating_point_description.h>

#include <sqlext.h>

#include <boost/variant/get.hpp>
#include <cstring>

namespace pydbc {

floating_point_description::floating_point_description() = default;
floating_point_description::~floating_point_description() = default;

std::size_t floating_point_description::do_element_size() const
{
	return sizeof(double);
}

SQLSMALLINT floating_point_description::do_column_c_type() const
{
	return SQL_C_DOUBLE;
}

SQLSMALLINT floating_point_description::do_column_sql_type() const
{
	return SQL_DOUBLE;
}

field floating_point_description::do_make_field(char const * data_pointer) const
{
	return {*reinterpret_cast<double const *>(data_pointer)};
}

void floating_point_description::do_set_field(cpp_odbc::writable_buffer_element & element, field const & value) const
{
	auto const as_double = boost::get<double>(value);
	memcpy(element.data_pointer, &as_double, element_size());
	element.indicator = element_size();
}

}