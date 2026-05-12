#ifndef V8READER_CORE_V8READERCORE_H
#define V8READER_CORE_V8READERCORE_H

#include <string>
#include <vector>

namespace v8reader::core {

struct Result {
	int code = 0;

	bool ok() const noexcept
	{
		return code == 0;
	}
};

struct FileListResult : Result {
	std::vector<std::string> names;
};

Result parse_to_folder(const std::string &filename,
	const std::string &output_dir,
	const std::vector<std::string> &filter = {});

Result unpack_to_folder(const std::string &filename,
	const std::string &output_dir,
	const std::string &block_name = {},
	bool print_progress = false);

Result build_cf_file(const std::string &input_dir,
	const std::string &output_filename,
	bool dont_deflate = false);

FileListResult list_file_names(const std::string &filename);

Result inflate_file(const std::string &input_filename,
	const std::string &output_filename);

Result deflate_file(const std::string &input_filename,
	const std::string &output_filename);

bool try_inflate_file(const std::string &input_filename,
	const std::string &output_filename);

} // namespace v8reader::core

#endif // V8READER_CORE_V8READERCORE_H
