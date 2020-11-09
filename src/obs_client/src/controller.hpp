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

#pragma once
#include <memory>
#include <string>
#include "ipc-client.hpp"
#include <napi.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>
#endif

struct ProcessInfo
{
	uint64_t handle;
	uint64_t id;

	ProcessInfo()
	{
		this->handle = 0;
		this->id     = 0;
	};
	ProcessInfo(uint64_t h, uint64_t i)
	{
		this->handle = h;
		this->id     = i;
	}
};

class Controller
{
	public:
	static Controller& GetInstance()
	{
		static Controller _inst;
		return _inst;
	}

	private:
	Controller();
	~Controller();

	public: // C++11
	Controller(Controller const&) = delete;
	void operator=(Controller const&) = delete;

	static void Init(Napi::Env env, Napi::Object exports);

	public:
	std::shared_ptr<ipc::client> host(const std::string& uri);

	std::shared_ptr<ipc::client> connect(const std::string& uri);

	void disconnect();

	std::shared_ptr<ipc::client> GetConnection();

	private:
	bool                         m_isServer = false;
	std::shared_ptr<ipc::client> m_connection;
	ProcessInfo                  procId;
};
