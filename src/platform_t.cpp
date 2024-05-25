#include <wideopencl/platform_t.h>
#include <wideopencl/error.h>

#include <stdexcept>


namespace wideopencl{


std::vector<platform_t> platform_t::find(){
	std::vector<cl_platform_id> platform_ids;
	{
		cl_uint num_platforms = 0;
		const auto error = clGetPlatformIDs(0, NULL, &num_platforms);
		if(error != CL_SUCCESS){
			throw std::runtime_error("clGetPlatformIDs() failed with: " + error_string(error));
		}
		platform_ids.resize(num_platforms);
	}
	{
		const auto error = clGetPlatformIDs(platform_ids.size(), platform_ids.data(), NULL);
		if(error != CL_SUCCESS){
			throw std::runtime_error("clGetPlatformIDs() failed with: " + error_string(error));
		}
	}

	std::vector<platform_t> result;
	for(const auto &platform_id : platform_ids){
		platform_t platform;
		platform.id = platform_id;

		size_t name_size = 0;
		{
			const auto error = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, NULL, &name_size);
			if(error != CL_SUCCESS){
				throw std::runtime_error("clGetPlatformInfo(CL_PLATFORM_NAME) failed with: " + error_string(error));
			}
		}
		{
			std::vector<char> data(name_size);
			const auto error = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, data.size(), data.data(), NULL);
			if(error != CL_SUCCESS){
				throw std::runtime_error("clGetPlatformInfo(CL_PLATFORM_NAME) failed with: " + error_string(error));
			}
			platform.name = std::string(data.begin(), data.end());
		}

		size_t version_size = 0;
		{
			const auto error = clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, 0, NULL, &version_size);
			if(error != CL_SUCCESS){
				throw std::runtime_error("clGetPlatformInfo(CL_PLATFORM_VERSION) failed with: " + error_string(error));
			}
		}
		{
			std::vector<char> data(version_size);
			const auto error = clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, data.size(), data.data(), NULL);
			if(error != CL_SUCCESS){
				throw std::runtime_error("clGetPlatformInfo(CL_PLATFORM_VERSION) failed with: " + error_string(error));
			}
			platform.version = std::string(data.begin(), data.end());
		}

		result.push_back(platform);
	}

	return result;
}


platform_t platform_t::find(const std::string &name){
	for(const auto &platform : find()){
		if(platform.name == name){
			return platform;
		}
	}
	throw std::runtime_error("No such OpenCL platform: '" + name + "'");
}


platform_t platform_t::choose(){
	const auto platforms = find();
	if(platforms.empty()){
		throw std::logic_error("No OpenCL platforms available");
	}
	return platforms.front();
}


}
