/*----------------------------------------------------------
This Source Code Form is subject to the terms of the
Mozilla Public License, v.2.0. If a copy of the MPL
was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.
----------------------------------------------------------*/

#include <sstream>
#include "VersionFile.h"
namespace v8unpack {

VersionFile::VersionFile() : m_compatibility(COMPATIBILITY_DEFAULT)
{ }

VersionFile VersionFile::parse(std::basic_istream<char> &ins)
{
	VersionFile result;
	int open_count = 3;
	while (open_count) {
		auto c = ins.get();
		if (!ins) {
			return result;
		}
		if (c == '{') {
			open_count--;
		}
	}
	int version = 0;
	while (ins) {
		auto c = ins.get();
		if (!ins || c == ',') {
			break;
		}
		if (c >= '0' && c <= '9') {
			version = version*10 + (c - '0');
		}
	}

	result.set_compatibility(version);

	return result;
}

void VersionFile::set_compatibility(int compatibility)
{
	m_compatibility = compatibility;
}

int VersionFile::compatibility() const
{
	return m_compatibility;
}

}