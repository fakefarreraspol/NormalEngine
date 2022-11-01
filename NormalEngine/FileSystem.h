#pragma once
#ifndef _MODULE_FS_H_
#define _MODULE_FS_H_

#include "Application.h"
#include "Module.h"


class FileSystem : public Module
{
public:
	FileSystem(Application* app, bool start_enabled = true);
	~FileSystem();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	bool AddPath(const char* filePath);

	uint Load(const char* file_path, char** buffer_path);
	uint Save(const char* file_path, const void* buffer, unsigned int size, bool append);
	std::string GetFileExtension(const char* file_path);

public:

};

#endif // !_MODULE_FS_H_