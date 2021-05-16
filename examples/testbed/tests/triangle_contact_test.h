/*
* Copyright (c) 2016-2019 Irlan Robson 
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef TRIANGLE_CONTACT_TEST_H
#define TRIANGLE_CONTACT_TEST_H

class TriangleContactTest : public Test
{
public:
	TriangleContactTest()
	{
		{
			b3BodyDef bdef;
			bdef.type = b3BodyType::e_staticBody;

			b3Body* body = m_world.CreateBody(bdef);

			b3TriangleShape ts;
			ts.m_vertex1.Set(-5.0f, 0.0f, 5.0f);
			ts.m_vertex2.Set(5.0f, 0.0f, 5.0f);
			ts.m_vertex3.Set(0.0f, 0.0f, -5.0f);

			b3ShapeDef sdef;
			sdef.shape = &ts;
			sdef.friction = 1.0f;

			body->CreateShape(sdef);
		}

		{
			b3BodyDef bdef;
			bdef.type = b3BodyType::e_dynamicBody;
			bdef.position.Set(0.0f, 5.0f, 0.0f);

			b3Body* body = m_world.CreateBody(bdef);

			b3HullShape hs;
			hs.m_hull = &b3BoxHull_identity;

			b3ShapeDef sdef;
			sdef.density = 0.1f;
			sdef.friction = 0.1f;
			sdef.shape = &hs;

			body->CreateShape(sdef);
		}
	}

	static Test* Create()
	{
		return new TriangleContactTest();
	}
};

#endif