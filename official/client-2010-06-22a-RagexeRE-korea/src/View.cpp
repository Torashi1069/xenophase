#include "View.h"


float CView::GetDestDistance()
{
	return m_dest.distance;
}


vector3d CView::GetFrom()
{
	return m_from;
}


matrix CView::GetViewMatrix()
{
	return m_invViewMatrix; // guessed
}


float CView::GetCurLongitude()
{
	return m_cur.longitude;
}
