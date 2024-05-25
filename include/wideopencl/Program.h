#pragma once

#include <wideopencl/Kernel.h>
#include <wideopencl/device_t.h>

#include <string>
#include <vector>
#include <memory>

#include <CL/cl.h>


namespace wideopencl{


class Program{
public:
	Program(cl_program program);
	~Program();
	Program(const Program &other) = delete;
	Program &operator=(const Program &other) = delete;

	void build(const std::vector<std::string> &options, const std::vector<device_t> &devices);
	std::vector<std::pair<device_t, std::string>> get_binaries() const;
	std::shared_ptr<Kernel> create_kernel(const std::string &name) const;

private:
	cl_program program;
};


}
