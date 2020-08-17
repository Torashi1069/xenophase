#pragma once


class CMyPoint
{
public:
	CMyPoint(const int in_x, const int in_y) : m_x(in_x), m_y(in_y) { }

public:
	int x() const { return m_x; }
	int y() const { return m_y; }

private:
	/* this+0 */ int m_x;
	/* this+4 */ int m_y;
};


class CMyRect
{
public:
	CMyRect(const int in_left, const int in_top, const int in_width, const int in_height) : m_left(in_left), m_top(in_top), m_width(in_width), m_height(in_height) { }

public:
	int left() const   { return m_left;               }
	int top() const    { return m_top;                }
	int right() const  { return m_left + m_width - 1; }
	int bottom() const { return m_top + m_height - 1; }

	int centerXpos() const; //TODO
	int centerYpos() const; //TODO

	int width() const  { return m_width;  }
	int height() const { return m_height; }

	CMyPoint LeftTop() const     { return CMyPoint(left(), top());     }
	CMyPoint RightTop() const    { return CMyPoint(right(), top());    }
	CMyPoint LeftBottom() const  { return CMyPoint(left(), bottom());  }
	CMyPoint RightBottom() const { return CMyPoint(right(), bottom()); }

	bool IsMyPoint(const CMyPoint& in_Point) const
	{
		return ( in_Point.CMyPoint::x() >= left()
		      && in_Point.CMyPoint::x() <= right()
		      && in_Point.CMyPoint::y() >= top()
		      && in_Point.CMyPoint::y() <= bottom() );
	}

	bool IsIntersection(const CMyRect& in_Area) const
	{
		return ( this->CMyRect::IsMyPoint(LeftTop())
		      || this->CMyRect::IsMyPoint(LeftBottom())
		      || this->CMyRect::IsMyPoint(RightTop())
		      || this->CMyRect::IsMyPoint(RightBottom())
		      || in_Area.CMyRect::IsMyPoint(LeftTop())
		      || in_Area.CMyRect::IsMyPoint(LeftBottom())
		      || in_Area.CMyRect::IsMyPoint(RightTop())
		      || in_Area.CMyRect::IsMyPoint(RightBottom()) );
	}

private:
	/* this+ 0 */ int m_left;
	/* this+ 4 */ int m_top;
	/* this+ 8 */ int m_width;
	/* this+12 */ int m_height;
};
