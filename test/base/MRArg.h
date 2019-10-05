#pragma once

#include <vector>
#include <string>

namespace muranbase{

	class MRArg{
	public:
		struct _MRArg{
			int   argc;
			char* argv[];
		};
	private:
		_MRArg *ptr;
        bool    bDeleteArgv;
	public:
		MRArg(int argc, char* argv[],   bool cloneArgvs     = false);
        MRArg(const char* command_line, bool append_nullptr = false);
        MRArg(std::vector<std::string>& vct,      bool append_nullptr = false);
		MRArg(const MRArg& o);
		~MRArg();
	public:
		void erase(int idx);
		_MRArg* operator->(){return ptr;}
	
	};

} // end namespace muranbase
