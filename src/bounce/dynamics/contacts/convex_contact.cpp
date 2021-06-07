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

#include <bounce/dynamics/contacts/convex_contact.h>
#include <bounce/dynamics/shapes/shape.h>
#include <bounce/dynamics/body.h>
#include <bounce/dynamics/world.h>
#include <bounce/common/memory/block_allocator.h>

b3Contact* b3ConvexContact::Create(b3Shape* shapeA, b3Shape* shapeB, b3BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b3ConvexContact));
	return new (mem) b3ConvexContact(shapeA, shapeB);
}

void b3ConvexContact::Destroy(b3Contact* contact, b3BlockAllocator* allocator)
{
	b3ConvexContact* c = (b3ConvexContact*)contact;
	c->~b3ConvexContact();
	allocator->Free(c, sizeof(b3ConvexContact));
}

b3ConvexContact::b3ConvexContact(b3Shape* shapeA, b3Shape* shapeB) : b3Contact(shapeA, shapeB)
{
	B3_NOT_USED(shapeA);
    B3_NOT_USED(shapeB);

	m_type = e_convexContact;

	m_manifoldCapacity = 1;
	m_manifolds = &m_stackManifold;
	m_manifoldCount = 0;

	m_cache.simplexCache.count = 0;
	m_cache.featureCache.m_featurePair.state = b3SATCacheType::e_empty;
}

bool b3ConvexContact::TestOverlap()
{
	b3Shape* shapeA = GetShapeA();
	b3Transform xfA = shapeA->GetBody()->GetTransform();

	b3Shape* shapeB = GetShapeB();
	b3Transform xfB = shapeB->GetBody()->GetTransform();

	return b3TestOverlap(xfA, 0, shapeA, xfB, 0, shapeB, &m_cache);
}