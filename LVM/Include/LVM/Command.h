/*
Copyright 2018 creatorlxd

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include "stdafx.h"

namespace LVM
{
	class LVMVirtualMechine;
	class CommandTypeManager;
	struct Command;

	using CommandFunctionType = std::function<void(const Command&,LVMVirtualMechine &)>;

	using ArgumentModeType = unsigned int;
	
	constexpr ArgumentModeType GetBoolNumber(const std::initializer_list<bool> content)
	{
	    ArgumentModeType re = 0;
	    ArgumentModeType cot = 0;
	    for (auto i : content)
	    {
	        if (i)
	            re |= 1 << cot;
	        cot += 1;
	    }
		return re;
	}

	/*����ֵʹ��������һ������ĵ�n�������Ƿ��ǵ�ַ*/
	constexpr ArgumentModeType GetArgumentMode(const std::initializer_list<bool> content)
	{
	    return GetBoolNumber(content);
	}

	/*
	type_name������������͵�������
	index������������͵����
	argument_modeʹ������������������͵ĵ�n�������Ƿ��ǵ�ַ
	func�����������������еĺ���
	*/
	struct CommandType
	{
		CommandType(const std::string &type_name = "NullCommandType", Byte index = 0, ArgumentModeType argument_mode = 0, const CommandFunctionType &func = [&](const Command&,LVMVirtualMechine &) -> void {});
		std::string m_Name;
		Byte m_Index;
		ArgumentModeType m_ArgumentMode;
		CommandFunctionType m_RunFunction;
	};

	void NewCommandType(const CommandType& command_type);

	CommandTypeManager& GetCommandTypeManager();

	class CommandTypeManager
	{
		public:
			static const Byte MaxCommandTypeIndex=255;

			friend CommandTypeManager& GetCommandTypeManager();
			
			void InsertCommandType(const CommandType& command_type);
			const CommandType* GetCommandTypeByName(const std::string& name);
			const CommandType* GetCommandTypeByIndex(Byte index);
		private:
			CommandTypeManager();

			std::map<std::string,CommandType> m_Content;
			std::array<const CommandType*,MaxCommandTypeIndex> m_IndexList;
	};

	struct DefineCommandType
	{
		DefineCommandType(Byte index, const std::string& name, ArgumentModeType argument_mode, CommandFunctionType func = [&](const Command&, LVMVirtualMechine &) -> void {});
	};
}