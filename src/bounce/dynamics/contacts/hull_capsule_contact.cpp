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

#include <bounce/dynamics/contacts/hull_capsule_contact.h>
#include <bounce/dynamics/shapes/hull_shape.h>
#include <bounce/dynamics/shapes/capsule_shape.h>
#include <bounce/dynamics/body.h>
#include <bounce/common/memory/block_allocator.h>

b3Contact* b3HullAndCapsuleContact::Create(b3Shape* shapeA, b3Shape* shapeB, b3BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b3HullAndCapsuleContact));
	return new (mem) b3HullAndCapsuleContact(shapeA, shapeB);
}

void b3HullAndCapsuleContact::Destroy(b3Contact* contact, b3BlockAllocator* allocator)
{
	((b3HullAndCapsuleContact*)contact)->~b3HullAndCapsuleContact();
	allocator->Free(contact, sizeof(b3HullAndCapsuleContact));
}

b3HullAndCapsuleContact::b3HullAndCapsuleContact(b3Shape* shapeA, b3Shape* shapeB) : b3ConvexContact(shapeA, shapeB)
{
	B3_ASSERT(shapeA->GetType() == e_hullShape);
	B3_ASSERT(shapeB->GetType() == e_capsuleShape);
}

void b3HullAndCapsuleContact::Collide()
{
	b3Shape* shapeA = GetShapeA();
	b3Shape* shapeB = GetShapeB();

	b3Transform xfA = shapeA->GetBody()->GetTransform();
	b3Transform xfB = shapeB->GetBody()->GetTransform();

	b3HullShape* hullA = (b3HullShape*)shapeA;
	b3CapsuleShape* capsuleB = (b3CapsuleShape*)shapeB;

	B3_ASSERT(m_manifoldCount == 0);
	b3CollideHullAndCapsule(m_stackManifold, xfA, hullA, xfB, capsuleB);
	m_manifoldCount = 1;
}