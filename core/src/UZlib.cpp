#include "UZlib.h"

#include <array>
#include <cassert>

namespace
{
constexpr std::size_t kChunkSize = 16384;
}

void ZInflateStream(v8reader::core::io::IByteStream& src, v8reader::core::io::IByteStream& dst)
{
	z_stream strm{};
	std::array<unsigned char, kChunkSize> in{};
	std::array<unsigned char, kChunkSize> out{};

	int ret = inflateInit2(&strm, -MAX_WBITS);
	if(ret != Z_OK)
		return;

	do
	{
		strm.avail_in = static_cast<uInt>(src.Read(in.data(), in.size()));
		if(strm.avail_in == 0)
			break;

		strm.next_in = in.data();

		do
		{
			strm.avail_out = static_cast<uInt>(out.size());
			strm.next_out = out.data();
			ret = inflate(&strm, Z_NO_FLUSH);

			if(ret == Z_NEED_DICT)
				ret = Z_DATA_ERROR;
			if(ret == Z_DATA_ERROR || ret == Z_MEM_ERROR || ret == Z_STREAM_ERROR)
			{
				(void)inflateEnd(&strm);
				return;
			}

			const std::size_t have = out.size() - static_cast<std::size_t>(strm.avail_out);
			if(have != 0)
				dst.Write(out.data(), have);
		}
		while(strm.avail_out == 0);
	}
	while(ret != Z_STREAM_END);

	(void)inflateEnd(&strm);
}

void ZDeflateStream(v8reader::core::io::IByteStream& src, v8reader::core::io::IByteStream& dst)
{
	z_stream strm{};
	std::array<unsigned char, kChunkSize> in{};
	std::array<unsigned char, kChunkSize> out{};

	int ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
	if(ret != Z_OK)
		return;

	int flush = Z_NO_FLUSH;

	do
	{
		strm.avail_in = static_cast<uInt>(src.Read(in.data(), in.size()));
		strm.next_in = in.data();
		flush = (strm.avail_in == 0) ? Z_FINISH : Z_NO_FLUSH;

		do
		{
			strm.avail_out = static_cast<uInt>(out.size());
			strm.next_out = out.data();
			ret = deflate(&strm, flush);
			if(ret == Z_STREAM_ERROR)
			{
				(void)deflateEnd(&strm);
				return;
			}

			const std::size_t have = out.size() - static_cast<std::size_t>(strm.avail_out);
			if(have != 0)
				dst.Write(out.data(), have);
		}
		while(strm.avail_out == 0);
	}
	while(flush != Z_FINISH || ret != Z_STREAM_END);

	(void)deflateEnd(&strm);
}

int inf(FILE* source, FILE* dest)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[kChunkSize];
	unsigned char out[kChunkSize];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit2(&strm, -MAX_WBITS);
	if(ret != Z_OK)
		return ret;

	do
	{
		strm.avail_in = fread(in, 1, kChunkSize, source);
		if(ferror(source))
		{
			(void)inflateEnd(&strm);
			return Z_ERRNO;
		}
		if(strm.avail_in == 0)
			break;
		strm.next_in = in;

		do
		{
			strm.avail_out = kChunkSize;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);
			switch(ret)
			{
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
					return ret;
			}
			have = kChunkSize - strm.avail_out;
			if(fwrite(out, 1, have, dest) != have || ferror(dest))
			{
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
		}
		while(strm.avail_out == 0);
	}
	while(ret != Z_STREAM_END);

	(void)inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int def(FILE* source, FILE* dest, int level)
{
	int ret;
	int flush;
	unsigned have;
	z_stream strm;
	unsigned char in[kChunkSize];
	unsigned char out[kChunkSize];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, level);
	if(ret != Z_OK)
		return ret;

	do
	{
		strm.avail_in = fread(in, 1, kChunkSize, source);
		if(ferror(source))
		{
			(void)deflateEnd(&strm);
			return Z_ERRNO;
		}
		flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
		strm.next_in = in;

		do
		{
			strm.avail_out = kChunkSize;
			strm.next_out = out;
			ret = deflate(&strm, flush);
			assert(ret != Z_STREAM_ERROR);
			have = kChunkSize - strm.avail_out;
			if(fwrite(out, 1, have, dest) != have || ferror(dest))
			{
				(void)deflateEnd(&strm);
				return Z_ERRNO;
			}
		}
		while(strm.avail_out == 0);
		assert(strm.avail_in == 0);
	}
	while(flush != Z_FINISH);
	assert(ret == Z_STREAM_END);

	(void)deflateEnd(&strm);
	return Z_OK;
}
