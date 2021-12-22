#pragma once

class DataType
{
	enum class Type
	{
		BOOL,
		UINT32,
		UINT64,
		FLOAT,
		DOUBLE,
		STRING,
		CUSTOM,
	};

	Type type;
	std::string typeName;
};