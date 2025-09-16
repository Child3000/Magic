// Copyright Bear Child

#pragma once

struct FMGMath
{
	static float SafeDivide(float A, float B)
	{
		if (B == 0)
		{
			return 0;
		}
		return A / B;
	}
	
	static double SafeDivide(double A, double B)
	{
		if (B == 0)
		{
			return 0;
		}
		return A / B;
	}
};
