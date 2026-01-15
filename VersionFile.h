/*----------------------------------------------------------
This Source Code Form is subject to the terms of the
Mozilla Public License, v.2.0. If a copy of the MPL
was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.
----------------------------------------------------------*/

#ifndef V8UNPACK_VERSIONFILE_H
#define V8UNPACK_VERSIONFILE_H

#include <string>

namespace v8unpack {

class VersionFile
{
public:

	const static int COMPATIBILITY_V80316 = 80316;
	const static int COMPATIBILITY_DEFAULT = 0;
	const static int COMPATIBILITY_UNSUPPORTED = -1;

	VersionFile();
	int compatibility() const;

	static VersionFile parse(std::basic_istream<char> &ins);

private:
	void set_compatibility(int compatibility);
	int m_compatibility = COMPATIBILITY_UNSUPPORTED;
};

}

#endif //V8UNPACK_VERSIONFILE_H
