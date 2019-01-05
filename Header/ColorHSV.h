#pragma once

struct ColorHSV
{
public:
	ColorHSV(int hue, int saturation, int value)
		: m_hue(hue)
		, m_saturation(saturation)
		, m_value(value)
	{

	}
	int hue() { return m_hue; }
	int saturation() { return m_saturation; }
	int value() { return m_value; }

private:
	const int m_hue;
	const int m_saturation;
	const int m_value;
};
