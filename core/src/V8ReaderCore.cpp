#include "v8reader_core/V8ReaderCore.h"

#include "V8File.h"

#include <filesystem>

namespace v8reader::core {

Result parse_to_folder(const std::string &filename,
	const std::string &output_dir,
	const std::vector<std::string> &filter)
{
	return {v8unpack::Parse(filename, output_dir, filter)};
}

Result unpack_to_folder(const std::string &filename,
	const std::string &output_dir,
	const std::string &block_name,
	bool print_progress)
{
	return {v8unpack::UnpackToFolder(filename, output_dir, block_name, print_progress)};
}

Result build_cf_file(const std::string &input_dir,
	const std::string &output_filename,
	bool dont_deflate)
{
	return {v8unpack::BuildCfFile(input_dir, output_filename, dont_deflate)};
}

FileListResult list_file_names(const std::string &filename)
{
	FileListResult result;
	result.code = v8unpack::ListFileNames(filename, result.names);
	return result;
}

Result inflate_file(const std::string &input_filename,
	const std::string &output_filename)
{
	return {v8unpack::Inflate(input_filename, output_filename)};
}

Result deflate_file(const std::string &input_filename,
	const std::string &output_filename)
{
	return {v8unpack::Deflate(input_filename, output_filename)};
}

bool try_inflate_file(const std::string &input_filename,
	const std::string &output_filename)
{
	return v8unpack::try_inflate(std::filesystem::path(input_filename),
		std::filesystem::path(output_filename));
}

} // namespace v8reader::core
