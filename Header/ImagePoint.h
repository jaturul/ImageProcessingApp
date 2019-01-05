#pragma once 

#include <utility>

struct ImagePoint
{
	ImagePoint(int row, int col) : m_point(row, col) {}

	int col() const
	{
		return m_point.second;
	}

	int row() const
	{
		return m_point.first;
	}

	inline bool operator==(const ImagePoint& otherPoint) const { return ( (this->row() == otherPoint.row()) && (this->col() == otherPoint.col()) ); }
	inline bool operator!=(const ImagePoint& otherPoint) const { return ( (this->row() != otherPoint.row()) || (this->col() == otherPoint.col()) ); }

	inline bool operator<(const ImagePoint& otherPoint)  const
	{
		if (this->col() == otherPoint.col())
		{
			return this->row() < otherPoint.row();
		}
		
		return this->col() < otherPoint.col();
	}

private:
	// both rows and cols start at 0!!!!
	const std::pair<int, int> m_point;
};
