/******************************************************************************
    Copyright (C) 2016-2019 by Streamlabs (General Workings Inc)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************************************/

#include "utility.hpp"
#include <codecvt>
#include <locale>

#include <sstream>
#include <fstream>

// This is from enc-amf
#if (defined _WIN32) || (defined _WIN64) // Windows

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifdef WINVER
#undef WINVER
#endif
#define WINVER 0x601

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x601

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)
typedef struct tagTHREADNAME_INFO
{
	DWORD  dwType;     // Must be 0x1000.
	LPCSTR szName;     // Pointer to name (in user addr space).
	DWORD  dwThreadID; // Thread ID (-1=caller thread).
	DWORD  dwFlags;    // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void utility::SetThreadName(uint32_t dwThreadID, const char* threadName)
{
	// DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( t.native_handle() ) );

	THREADNAME_INFO info;
	info.dwType     = 0x1000;
	info.szName     = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags    = 0;

	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}
}
void utility::SetThreadName(const char* threadName)
{
	utility::SetThreadName(GetCurrentThreadId(), threadName);
}
#endif

static thread_local std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

std::string from_utf16_wide_to_utf8(const wchar_t* from, size_t length)
{
	const wchar_t* from_end;

	if (length == 0)
		return {};
	else if (length != -1)
		from_end = from + length;
	else
		return converter.to_bytes(from);

	return converter.to_bytes(from, from_end);
}

std::wstring from_utf8_to_utf16_wide(const char* from, size_t length)
{
	const char* from_end;

	if (length == 0)
		return {};
	else if (length != -1)
		from_end = from + length;
	else
		return converter.from_bytes(from);

	return converter.from_bytes(from, from_end);
}

std::string read_app_state_data(std::string app_state_path)
{
	std::ostringstream buffer; 
 	std::ifstream state_file(app_state_path, std::ios::in);
	if (state_file.is_open())
	{
		buffer << state_file.rdbuf(); 
		state_file.close();
		return buffer.str();
	} 
	return "";
}

void write_app_state_data(std::string app_state_path, std::string updated_status)
{
	std::ofstream out_state_file;
	out_state_file.open(app_state_path, std::ios::trunc | std::ios::out );
	if (out_state_file.is_open()) {
		out_state_file << updated_status << "\n";
		out_state_file.flush();
		out_state_file.close();
	}
}

void ipc_freez_callback(bool freez_detected, std::string app_state_path)
{
	static int freez_counter = 0;
	if (freez_detected) {
		freez_counter++;
		if (freez_counter > 1) {
			return;
		}
	} else {
		freez_counter--;
		if (freez_counter > 0) {
			return;
		}
	}
	const std::string flag_value = "ipc_freez";
	const std::string flag_name = "detected";

	app_state_path += "\\appState";
	std::string current_status = read_app_state_data(app_state_path);

}
