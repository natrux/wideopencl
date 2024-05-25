#pragma once

#include <wideopencl/Buffer.h>
#include <wideopencl/device_t.h>

#include <vector>
#include <array>

#include <CL/cl.h>


namespace wideopencl{


class Kernel;

class CommandQueue{
public:
	CommandQueue(cl_command_queue queue, const device_t &device);
	~CommandQueue();
	CommandQueue(const CommandQueue &other) = delete;
	CommandQueue &operator=(const CommandQueue &other) = delete;

	void read(const Buffer &buffer, void *data);
	void write(Buffer &buffer, const void *data);
	void execute(const Kernel &kernel, size_t global);
	void execute(const Kernel &kernel, size_t global, size_t local);
	void execute(const Kernel &kernel, const std::vector<size_t> &global);
	void execute(const Kernel &kernel, const std::vector<size_t> &global, const std::vector<size_t> &local);
	void flush();
	void finish();

private:
	cl_command_queue queue;
	device_t device;
};


}
