#pragma once

struct DataType {
	enum class Type
	{
		BOOL,
		UINT8,
		UINT16,
		UINT32,
		UINT64,
		INT8,
		INT16,
		INT32,
		INT64,
		FLOAT,
		DOUBLE,
		STRING,
		CUSTOM,
	};

	bool isRepeated{ false };
	Type type;
	std::string typeName;
};