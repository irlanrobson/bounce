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

#include <bounce/dynamics/contacts/capsule_sphere_contact.h>
#include <bounce/dynamics/shapes/capsule_shape.h>
#include <bounce/dynamics/shapes/sphere_shape.h>
#include <bounce/dynamics/body.h>
#include <bounce/common/memory/block_allocator.h>

b3Contact* b3CapsuleAndSphereContact::Create(b3Shape* shapeA, b3Shape* shapeB, b3BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b3CapsuleAndSphereContact));
	return new (mem) b3CapsuleAndSphereContact(shapeA, shapeB);
}

void b3CapsuleAndSphereContact::Destroy(b3Contact* contact, b3BlockAllocator* allocator)
{
	((b3CapsuleAndSphereContact*)contact)->~b3CapsuleAndSphereContact();
	allocator->Free(contact, sizeof(b3CapsuleAndSphereContact));
}

b3CapsuleAndSphereContact::b3CapsuleAndSphereContact(b3Shape* shapeA, b3Shape* shapeB) : b3ConvexContact(shapeA, shapeB)
{
	B3_ASSERT(shapeA->GetType() == e_capsuleShape);
	B3_ASSERT(shapeB->GetType() == e_sphereShape);
}

void b3CapsuleAndSphereContact::Evaluate(b3Manifold& manifold, const b3Transform& xfA, const b3Transform& xfB) 
{
	b3CollideCapsuleAndSphere(manifold, xfA, (b3CapsuleShape*)GetShapeA(), xfB, (b3SphereShape*)GetShapeB());
}