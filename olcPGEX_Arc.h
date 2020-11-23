/*
	+-------------------------------------------------------------+
	|         OneLoneCoder Pixel Game Engine Extension        |
	|                     Arc Drawing Routines	                  	   |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	This is an extension to the olcPixelGameEngine which provides
	additional drawing routines for rendering circular arcs
	of variable dimension, colour and resolution.

	License (OLC-3)
	~~~~~~~~~~~~~~~
	Copyright 2018 - 2019 OneLoneCoder.com
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.
	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	Author
	~~~~~~
	Carl Kavanagh, aka AlterEgo
*/

#include "olcPixelGameEngine.h"

#ifndef OLC_PGEX_ARCS
#define OLC_PGEX_ARCS

namespace olc
{
	class Arc : public olc::PGEX
	{
	private:
		Arc();

	public:
		static void Draw(double x, double y, double radius, double startAngle, double range, olc::Pixel p = olc::WHITE, int resolution = 32);
		static void Draw(const olc::vd2d& position, double radius, double startAngle, double range, olc::Pixel p = olc::WHITE, int resolution = 32);
		static void Fill(double x, double y, double radius, double startAngle, double range, olc::Pixel p = olc::WHITE, int resolution = 32);
		static void Fill(const olc::vd2d& position, double radius, double startAngle, double range, olc::Pixel p = olc::WHITE, int resolution = 32);
	};
}

#ifdef OLC_PGEX_ARC
#undef OLC_PGEX_ARC

namespace olc
{
	Arc::Arc() {}

	void Arc::Draw(double x, double y, double radius, double startAngle, double range, olc::Pixel p, int resolution)
	{
		double angle = range / resolution; // angle of increment between points
		double deltaX = cos(angle); // change along the x axis each increment
		double deltaY = -sin(angle); // change along the y axis each increment
		double pointX = cos(startAngle) * radius; // first point along the x axis on the arc
		double pointY = -sin(startAngle) * radius; // first point along the y axis on the arc
		double prevX = pointX; // track the previous point on the x axis
		double prevY = pointY; // track the previous point on the y axis

		// for every point on the arc
		for(int i = 0; i < resolution; ++i)
		{
			// calculate the next point on the arc by rotating the current point
			// by the fixed rate of change along the x and y axes
			double temp = pointX * deltaX - pointY * deltaY;
			pointY = pointX * deltaY + pointY * deltaX;
			pointX = temp;

			// connect the plotted points
			pge->DrawLine(x + prevX, y + prevY, x + pointX, y + pointY, p);

			prevX = pointX; // track the previous point on the x axis
			prevY = pointY; // track the previous point on the y axis
		}
	}

	void Arc::Draw(const olc::vd2d& position, double radius, double startAngle, double range, olc::Pixel p, int resolution)
	{
		Arc::Draw(position.x, position.y, radius, startAngle, range, p, resolution);
	}

	void Arc::Fill(double x, double y, double radius, double startAngle, double range, olc::Pixel p, int resolution)
	{
		double angle = range / resolution; // angle of increment between points
		double deltaX = cos(angle); // change along the x axis each increment
		double deltaY = -sin(angle); // change along the y axis each increment
		double pointX = cos(startAngle) * radius; // first point along the x axis on the arc
		double pointY = -sin(startAngle) * radius; // first point along the y axis on the arc
		double prevX = pointX; // track the previous point on the x axis
		double prevY = pointY; // track the previous point on the y axis

		// for every point on the arc
		for(int i = 0; i < resolution; ++i)
		{
			// calculate the next point on the arc by rotating the current point
			// by the fixed rate of change along the x and y axes
			double temp = pointX * deltaX - pointY * deltaY;
			pointY = pointX * deltaY + pointY * deltaX;
			pointX = temp;

			// fill in the plotted points
			pge->FillTriangle(x, y, x + prevX, y + prevY, x + pointX, y + pointY, p);

			prevX = pointX; // track the previous point on the x axis
			prevY = pointY; // track the previous point on the y axis
		}
	}

	void Arc::Fill(const olc::vd2d& position, double radius, double startAngle, double range, olc::Pixel p, int resolution)
	{
		Arc::Fill(position.x, position.y, radius, startAngle, range, p, resolution);
	}
}

#endif
#endif
