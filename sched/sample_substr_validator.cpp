// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2014 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

// A sample validator that accepts results whose stderr output
// contains or doesn't contain a given string.
// Usage:
// sample_substr_validator --stderr_string xxx [--reject_if_present]] [other options]
// --reject_if_present: reject (invalidate) the result if the string is present
// (default: accept it if the string is present)

#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "sched_msgs.h"
#include "sched_util_basic.h"
#include "validate_util.h"
#include "validate_util2.h"
#include "validator.h"
#include "md5_file.h"

using std::vector;


int validate_handler_init(int argc, char** argv)
{
    return 0;
}

void validate_handler_usage() {
}

int init_result(RESULT& result, void*& output_data)
{
    if(result.name == NULL)
        return -1;
    
    std::string* output = new std::string("");
    OUTPUT_FILE_INFO fi;
    get_output_file_info(result, fi);

    char md5_buf[MD5_LEN];
    double nbytes;

    int retval = md5_file(fi.path.c_str(), md5_buf, nbytes, false);
    output->append(md5_buf);

    output_data = (void*) output;
    return 0;
}

int compare_results(RESULT& res, void*data1, RESULT const& res2, void*data2, bool& match)
{
    std::string* md5[2] = {
        static_cast<std::string*>(data1),
        static_cast<std::string*>(data2),
    };

    int retval = md5[0]->compare(*md5[1]);
    match = (retval == 0);

    return 0;
}

int cleanup_result(RESULT const&, void*) {
    return 0;
}

const char *BOINC_RCSID_f3a7a34795 = "$Id$";
