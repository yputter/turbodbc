#include <turbodbc_arrow/arrow_result_set.h>
#include <turbodbc_arrow/set_arrow_parameters.h>

#include <pybind11/pybind11.h>

using turbodbc_arrow::arrow_result_set;
using turbodbc_arrow::set_arrow_parameters;

namespace {

arrow_result_set make_arrow_result_set(std::shared_ptr<turbodbc::result_sets::result_set> result_set_pointer,
    bool strings_as_dictionary)
{
	return arrow_result_set(*result_set_pointer, strings_as_dictionary);
}

}

PYBIND11_MODULE(turbodbc_arrow_support, module)
{
    module.doc() = "Native helpers for turbodbc's Apache Arrow support";

    pybind11::class_<arrow_result_set>(module, "ArrowResultSet")
        .def("fetch_all", &arrow_result_set::fetch_all);

    module.def("make_arrow_result_set", make_arrow_result_set);
    module.def("set_arrow_parameters", set_arrow_parameters);
}
