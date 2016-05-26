#pragma once

enum class PrimitiveType
{
	kPointLIST = 0,
	kLineList,
	kLineStrip,
	kTriangleList,
	kTriangleStrip,
	kTriangleFan,
};

enum class FillMode
{
	kPoint = 0,
	kWireFrame,
	kSolid,
};